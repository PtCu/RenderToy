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

namespace platinum
{
    Renderer::Renderer(int img_h, int img_w, int channel, const std::string &fname, int iters)
        : img(Image(img_h, img_w, channel)), filename(fname), iterations(iters)
    {
    }

    void Renderer::Render(const World &scene, const Camera &cam)
    {
        size_t ny = img.GetHeight();
        size_t nx = img.GetWidth();
        float u, v;
        for (int j = 0; j < ny; ++j)
        {
            for (int i = 0; i < nx; ++i)
            {
                glm::vec3 col(0, 0, 0);
                for (int s = 0; s < iterations; ++s)
                {
                    u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
                    v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);
                    Ray r = cam.GetRay(u, v);
                    col += scene.CastRay(r, 0);
                }
                col /= static_cast<float>(iterations);
                col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
                img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
            }
        }
        img.SaveAsPNG(filename);
    }
}
