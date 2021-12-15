// The MIT License (MIT)

// Copyright (c) 2021 PtCu

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include "renderer.h"
#include <fstream>
inline float clamp(const float &lo, const float &hi, const float &v)
{
    return std::max(lo, std::min(hi, v));
}

namespace platinum
{
    Renderer::Renderer(int img_w, int img_h, int channel, const std::string &fname, int iters)
        : filename_(fname), _spp(iters)
    {
        img_.GenBuffer(img_w, img_h, channel);
    }
    void Renderer::UpdateProgress(float progress)
    {
        int barWidth = 70;

        std::cout << "[";
        int pos = static_cast<int>(barWidth * progress);
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < pos)
                std::cout << "=";
            else if (i == pos)
                std::cout << ">";
            else
                std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();
    };
    void Renderer::Render(Scene &scene, const std::shared_ptr<Camera> &cam)
    {
        scene.BuildBVH();
        int nx = img_.GetWidth();
        int ny = img_.GetHeight();

        int img_size = ny * nx;
        std::vector<glm::vec3> framebuffer(img_size);
        int has_finished_num = 0;
        auto calculateRstForEachTile = [&](size_t row_start, size_t row_end, size_t col_start, size_t col_end)
        {
            for (size_t i = row_start; i < row_end; ++i)
            {
                int px_id = i * nx + col_start;
                for (size_t j = col_start; j < col_end; ++j)
                {
                    for (int k = 0; k < _spp; k++)
                    {
                        float u = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(nx);
                        float v = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(ny);
                        auto r = cam->GetRay(u, v);
                        auto rst = scene.CastRay(r);
                        framebuffer[px_id] += (rst / static_cast<float>(_spp));
                    }

                    ++has_finished_num;
                    ++px_id;
                }
                // 互斥锁，用于打印处理进程
                std::lock_guard<std::mutex> g1(_mutex_ins);
                UpdateProgress(static_cast<float>(has_finished_num) / img_size);
            }
        };

        int id = 0;
        constexpr int bx = 4;
        constexpr int by = 4;
        std::thread th[bx * by];

        int strideX = (nx + 1) / bx;
        int strideY = (ny + 1) / by;

        // 分块计算光线追踪
        for (int i = 0; i < nx; i += strideX)
        {
            for (int j = 0; j < ny; j += strideY)
            {
                th[id] = std::thread(calculateRstForEachTile, i, std::min(i + strideX, ny), j, std::min(j + strideY, nx));
                id++;
            }
        }
        for (int i = 0; i < bx * by; i++)
            th[i].join();
        UpdateProgress(1.f);
        // for (int cnt = 1; cnt <= spp_; ++cnt)
        // {
        //     for (int px_id = 0; px_id < img_size; ++px_id)
        //     {
        //         int i = px_id % nx;
        //         int j = px_id / nx;
        //         u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
        //         v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);

        //         auto r = cam->GetRay(u, v);
        //         auto rst = scene.CastRay(r);

        //         framebuffer[px_id] += (rst / static_cast<float>(spp_));
        //     }
        //     UpdateProgress(static_cast<float>(cnt) / spp_);
        // }

#pragma omp parallel for schedule(dynamic, 1024)
        for (int px_id = 0; px_id < img_size; ++px_id)
        {
            int i = px_id % nx;
            int j = px_id / nx;
            auto col = framebuffer[px_id];
            col.r = std::pow(clamp(0, 1, col.r), 0.6f);
            col.g = std::pow(clamp(0, 1, col.g), 0.6f);
            col.b = std::pow(clamp(0, 1, col.b), 0.6f);
            glm::vec3 new_col(col.r, col.g, col.b);

            img_.SetPixel(i, j, new_col);
        }
        // UpdateProgress(1.f);
        img_.SaveAsPNG(filename_);
    }
}
