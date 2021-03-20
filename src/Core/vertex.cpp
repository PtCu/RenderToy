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

#include "vertex.h"

namespace platinum
{
    Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, float u, float v)
        : pos(pos), normal(normal), u(u), v(v) {}

    void Vertex::Transform(const glm::mat4 &transform)
    {
        auto posQ = transform * glm::vec4(pos, 1.0);
        pos = glm::vec3(posQ) / posQ.w;
        normal = glm::normalize(glm::transpose(glm::inverse(glm::mat3(transform))) * normal);
    }

    void Vertex::Transform(const glm::mat4 &transform, const glm::mat3 &normalTransform)
    {
        auto posQ = transform * glm::vec4(pos, 1.0);
        pos = glm::vec3(posQ) / posQ.w;
        normal = glm::normalize(normalTransform * normal);
    }

    const Vertex Vertex::GenVert(const glm::vec3 &abg, const Vertex &A, const Vertex &B, const Vertex &C)
    {
        Vertex rst;
        rst.u = glm::dot(abg, glm::vec3(A.u, B.u, C.u));
        rst.v = glm::dot(abg, glm::vec3(A.v, B.v, C.v));
        rst.pos = abg[0] * A.pos + abg[1] * B.pos + abg[2] * C.pos;
        rst.normal = abg[0] * A.normal + abg[1] * B.normal + abg[2] * C.normal;

        return rst;
    }

}
