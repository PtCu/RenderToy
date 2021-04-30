// The MIT License (MIT)

// Copyright (c) YEAR NAME

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

#include "lambertian.h"
namespace platinum
{
    bool Lambertian::Scatter(Intersection &rec) const
    {
        auto reflected = glm::vec3(rec.vert.normal) + Random::RandomInUnitSphere();
        auto attenuation = albedo->GetValue(rec.vert.u, rec.vert.v, rec.vert.pos);
        rec.ray->Update(rec.vert.pos, reflected, attenuation);
        return true;
    }
    // sample a ray by Material properties
    glm::vec3 Lambertian::sample(const glm::vec3 &wi, const glm::vec3 &N)
    {
         // uniform sample on the hemisphere
         float x_1 = Random::RandomInUnitFloat(), x_2 = Random::RandomInUnitFloat();
         float z = std::fabs(1.0f - 2.0f * x_1);
         float r = std::sqrt(1.0f - z * z), phi = 2 * PI * x_2;
         glm::vec3 locay_ray(r * std::cos(phi), r * std::sin(phi), z);
         
    }
    // given a ray, calculate the PdF of this ray
    float Lambertian::pdf(const glm::vec3 &wi, const glm::vec3 &wo, const glm::vec3 &N)
    {
        float cosine = glm::dot(wo, N);
        if (cosine > 0.0f)
        {
            return 0.5f / PI;
        }
        else
        {
            return 0.0f;
        }
    }
    // given a ray, calculate the contribution of this ray
    glm::vec3 Lambertian::eval(const glm::vec3 &wi, const glm::vec3 &wo, const glm::vec3 &N)
    {
        // calculate the contribution of diffuse   model
        float cosalpha = glm::dot(N, wo);
        if (cosalpha > 0.0f)
        {
        }
        else
        {
            return glm::vec3(0.0f);
        }
    }

}