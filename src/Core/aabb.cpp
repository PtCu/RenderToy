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
    AABB::AABB()
    {
        float _min = std::numeric_limits<float>::lowest();
        float _max = std::numeric_limits<float>::max();
        p_min_ = glm::vec3{ _max, _max, _max };
        p_max_ = glm::vec3{ _min, _min, _min };
        is_valid_ = false;
    }
    AABB::AABB(const glm::vec3& a, const glm::vec3& b)
    {
        p_min_ = glm::min(a, b);
        p_max_ = glm::max(a, b);
        is_valid_ = true;
    }
    bool AABB::IsHit(const Ray& r) const
    {
        if (is_valid_ == false)
            return false;
        const glm::vec3 invDir = r.GetInvDirection();
        const AABB& bounds = *this;
        // Check for ray intersection against $x$ and $y$ slabs
        auto tMin = (bounds[r.IsDirNeg(0)].x - r.GetOrigin().x) * invDir.x;
        auto tMax = (bounds[1 - r.IsDirNeg(0)].x - r.GetOrigin().x) * invDir.x;
        auto tyMin = (bounds[r.IsDirNeg(1)].y - r.GetOrigin().y) * invDir.y;
        auto tyMax = (bounds[1 - r.IsDirNeg(1)].y - r.GetOrigin().y) * invDir.y;

        if (tMin > tyMax || tyMin > tMax)
            return false;
        if (tyMin > tMin)
            tMin = tyMin;
        if (tyMax < tMax)
            tMax = tyMax;

        // Check for ray intersection against $z$ slab
        auto tzMin = (bounds[r.IsDirNeg(2)].z - r.GetOrigin().z) * invDir.z;
        auto tzMax = (bounds[1 - r.IsDirNeg(2)].z - r.GetOrigin().z) * invDir.z;

        if (tMin > tzMax || tzMin > tMax)
            return false;
        if (tzMin > tMin)
            tMin = tzMin;
        if (tzMax < tMax)
            tMax = tzMax;

        return (tMin < r.GetMaxTime()) && (tMax > 0);
    }
    AABB AABB::Intersect(const AABB& b) const
    {
        return AABB(glm::max(p_min_, b.p_min_), glm::min(p_max_, b.p_max_));
    }
    void AABB::Expand(const AABB& aabb)
    {
        if (aabb.is_valid_)
        {
            if (is_valid_)
            {
                p_min_ = glm::min(p_min_, aabb.p_min_);
                p_max_ = glm::max(p_max_, aabb.p_max_);
            }
            else
            {
                p_min_ = aabb.GetMin();
                p_max_ = aabb.GetMax();
                is_valid_ = true;
            }
        }
    }
    void AABB::Expand(const glm::vec3& p)
    {
        p_min_ = glm::min(p_min_, p);
        p_max_ = glm::max(p_max_, p);
        is_valid_ = true;
    }
    glm::vec3 AABB::Offset(const glm::vec3& p) const
    {
        assert(p_max_.x > p_min_.x && p_max_.y > p_min_.y && p_max_.z > p_min_.z);
        glm::vec3 o = p - p_min_;
        o.x /= p_max_.x - p_min_.x;
        o.y /= p_max_.y - p_min_.y;
        o.z /= p_max_.z - p_min_.z;
        return o;
    }
    bool AABB::Overlaps(const AABB& p) const
    {
        bool x = (p_max_.x >= p.p_min_.x) && (p_min_.x <= p.p_max_.x);
        bool y = (p_max_.y >= p.p_min_.y) && (p_min_.y <= p.p_max_.y);
        bool z = (p_max_.z >= p.p_min_.z) && (p_min_.z <= p.p_max_.z);
        return (x && y && z);
    }
    bool AABB::Inside(const glm::vec3& p) const
    {
        return p.x >= p_min_.x && p.x <= p_max_.x &&
            p.y >= p_min_.y && p.y <= p_max_.y &&
            p.z >= p_min_.z && p.z <= p_max_.z;
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
