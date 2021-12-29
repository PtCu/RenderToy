// The MIT License (MIT)

// Copyright (c) 2021 PtCU

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

#ifndef CORE_RAND_H_
#define CORE_RAND_H_

#include <random>
#include <core/defines.h>
#include <glm/glm.hpp>

namespace platinum
{
    class Random
    {
    public:
        static float RandomInUnitFloat()
        {
            static std::random_device seed_gen;
            static std::mt19937 engine(seed_gen());
            static std::uniform_real_distribution<> dist(0.f, 1.f);
            return static_cast<float>(dist(engine));
        }
        static glm::vec3 RandomInUnitDisk()
        {
            glm::vec3 p;
            do
            {
                p = 2.0f * glm::vec3(RandomInUnitFloat(), RandomInUnitFloat(), 0) - glm::vec3(1, 1, 0);
            } while (glm::dot(p, p) >= 1.0);
            return p;
        }
        static glm::vec3 RandomInUnitSphere()
        {
            glm::vec3 p;
            do
            {
                p = 2.0f * glm::vec3(RandomInUnitFloat(), RandomInUnitFloat(), RandomInUnitFloat()) - glm::vec3(1, 1, 1);
            } while (glm::dot(p, p) >= 1.0);
            return p;
        }
    };

} // namespace platinum

#endif
