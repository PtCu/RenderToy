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

#ifndef CORE_AABB_H_
#define CORE_AABB_H_

#include "defines.h"
#include <glm/glm.hpp>
#include "ray.h"

namespace platinum
{
    class AABB
    {
    public:
        AABB()
        {
            float _min = std::numeric_limits<float>::lowest();
            float _max = std::numeric_limits<float>::max();
            p_min = glm::vec3(_max, _max, _max);
            p_max = glm::vec3(_min, _min, _min);
        }
        AABB(const glm::vec3 &a, const glm::vec3 &b)
        {
            p_min = glm::min(a, b);
            p_max = glm::max(a, b);
        }
        AABB Intersect(const AABB &b) const;

        void Expand(const AABB &aabb);

        glm::vec3 Offset(const glm::vec3 &p) const;

        bool Overlaps(const AABB &p) const;

        bool Inside(const glm::vec3 &p) const;

        int maxExtent() const;

        bool Hit(const Ray &r, float tmin, float tmax) const;
       
        inline const glm::vec3 operator[](int i) const
        {
            return i == 0 ? p_min : p_max;
        }
        inline glm::vec3 Diagonal() const { return p_max - p_min; }
        inline float SurfaceArea() const {}
        inline glm::vec3 Centroid() { return 0.5f * p_min + 0.5f * p_max; }
        inline glm::vec3 GetMin() const { return p_min; }
        inline glm::vec3 GetMax() const { return p_max; }

    private:
        glm::vec3 p_min;
        glm::vec3 p_max;
    };
    inline AABB Union(const AABB &b1, const AABB &b2)
    {
        glm::vec3 min_p = glm::min(b1.GetMin(), b2.GetMin());
        glm::vec3 max_p = glm::max(b1.GetMax(), b2.GetMax());
        return AABB(min_p, max_p);
    }
}
#endif