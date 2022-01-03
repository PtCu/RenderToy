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

#ifndef GEOMETRY_SPHERE_H_
#define GEOMETRY_SPHERE_H_

#include <core/object.h>
#include <core/ray.h>
#include <core/intersection.h>
#include <core/aabb.h>
#include <math/rand.h>

namespace platinum
{
    class Sphere : public Object
    {
    public:
        Sphere() = default;
        Sphere(glm::vec3 cen, float r, std::shared_ptr<Material> m = nullptr);
        ~Sphere() = default;
        virtual HitRst Intersect(const Ray& r);
        virtual float GetArea() const;
        virtual AABB GetBoundingBox() const;
        virtual void Sample(HitRst& inter, float& pdf) const;

    protected:
        virtual glm::vec3 getCenter(const Ray& r) const;
        virtual void setIntersection(float t, HitRst& rec, const Ray& r) const;
        void getSphereUV(const glm::vec3& p, float& u, float& v) const;

    private:
        float area_;
        glm::vec3 center_;
        float radius_;
        AABB bounding_box_;
    };

} // namespace platinum

#endif
