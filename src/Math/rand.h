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

#include "vector.h"
#include <random>

namespace platinum
{
    class Random
    {
    public:
        static double drand48()
        {
            static std::random_device seed_gen;
            static std::mt19937 engine(seed_gen);
            static std::uniform_real_distribution<> dist(0.0, 1.0);
            return dist(engine);
        }
        static Vector3f RandomInUnitDisk()
        {
            Vector3f p;
            do
            {
                p = 2.0 * Vector3f(drand48(), drand48(), 0) - Vector3f(1, 1, 0);
            } while (Dot(p, p) >= 1.0);
            return p;
        }
        static Vector3f RandomInUnitSphere()
        {
            Vector3f p;
            do
            {
                p = 2.0 * Vector3f(drand48(), drand48(), drand48()) - Vector3f(1, 1, 1);
            } while (Dot(p, p) >= 1.0);
            return p;
        }
    };

} // namespace platinum

#endif
