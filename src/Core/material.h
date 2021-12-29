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

#ifndef CORE_MATERIAL_H_
#define CORE_MATERIAL_H_
#include <glm/glm.hpp>
#include <core/ray.h>
#include <core/intersection.h>
#include <core/defines.h>

namespace platinum
{
    class Material
    {
    public:
        //ordinary scatter
        virtual ~Material() = default;
        // Sample a ray by Material properties
        virtual bool ComputeScatteringFunctions(HitRst& rst) const = 0;
        virtual glm::vec3 Sample(const glm::vec3& d, HitRst& rst) const = 0;
        //Given a ray, calculate the PdF of this ray
        virtual float Pdf(const glm::vec3& wi, const glm::vec3& wo, HitRst& rst) const = 0;
        // brdf. Given a ray, calculate the contribution of this ray
        virtual glm::vec3 ScatterPdf(const glm::vec3& wi, const glm::vec3& wo, HitRst& rst) const = 0;
        //The material_ itself emits light.
        virtual glm::vec3 Emit() const = 0;
        virtual bool IsEmit() const = 0;

    protected:
        bool Refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted) const
        {
            glm::vec3 uv = glm::normalize(v);
            float dt = glm::dot(uv, n);
            float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
            if (discriminant > 0)
            {
                refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
                return true;
            }
            else
                return false;
        }

        glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n) const
        {
            return glm::vec3(v - 2.0f * glm::dot(v, n) * n);
        }

        float Schlick(float cosine, float refIdx) const
        {
            float r0 = (1.0f - refIdx) / (1.0f + refIdx);
            r0 = r0 * r0;
            return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
        }
        //Convert local vector a to world vector according to provided normal n.
        glm::vec3 toWorld(const glm::vec3& a, const glm::vec3& n) const
        {
            glm::vec3 b, c;
            if (std::fabs(n.x) > std::fabs(n.y))
            {
                float inv_len = 1.0f / std::sqrt(n.x * n.x + n.z * n.z);
                c = glm::vec3(n.z * inv_len, 0.f, -n.x * inv_len);
            }
            else
            {
                float inv_len = 1.0f / std::sqrt(n.y * n.y + n.z * n.z);
                c = glm::vec3(0.0f, n.z * inv_len, -n.y * inv_len);
            }
            b = glm::cross(c, n);
            return a.x * b + a.y * c + a.z * n;
        }
    };

} // namespace platinum

#endif
