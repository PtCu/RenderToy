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
    bool AABB::Hit(const Ray &r, float tmin, float tmax) const
    {
        for (int i = 0; i < 3; i++)
        {
            float t0 = glm::min((p_min[i] - r.GetOrigin()[i]) / r.GetDirection()[i],
                                (p_max[i] - r.GetOrigin()[i]) / r.GetDirection()[i]);
            float t1 = glm::max((p_min[i] - r.GetOrigin()[i]) / r.GetDirection()[i],
                                (p_max[i] - r.GetOrigin()[i]) / r.GetDirection()[i]);

            tmin = glm::max(t0, tmin);
            tmax = glm::min(t1, tmax);
            if (tmax <= tmin)
                return false;
        }
        return true;
    }
    AABB AABB::Intersect(const AABB &b) const
    {
        return AABB(glm::max(p_min, b.p_min), glm::min(p_max, b.p_max));
    }
    void AABB::Expand(const AABB &aabb)
    {
        p_min = glm::min(p_min, aabb.p_min);
        p_max = glm::max(p_max, aabb.p_max);
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

    int AABB::maxExtent() const
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
