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

#include "movingSphere.h"

namespace platinum
{
    MovingSphere::MovingSphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, std::shared_ptr<Material> m)
        : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), material(std::move(m))
    {
        glm::vec3 minP = glm::min(center0 - glm::vec3(radius), center1 - glm::vec3(radius));
        glm::vec3 maxP = glm::max(center0 + glm::vec3(radius), center1 + glm::vec3(radius));
        bounding_box = AABB(minP, maxP);
    };
    Intersection MovingSphere::Intersect(const Ray &r) const
    {
        Intersection rec;
        glm::vec3 oc = r.GetOrigin() - GetCenter(r.GetTime());
        float a = glm::dot(r.GetDirection(), r.GetDirection());
        float b = glm::dot(oc, r.GetDirection());
        float c = glm::dot(oc, oc) - radius * radius;
        float discriminant = b * b - a * c;
        if (discriminant > 0)
        {
            float temp = (-b - sqrt(discriminant)) / a;
            if (temp < r.GetMaxTime() && temp > r.GetMinTime())
            {
                rec.time = temp;
                rec.point = r.PointAtT(rec.time);
                rec.normal = glm::vec3((rec.point - GetCenter(r.GetTime())) / radius);
                rec.material = material;
                return rec;
            }
            temp = (-b + sqrt(discriminant)) / a;
            if (temp < r.GetMaxTime() && temp > r.GetMinTime())
            {
                rec.time = temp;
                rec.point = r.PointAtT(rec.time);
                rec.normal = glm::vec3((rec.point - GetCenter(r.GetTime())) / radius);
                rec.material = material;
                return rec;
            }
        }
        return rec;
    }
} // namespace platinum
