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

#include "../Core/object.h"
#include "../Core/tRay.h"
#include "../Core/intersection.h"
#include "../Core/aabb.h"
#include "../Math/rand.h"
#include "sphere.h"

namespace platinum
{
    class MovingSphere : public Sphere
    {
    public:
        MovingSphere() = default;
        ~MovingSphere() = default;
        MovingSphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, const std::shared_ptr<Material> &m = nullptr);
        virtual AABB GetBoundingBox() const { return bounding_box; }
    
    protected:
        virtual glm::vec3 getCenter(const std::shared_ptr<Ray> &r) const;

    private:
        glm::vec3 center0, center1;
        float time0, time1;
        float radius;
        AABB bounding_box;
    };

} // namespace platinum

#endif
