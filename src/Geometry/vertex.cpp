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

#include <geometry/vertex.h>

namespace platinum
{
    Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, float u, float v)
        : position_(pos), normal_(normal), u_(u), v_(v) {}

    void Vertex::Transform(const glm::mat4 &transform)
    {
        auto posQ = transform * glm::vec4(position_, 1.0);
        position_ = glm::vec3(posQ) / posQ.w;
        normal_ = glm::normalize(glm::transpose(glm::inverse(glm::mat3(transform))) * normal_);
    }

    void Vertex::Transform(const glm::mat4 &transform, const glm::mat3 &normalTransform)
    {
        auto posQ = transform * glm::vec4(position_, 1.0);
        position_ = glm::vec3(posQ) / posQ.w;
        normal_ = glm::normalize(normalTransform * normal_);
    }

    const Vertex Vertex::GenVert(const glm::vec3 &abg, const Vertex &A, const Vertex &B, const Vertex &C)
    {
        Vertex rst;
        rst.u_ = glm::dot(abg, glm::vec3(A.u_, B.u_, C.u_));
        rst.v_ = glm::dot(abg, glm::vec3(A.v_, B.v_, C.v_));
        rst.position_ = abg[0] * A.position_ + abg[1] * B.position_ + abg[2] * C.position_;
        rst.normal_ = abg[0] * A.normal_ + abg[1] * B.normal_ + abg[2] * C.normal_;

        return rst;
    }

}
