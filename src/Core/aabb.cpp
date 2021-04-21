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

#include "aabb.h"

namespace platinum
{
    bool AABB::IsHit(const std::shared_ptr<Ray> &r) const
    {
        if (is_valid == false)
            return false;
        const glm::vec3 invDir = r->GetInvDirection();
        const AABB &bounds = *this;
        // Check for ray intersection against $x$ and $y$ slabs
        auto tMin = (bounds[r->IsDirNeg(0)].x - r->GetOrigin().x) * invDir.x;
        auto tMax = (bounds[1 - r->IsDirNeg(0)].x - r->GetOrigin().x) * invDir.x;
        auto tyMin = (bounds[r->IsDirNeg(1)].y - r->GetOrigin().y) * invDir.y;
        auto tyMax = (bounds[1 - r->IsDirNeg(1)].y - r->GetOrigin().y) * invDir.y;

        if (tMin > tyMax || tyMin > tMax)
            return false;
        if (tyMin > tMin)
            tMin = tyMin;
        if (tyMax < tMax)
            tMax = tyMax;

        // Check for ray intersection against $z$ slab
        auto tzMin = (bounds[r->IsDirNeg(2)].z - r->GetOrigin().z) * invDir.z;
        auto tzMax = (bounds[1 - r->IsDirNeg(2)].z - r->GetOrigin().z) * invDir.z;

        if (tMin > tzMax || tzMin > tMax)
            return false;
        if (tzMin > tMin)
            tMin = tzMin;
        if (tzMax < tMax)
            tMax = tzMax;

        return (tMin < r->GetMaxTime()) && (tMax > 0);
    }
    AABB AABB::Intersect(const AABB &b) const
    {
        return AABB(glm::max(p_min, b.p_min), glm::min(p_max, b.p_max));
    }
    void AABB::Expand(const AABB &aabb)
    {
        if (aabb.is_valid)
        {
            if (is_valid)
            {
                p_min = glm::min(p_min, aabb.p_min);
                p_max = glm::max(p_max, aabb.p_max);
            }
            else{
                p_min = aabb.GetMin();
                p_max = aabb.GetMax();
                is_valid = true;
            }
        }

        
    }
    void AABB::Expand(const glm::vec3 &p)
    {
        p_min = glm::min(p_min, p);
        p_max = glm::max(p_max, p);
        is_valid = true;
    }
    glm::vec3 AABB::Offset(const glm::vec3 &p) const
    {
        assert(p_max.x > p_min.x && p_max.y > p_min.y && p_max.z > p_min.z);
        glm::vec3 o = p - p_min;
        o.x /= p_max.x - p_min.x;
        o.y /= p_max.y - p_min.y;
        o.z /= p_max.z - p_min.z;
        return o;
    }
    bool AABB::Overlaps(const AABB &p) const
    {
        bool x = (p_max.x >= p.p_min.x) && (p_min.x <= p.p_max.x);
        bool y = (p_max.y >= p.p_min.y) && (p_min.y <= p.p_max.y);
        bool z = (p_max.z >= p.p_min.z) && (p_min.z <= p.p_max.z);
        return (x && y && z);
    }
    bool AABB::Inside(const glm::vec3 &p) const
    {
        return p.x >= p_min.x && p.x <= p_max.x &&
               p.y >= p_min.y && p.y <= p_max.y &&
               p.z >= p_min.z && p.z <= p_max.z;
    }

    int AABB::MaxExtent() const
    {
        glm::vec3 d = Diagonal();
        if (d.x > d.y && d.x > d.z)
            return 0;
        else if (d.y > d.z)
            return 1;
        else
            return 2;
    }

}
