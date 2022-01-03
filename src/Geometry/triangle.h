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

#ifndef GEOMETRY_TRIANGLE_H_
#define GEOMETRY_TRIANGLE_H_

#include <core/object.h>
#include <core/ray.h>
#include <core/intersection.h>
#include <core/aabb.h>
#include <geometry/vertex.h>
#include <math/rand.h>

namespace platinum
{
    class Triangle : public Object
    {
    public:
        Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, std::shared_ptr<Material> material_ = NULL);
        Triangle(const Vertex& a, const Vertex& b, const Vertex& c, std::shared_ptr<Material> material_ = NULL);
        virtual HitRst Intersect(const Ray& r);
        virtual AABB GetBoundingBox() const;
        virtual float GetArea() const;
        virtual void Sample(HitRst& inter, float& pdf) const;
        const Vertex& GetA() const { return A; }
        const Vertex& GetB() const { return B; }
        const Vertex& GetC() const { return C; }

    protected:
        glm::vec4 intersectRay(const glm::vec3& o, const glm::vec3& d);

    private:
        Vertex A, B, C;
        glm::vec3 normal_, e1, e2;
        float area_{ 0.f };
        AABB bounding_box_;
    };
}

#endif
