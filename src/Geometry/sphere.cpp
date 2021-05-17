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

#include "sphere.h"
namespace platinum
{
    float Sphere::GetArea() const
    {
    }
    AABB Sphere::GetBoundingBox() const
    {
        return bounding_box;
    }
    glm::vec3 Sphere::getCenter(const std::shared_ptr<Ray> &r) const
    {
        return center;
    }
    Sphere::Sphere(glm::vec3 cen, float r, const std::shared_ptr<Material> &m)
        : center(cen), radius(r), Object(m)
    {
        glm::vec3 minP = center - glm::vec3(radius);
        glm::vec3 maxP = center + glm::vec3(radius);
        bounding_box = AABB(minP, maxP);
        area = PI * 4.0f * r * r;
    };
    void Sphere::setIntersection(float t, Intersection &rec, const std::shared_ptr<Ray> &r) const
    {
        rec.ray = r;
        rec.ray->SetTMax(t);
        rec.vert.pos = r->PointAtT(rec.ray->GetMaxTime());
        rec.vert.normal = glm::vec3((rec.vert.pos - getCenter(r)) / radius);
        getSphereUV(rec.vert.normal, rec.vert.u, rec.vert.v);
        rec.material = GetMaterial();
        rec.happened = true;
    }

    Intersection Sphere::Intersect(std::shared_ptr<Ray> &r)
    {
        Intersection rec;
        glm::vec3 oc = r->GetOrigin() - getCenter(r);
        float a = glm::dot(r->GetDirection(), r->GetDirection());
        float b = glm::dot(oc, r->GetDirection());
        float c = glm::dot(oc, oc) - radius * radius;
        float discriminant = b * b - a * c;
        if (discriminant > 0)
        {
            float temp = (-b - sqrt(discriminant)) / a;
            if (temp < r->GetMaxTime() && temp > r->GetMinTime())
            {
                setIntersection(temp, rec, r);
            }
            temp = (-b + sqrt(discriminant)) / a;
            if (temp < r->GetMaxTime() && temp > r->GetMinTime())
            {
                setIntersection(temp, rec, r);
            }
        }
        return rec;
    }
    //Using the polar coordinates of sphere (phi, theta) to get fractions as u, v.
    void Sphere::getSphereUV(const glm::vec3 &p, float &u, float &v) const
    {
        float phi = atan2(p.z, p.x);
        float theta = asin(p.y);
        u = 1 - (phi + PI) / (2 * PI);
        v = (theta + PI / 2) / PI;
    }

} // namespace platinum
