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

#ifndef GEOMETRY_MOVESPHERE_H_
#define GEOMETRY_MOVESPHERE_H_

#include <core/object.h>
#include <core/ray.h>
#include <core/intersection.h>
#include <core/aabb.h>
#include <math/rand.h>
#include <geometry/sphere.h>

namespace platinum
{
    class MovingSphere : public Sphere
    {
    public:
        MovingSphere() = default;
        ~MovingSphere() = default;
        MovingSphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, std::shared_ptr<Material> m = nullptr);
        virtual AABB GetBoundingBox() const { return bounding_box_; }

    protected:
        virtual glm::vec3 getCenter(const Ray& r) const;

    private:
        glm::vec3 center0, center1;
        float time0_, time1_;
        float radius_;
        AABB bounding_box_;
    };

} // namespace platinum

#endif
