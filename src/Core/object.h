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

#ifndef CORE_OBJECT_H_
#define CORE_OBJECT_H_

#include <glm/glm.hpp>
#include "defines.h"
#include "material.h"

namespace platinum
{
    class Object
    {
    public:
        Object() {}
        Object(std::shared_ptr<const Material> mat = NULL) : material(mat) {}
        const std::shared_ptr<const Material> GetMaterial() const { return material; }
        virtual ~Object() {}
        //TODO: 考虑将虚拟函数声明为非公用的，将公用函数声明为非虚拟的
        virtual Intersection Intersect(std::shared_ptr<Ray> &r) = 0;
        virtual AABB GetBoundingBox() const = 0;
        virtual void Sample(Intersection &inter, float &pdf) const = 0;
        virtual float GetArea() const = 0;

    private:
        std::shared_ptr<const Material> material;
    };
} // namespace platinum

#endif