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

#include "moving_sphere.h"

namespace platinum
{

    MovingSphere::MovingSphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, const std::shared_ptr<Material> &m)
        : _center(cen0), _center1(cen1), _t0(t0), _t1(t1), Sphere(glm::vec3(0), r, m)
    {
        glm::vec3 minP = glm::min(_center - glm::vec3(_radius), _center1 - glm::vec3(_radius));
        glm::vec3 maxP = glm::max(_center + glm::vec3(_radius), _center1 + glm::vec3(_radius));
        _bounding_box = AABB(minP, maxP);
    }

    glm::vec3 MovingSphere::getCenter(const std::shared_ptr<Ray> &r) const
    {
        std::shared_ptr<TRay> tRay = std::dynamic_pointer_cast<TRay>(r);
        float t = tRay->GetTime();
        return _center + ((t - _t0) / (_t1 - _t0)) * (_center1 - _center);
    }

} // namespace platinum
