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
inline float clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}

namespace platinum
{
    Renderer::Renderer(int img_w, int img_h, int channel, const std::string& fname, int iters)
        : _filename(fname), _spp(iters)
    {
        _img.GenBuffer(img_w, img_h, channel);
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
    void Renderer::Render(Scene& scene, Camera& cam)
    {
        scene.BuildBVH();
        int nx = _img.GetWidth();
        int ny = _img.GetHeight();
        float u = 0, v = 0;
        int img_size = ny * nx;

        std::vector<glm::vec3> framebuffer(img_size);

        for (int cnt = 1; cnt <= _spp; ++cnt)
        {
#pragma omp parallel for schedule(dynamic, 1024)
            for (int px_id = 0; px_id < img_size; ++px_id)
            {
                int i = px_id % nx;
                int j = px_id / nx;
                u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
                v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);

                auto r = cam.GetRay(u, v);
                auto rst = scene.CastRay(r);

                framebuffer[px_id] += (rst / static_cast<float>(_spp));

            }
            UpdateProgress(static_cast<float>(cnt) / _spp);
        }

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

            _img.SetPixel(i, j, new_col);
        }
        // UpdateProgress(1.f);
        _img.SaveAsPNG(_filename);
    }
}
