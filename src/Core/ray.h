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
#ifndef CORE_RAY_H_
#define CORE_RAY_H_
#include <glm/glm.hpp>
#include "defines.h"

namespace platinum
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const glm::vec3 &a, const glm::vec3 &b, PFloat ti = 0.0) : o(a), d(b), _time(ti) {}
        glm::vec3 GetOrigin() const { return o; }
        glm::vec3 GetDirection() const { return d; }
        PFloat GetTime() const { return _time; }
        glm::vec3 PointAtT(PFloat t) const { return o + t * d; }

        glm::vec3 o;
        glm::vec3 d;
        PFloat _time;
    };
} // namespace platinum

#endif
