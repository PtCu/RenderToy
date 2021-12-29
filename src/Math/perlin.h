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

#ifndef MATH_PERLIN_H_
#define MATH_PERLIN_H_

#include <glm/glm.hpp>
#include <core/defines.h>
#include <math/rand.h>
#include <chrono> // std::chrono::system_clock

namespace platinum
{
    class Perlin
    {
    public:
        static float Turb(const glm::vec3& p, size_t depth = 7);

    private:
        static float GenNoise(const glm::vec3& p);
        static float PerlinInterp(const glm::vec3 c[2][2][2], float u, float v, float w);
        static std::vector<size_t> GenPermute(size_t n);
        static std::vector<glm::vec3> GenRandVec(size_t n);

        static std::vector<glm::vec3> rand_vec_;

        // 0, 1, ... , 255 变更顺序后的序列
        static std::vector<size_t> perm_x_;
        static std::vector<size_t> perm_y_;
        static std::vector<size_t> perm_z_;
    };
}

#endif
