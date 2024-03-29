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
    void Sphere::Sample(HitRst &rst, float &pdf) const
    {
        float theta = 2.0f * PI * Random::RandomInUnitFloat(), phi = PI * Random::RandomInUnitFloat();
        glm::vec3 dir(std::cos(phi), std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta));
        rst.record.vert._position = _center + _radius * dir;
        rst.record.vert._normal = dir;
        pdf = 1.0f / _area;
        rst.emit = _material->Emit();
    }
    float Sphere::GetArea() const
    {
        return _area;
    }
    AABB Sphere::GetBoundingBox() const
    {
        return _bounding_box;
    }
    glm::vec3 Sphere::getCenter(const std::shared_ptr<Ray> &r) const
    {
        return _center;
    }
    Sphere::Sphere(glm::vec3 cen, float r, const std::shared_ptr<Material> &m)
        : _center(cen), _radius(r), Object(m)
    {
        glm::vec3 minP = _center - glm::vec3(_radius);
        glm::vec3 maxP = _center + glm::vec3(_radius);
        _bounding_box = AABB(minP, maxP);
        _area = PI * 4.0f * r * r;
    };
    void Sphere::setIntersection(float t, HitRst &rst, const std::shared_ptr<Ray> &r) const
    {
        rst.record.ray = r;
        rst.record.ray->SetTMax(t);
        rst.record.vert._position = r->PointAt(rst.record.ray->GetMaxTime());
        rst.record.vert._normal = glm::vec3((rst.record.vert._position - getCenter(r)) / _radius);
        getSphereUV(rst.record.vert._normal, rst.record.vert._u, rst.record.vert._v);
        rst.material_ = GetMaterial();
        rst.is_hit = true;
    }

    HitRst Sphere::Intersect(std::shared_ptr<Ray> &r)
    {
        HitRst rst;
        glm::vec3 oc = r->GetOrigin() - getCenter(r);
        float a = glm::dot(r->GetDirection(), r->GetDirection());
        float b = glm::dot(oc, r->GetDirection());
        float c = glm::dot(oc, oc) - _radius * _radius;
        float discriminant = b * b - a * c;
        if (discriminant > 0)
        {
            float temp = (-b - sqrt(discriminant)) / a;
            if (temp < r->GetMaxTime() && temp > r->GetMinTime())
            {
                setIntersection(temp, rst, r);
            }
            temp = (-b + sqrt(discriminant)) / a;
            if (temp < r->GetMaxTime() && temp > r->GetMinTime())
            {
                setIntersection(temp, rst, r);
            }
        }
        return rst;
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
