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
#include "ray.h"

namespace platinum
{
    class AABB
    {
    public:
        AABB();
        AABB(const glm::vec3 &a, const glm::vec3 &b);
        ~AABB() = default;
        AABB Intersect(const AABB &b) const;
        void Expand(const glm::vec3 &p);
        void Expand(const AABB &aabb);
        glm::vec3 Offset(const glm::vec3 &p) const;
        bool Overlaps(const AABB &p) const;
        bool Inside(const glm::vec3 &p) const;
        //For best partition when building BVH tree.
        int MaxExtent() const;
        bool IsHit(const std::shared_ptr<Ray> &r) const;
        const glm::vec3 operator[](int i) const
        {
            return i == 0 ? p_min : p_max;
        }
        glm::vec3 Diagonal() const { return p_max - p_min; }
        glm::vec3 Centroid() const { return 0.5f * p_min + 0.5f * p_max; }
        float SurfaceArea() const
        {
            auto d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }
        glm::vec3 GetMin() const { return p_min; }
        glm::vec3 GetMax() const { return p_max; }
        bool IsValid() const { return is_valid; }

    protected:
        glm::vec3 p_min;
        glm::vec3 p_max;
        bool is_valid;
    };

    inline AABB Union(const AABB &b1, const AABB &b2)
    {
        glm::vec3 min_p = glm::min(b1.GetMin(), b2.GetMin());
        glm::vec3 max_p = glm::max(b1.GetMax(), b2.GetMax());
        return AABB(min_p, max_p);
    }
    inline AABB Union(const AABB &b1, const glm::vec3 &b2)
    {
        glm::vec3 min_p = glm::min(b1.GetMin(), b2);
        glm::vec3 max_p = glm::max(b1.GetMax(), b2);
        return AABB(min_p, max_p);
    }
}

#endif