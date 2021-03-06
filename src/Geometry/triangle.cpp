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

    void Triangle::Sample(Intersection &inter, float &pdf) const
    {
        float x = std::sqrt(Random::RandomInUnitFloat()), y = Random::RandomInUnitFloat();
        inter.vert.pos = A.pos * (1.0f - x) + B.pos * (x * (1.0f - y)) + C.pos * (x * y);
        inter.vert.normal = this->normal;
        pdf = 1.0f / area;
        // inter.ray->SetColor(material->Emit());
    }
    AABB Triangle::GetBoundingBox() const
    {
        return bounding_box;
    }
    float Triangle::GetArea() const
    {
        return area;
    }
    Triangle::Triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const std::shared_ptr<Material> &material)
        : A(a), B(b), C(c), Object(material)
    {
        e1 = C.pos - A.pos;
        e2 = B.pos - A.pos;
        normal = -glm::normalize(glm::cross(e1, e2));
        area = 0.5f * glm::cross(e1, e2).length();
        bounding_box = AABB(A.pos, B.pos);
        bounding_box.Expand(C.pos);
    }
    Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c, const std::shared_ptr<Material> &material)
        : A(a), B(b), C(c), Object(material)
    {
        e1 = C.pos - A.pos;
        e2 = B.pos - A.pos;
        normal = -glm::normalize(glm::cross(e1, e2));
        area = 0.5f * glm::cross(e1, e2).length();
        // glm::vec3 minP = min(min(A.pos, B.pos), C.pos);
        // glm::vec3 maxP = max(max(A.pos, B.pos), C.pos);
        // for (size_t i = 0; i < 3; i++)
        // {
        //     if (minP[i] == maxP[i])
        //     {
        //         minP[i] -= 0.001f;
        //         maxP[i] += 0.001f;
        //     }
        // }
        // bounding_box = AABB(minP, maxP);
        bounding_box = AABB(A.pos, B.pos);
        bounding_box.Expand(C.pos);
    }
    glm::vec4 Triangle::intersectRay(const glm::vec3 &o, const glm::vec3 &d)
    {
        glm::mat3 equation_A(glm::vec3(A.pos - B.pos), glm::vec3(A.pos - C.pos), d);

        if (glm::abs(glm::determinant(equation_A)) < EPSILON)
            return glm::vec4(0, 0, 0, 0);

        glm::vec3 equation_b = A.pos - o;
        glm::vec3 equation_X = glm::inverse(equation_A) * equation_b;
        float alpha = 1 - equation_X[0] - equation_X[1];
        return glm::vec4(alpha, equation_X);
    }

    Intersection Triangle::Intersect(std::shared_ptr<Ray> &r)
    {
        // //moller trumbore algorithm
        // Intersection inter;

        // if (glm::dot(r->GetDirection(), normal) > 0)
        //     return inter;
        // float u, v, t_tmp = 0;
        // glm::vec3 pvec = glm::cross(r->GetDirection(), e2);
        // float det = glm::dot(e1, pvec);
        // // This r is parallel to this triangle.
        // if (fabs(det) < EPSILON)
        //     return inter;

        // float det_inv = 1. / det;
        // glm::vec3 tvec = r->GetOrigin() - A.pos;
        // u = glm::dot(tvec, pvec) * det_inv;
        // if (u < 0 || u > 1)
        //     return inter;
        // glm::vec3 qvec = glm::cross(tvec, e1);
        // v = glm::dot(r->GetDirection(), qvec) * det_inv;
        // if (v < 0 || u + v > 1)
        //     return inter;
        // // At this stage we can compute t to find out where the intersection point is on the line.
        // t_tmp = glm::dot(e2, qvec) * det_inv;

        // // This means that there is a line intersection but not a ray intersection.
        // if (t_tmp < EPSILON)
        // {
        //     return inter;
        // }
        // inter.ray = r;
        // r->SetTMax(t_tmp);
        // inter.vert = r->GetOrigin() + r->GetDirection() * t_tmp;
        // inter.happened = true;
        // inter.material = GetMaterial(); //材料
        // return inter;

        Intersection rec;
        glm::vec4 abgt = this->intersectRay(r->GetOrigin(), r->GetDirection());
        if (abgt == glm::vec4(0) || abgt[0] < 0 || abgt[0] > 1 || abgt[1] < 0 || abgt[1] > 1 || abgt[2] < 0 || abgt[2] > 1 || abgt[3] < r->GetMinTime() || abgt[3] > r->GetMaxTime())
            return rec;

        rec.vert = Vertex::GenVert(glm::vec3(abgt[0], abgt[1], abgt[2]), A, B, C);
        rec.vert.normal = normal;
        rec.ray = r;
        rec.material = GetMaterial();
        rec.happened = true;
        r->SetTMax(abgt[3]);
        return rec;
    }
}
