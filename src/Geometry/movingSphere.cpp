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

    bool MovingSphere::Intersect(const Ray &r, PFloat t_min, PFloat t_max, Intersection &rec) const
    {
        Vector3f oc = r.GetOrigin() - GetCenter(r.GetTime());
        PFloat a = Dot(r.GetDirection(), r.GetDirection());
        PFloat b = Dot(oc, r.GetDirection());
        PFloat c = Dot(oc, oc) - radius * radius;
        PFloat discriminant = b * b - a * c;
        if (discriminant > 0)
        {
            PFloat temp = (-b - sqrt(discriminant)) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.time = temp;
                rec.point = r.PointAtT(rec.time);
                rec.normal = Normal3f((rec.point - GetCenter(r.GetTime())) / radius);
                rec.material = material;
                return true;
            }
            temp = (-b + sqrt(discriminant)) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.time = temp;
                rec.point = r.PointAtT(rec.time);
                rec.normal = Normal3f((rec.point - GetCenter(r.GetTime())) / radius);
                rec.material = material;
                return true;
            }
        }
        return false;
    }
} // namespace platinum
