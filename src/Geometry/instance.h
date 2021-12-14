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

#ifndef CORE_TRANSFORM_H_
#define CORE_TRANSFORM_H_

#include "../core/object.h"
#include "../core/ray.h"
#include "../core/intersection.h"
#include "../core/aabb.h"
#include "../math/rand.h"
#include <bitset>

namespace platinum
{
    //An instance is a geometric primitive that has been moved or rotated somehow.
    class Instance : public Object
    {
    public:
        Instance(const glm::mat4 &transform, std::shared_ptr<Object> former, const std::shared_ptr<Material> &m = NULL);
        virtual HitRst Intersect(std::shared_ptr<Ray> &r);
        virtual AABB GetBoundingBox() const { return bounding_box_; }
        virtual float GetArea() const;
        virtual void Sample(HitRst &inter, float &pdf) const;

    private:
        AABB bounding_box_;
        glm::mat4 transform;
        glm::mat4 inverseTransform;
        glm::mat3 normalTransform;
        std::shared_ptr<Object> former;
    };
}

#endif
