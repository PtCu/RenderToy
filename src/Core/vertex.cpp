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
        : _position(pos), _normal(normal), _u(u), _v(v) {}

    void Vertex::Transform(const glm::mat4 &transform)
    {
        auto posQ = transform * glm::vec4(_position, 1.0);
        _position = glm::vec3(posQ) / posQ.w;
        _normal = glm::normalize(glm::transpose(glm::inverse(glm::mat3(transform))) * _normal);
    }

    void Vertex::Transform(const glm::mat4 &transform, const glm::mat3 &normalTransform)
    {
        auto posQ = transform * glm::vec4(_position, 1.0);
        _position = glm::vec3(posQ) / posQ.w;
        _normal = glm::normalize(normalTransform * _normal);
    }

    const Vertex Vertex::GenVert(const glm::vec3 &abg, const Vertex &A, const Vertex &B, const Vertex &C)
    {
        Vertex rst;
        rst._u = glm::dot(abg, glm::vec3(A._u, B._u, C._u));
        rst._v = glm::dot(abg, glm::vec3(A._v, B._v, C._v));
        rst._position = abg[0] * A._position + abg[1] * B._position + abg[2] * C._position;
        rst._normal = abg[0] * A._normal + abg[1] * B._normal + abg[2] * C._normal;

        return rst;
    }

}
