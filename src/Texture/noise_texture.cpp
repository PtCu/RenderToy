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

#include "noise_texture.h"
namespace platinum
{
    glm::vec3 NoiseTexture::GetValue(float u, float v, const glm::vec3 &p) const
    {
        glm::vec3 c;
        switch (mode_)
        {
        case 0:
            c = color_ * 0.5f * (1.0f + sin(scale_ * p.x + 10 * Perlin::Turb(p * scale_)));
            break;
        case 1:
            c = color_ * 0.5f * (1.0f + sin(10 * Perlin::Turb(p * scale_)));
            break;
        case 2:
            c = color_ * 0.5f * (1.0f + Perlin::Turb(p * scale_));
            break;
        case 3:
            c = color_ * Perlin::Turb(p * scale_);
            break;
        default:
            break;
        }
        return c;
    }

}
