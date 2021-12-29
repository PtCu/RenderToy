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

#ifndef TEXTURE_NOISE_TEXTURE_H_
#define TEXTURE_NOISE_TEXTURE_H_

#include <core/texture.h>
#include <glm/glm.hpp>
#include <math/perlin.h>
namespace platinum
{
    class NoiseTexture : public Texture
    {
    public:
        NoiseTexture() = default;
        ~NoiseTexture() = default;
        NoiseTexture(float sc, int m = 0, const glm::vec3& c = { 1, 1, 1 }) : scale_(sc), mode_(m), color_(c) {}
        virtual glm::vec3 GetValue(float u, float v, const glm::vec3& p) const;

    private:
        float scale_;
        int mode_;
        glm::vec3 color_;
    };
}

#endif