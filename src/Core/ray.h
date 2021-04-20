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
        Ray(const glm::vec3 &o, const glm::vec3 &d) : origin(o), direction(d)
        {
            t_min = 0.0;
            t_max = std::numeric_limits<float>::max();
            color = glm::vec3(1.0);
            inv_d = {1.0f / d.x, 1.0f / d.y, 1.0f / d.z};
            dirIsNeg = {d.x < 0, d.y < 0, d.z < 0};
            isTransformed = false;
        }
        virtual ~Ray() = default;
        void Update(const glm::vec3 &o, const glm::vec3 &d, const glm::vec3 &a);

        glm::vec3 GetOrigin() const { return origin; }

        glm::vec3 GetDirection() const { return direction; }

        glm::vec3 GetInvDirection() const { return inv_d; }

        float GetMinTime() const { return t_min; }

        float GetMaxTime() const { return t_max; }

        glm::vec3 GetColor() const { return color; }

        glm::vec3 PointAtT(float t) const { return origin + t * direction; }

        int IsDirNeg(size_t i) const { return dirIsNeg[i]; }

        void SetColor(const glm::vec3 &c);

        void SetTMax(float t) { t_max = t; }

        void Transform(const glm::mat4 &transform);

    protected:
        virtual void DoNothing() {}

    private:
        glm::vec3 origin;
        glm::vec3 direction, inv_d;
        glm::vec3 color;
        float t_min, t_max;
        std::array<int, 3> dirIsNeg;
        bool isTransformed;
    };
} // namespace platinum

#endif
