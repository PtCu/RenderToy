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
namespace platinum
{
    Renderer::Renderer(int img_w, int img_h, int channel, const std::string &fname, int iters)
        : filename(fname), iterations(iters)
    {
        img.GenBuffer(img_w, img_h, channel);
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
        int nx = img.GetWidth();
        int ny = img.GetHeight();
        float u = 0, v = 0;
        int img_size = ny * nx;

        for (int cnt = 1; cnt <= iterations; ++cnt)
        {

#pragma omp parallel for schedule(dynamic, 1024)
            for (int px_id = 0; px_id < img_size; ++px_id)
            {
                int i = px_id % nx;
                int j = px_id / nx;
                u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
                v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);
                auto r = cam->GetRay(u, v);
                auto rst = scene.CastRay(r);
                auto col = img.GetPixel_F(i, j);
                glm::vec3 new_col(col.r, col.g, col.b);
                new_col += rst / (static_cast<float>(iterations));
                Image::Pixel pix(new_col.r, new_col.g, new_col.b);
                img.SetPixel(i, j, pix);
            }
            UpdateProgress(static_cast<float>(cnt) / iterations);
        }
        for (int px_id = 0; px_id < img_size; ++px_id)
        {
            int i = px_id % nx;
            int j = px_id / nx;
            auto col = img.GetPixel_F(i, j);
            col.r = std::pow(col.r, 0.6);
            col.g = std::pow(col.g, 0.6);
            col.b = std::pow(col.b, 0.6);
            glm::vec3 new_col(col.r, col.g, col.b);

            img.SetPixel(i, j, new_col);
        }

        // #pragma omp parallel for schedule(dynamic, 1024)
        //         for (int px_id = 0; px_id < img_size; ++px_id)
        //         {
        //             int i = px_id % nx;
        //             int j = px_id / nx;
        //             glm::vec3 col(0, 0, 0);
        //             for (int cnt = 1; cnt <= iterations; ++cnt)
        //             {
        //                 u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
        //                 v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);
        //                 auto r = cam->GetRay(u, v);
        //                 auto rst = scene.CastRay(r);
        //                 col += rst;
        //             }
        //             col /= (static_cast<float>(iterations));
        //             col = glm::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
        //             img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        //             // UpdateProgress(static_cast<float>(cnt) / iterations);
        //         }

        // for (int j = 0; j < ny; ++j)
        // {
        //     for (int i = 0; i < nx; ++i)
        //     {
        //         glm::vec3 col(0, 0, 0);
        //         for (int s = 0; s < iterations; ++s)
        //         {
        //             u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
        //             v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);
        //             auto r = cam->GetRay(u, v);
        //             col += scene.CastRay(r);
        //         }
        //         col /= static_cast<float>(iterations);
        //         col = glm::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
        //         img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        //     }
        //     UpdateProgress(j / (float)ny);
        // }
        UpdateProgress(1.f);
        img.SaveAsPNG(filename);
    }
}
