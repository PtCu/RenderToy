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

#include <geometry/triangle.h>

namespace platinum
{

    void Triangle::Sample(HitRst& rst, float& pdf) const
    {
        float x = std::sqrt(Random::RandomInUnitFloat()), y = Random::RandomInUnitFloat();
        rst.record.vert.position_ = A.position_ * (1.0f - x) + B.position_ * (x * (1.0f - y)) + C.position_ * (x * y);
        rst.record.vert.normal_ = this->normal_;
        pdf = 1.0f / area_;
    }
    AABB Triangle::GetBoundingBox() const
    {
        return bounding_box_;
    }
    float Triangle::GetArea() const
    {
        return area_;
    }
    Triangle::Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, std::shared_ptr<Material> material_)
        : A(a), B(b), C(c), Object(material_)
    {
        e1 = B.position_ - A.position_;
        e2 = C.position_ - A.position_;
        normal_ = glm::normalize(glm::cross(e1, e2));
        area_ = 0.5f * glm::length(glm::cross(e1, e2));
        bounding_box_ = AABB(A.position_, B.position_);
        bounding_box_.Expand(C.position_);
    }
    Triangle::Triangle(const Vertex& a, const Vertex& b, const Vertex& c, std::shared_ptr<Material> material_)
        : A(a), B(b), C(c), Object(material_)
    {
        e1 = B.position_ - A.position_;
        e2 = C.position_ - A.position_;
        normal_ = glm::normalize(glm::cross(e1, e2));
        area_ = 0.5f * glm::length(glm::cross(e1, e2));
        bounding_box_ = AABB(A.position_, B.position_);
        bounding_box_.Expand(C.position_);
    }
    glm::vec4 Triangle::intersectRay(const glm::vec3& o, const glm::vec3& d)
    {
        glm::mat3 equation_A(glm::vec3(A.position_ - B.position_), glm::vec3(A.position_ - C.position_), d);

        if (glm::abs(glm::determinant(equation_A)) < EPSILON)
            return glm::vec4(0, 0, 0, 0);

        glm::vec3 equation_b = A.position_ - o;
        glm::vec3 equation_X = glm::inverse(equation_A) * equation_b;
        float alpha = 1 - equation_X[0] - equation_X[1];
        return glm::vec4(alpha, equation_X);
    }

    HitRst Triangle::Intersect(const Ray& r)
    {
        HitRst rst;
        glm::vec4 abgt = this->intersectRay(r.GetOrigin(), r.GetDirection());
        if (abgt == glm::vec4(0) || abgt[0] < 0 || abgt[0] > 1 || abgt[1] < 0 || abgt[1] > 1 || abgt[2] < 0 || abgt[2] > 1 || abgt[3] < r.GetMinTime() || abgt[3] > r.GetMaxTime())
            return HitRst::InValid;

        rst.record.vert = Vertex::GenVert(glm::vec3(abgt[0], abgt[1], abgt[2]), A, B, C);
        rst.record.vert.normal_ = this->normal_;
        rst.record.ray = r;
        rst.material = GetMaterial();
        rst.is_hit = true;
        rst.record.ray.SetTMax(abgt[3]);
        return rst;
    }
}
