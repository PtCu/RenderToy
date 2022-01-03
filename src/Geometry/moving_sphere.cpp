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

    MovingSphere::MovingSphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, std::shared_ptr<Material> m)
        : center0(cen0), center1(cen1), time0_(t0), time1_(t1), Sphere(glm::vec3(0), r, m)
    {
        glm::vec3 minP = glm::min(center0 - glm::vec3(radius_), center1 - glm::vec3(radius_));
        glm::vec3 maxP = glm::max(center0 + glm::vec3(radius_), center1 + glm::vec3(radius_));
        bounding_box_ = AABB(minP, maxP);
    }

    glm::vec3 MovingSphere::getCenter(const Ray& r) const
    {
        float t = r.GetTime();
        return center0 + ((t - time0_) / (time1_ - time0_)) * (center1 - center0);
    }

} // namespace platinum
