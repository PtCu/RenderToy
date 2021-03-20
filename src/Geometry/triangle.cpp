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

#include "triangle.h"

namespace platinum
{
    Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex&c,const std::shared_ptr<Material> &material)
        : A(a), B(b), C(c), Object(material)
    {
        glm::vec3 minP = glm::min(glm::min(A.pos, B.pos), C.pos);
        glm::vec3 maxP = glm::max(glm::max(A.pos, B.pos), C.pos);
        for (size_t i = 0; i < 3; i++)
        {
            if (minP[i] == maxP[i])
            {
                minP[i] -= 0.001f;
                maxP[i] += 0.001f;
            }
        }
        bounding_box = AABB(minP, maxP);
    }

    Intersection Triangle::Intersect(std::shared_ptr<Ray> &r) const
    {
        Intersection rec;
        auto v0 = A.pos;
        auto v1 = B.pos;
        auto v2 = C.pos;
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 pvec = glm::cross(r->GetDirection(), edge2);
        float det = glm::dot(edge1, pvec);
        if (det == 0 || det < 0)
            return rec;

        glm::vec3 tvec = r->GetOrigin() - v0;
        float b1 = glm::dot(tvec, pvec);
        if (b1 < 0 || b1 > det)
            return rec;

        glm::vec3 qvec = glm::cross(tvec, edge1);
        float b2 = glm::dot(r->GetDirection(), qvec);
        if (b2 < 0 || b1 + b2 > det)
            return rec;

        float invDet = 1 / det;

        float tnear = glm::dot(edge2, qvec) * invDet;
        b1 *= invDet;
        b2 *= invDet;

        rec.vert = Vertex::GenVert(glm::vec3(b1, b2, 1 - b1 - b2), A, B, C);
        //hitRst.hitable = this;
        rec.ray = r;
        rec.material = GetMaterial();
        r->SetTMax(tnear);
        return rec;
    }
}
