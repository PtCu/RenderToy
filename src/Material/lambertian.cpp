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
    glm::vec3 Lambertian::Sample(const glm::vec3 &wi, const glm::vec3 &wo,Intersection&rec) const
    {
        // uniform sample on the hemisphere
        // See chapter 6.
        // x_1 is for phi, x_2 is for theta
        float x_1 = Random::RandomInUnitFloat(), x_2 = Random::RandomInUnitFloat();
        float cos_theta = std::fabs(1.0f - 2.0f * x_1);
        float r = std::sqrt(1.0f - cos_theta * cos_theta), phi = 2 * PI * x_2;
        glm::vec3 local_ray(r * std::cos(phi), r * std::sin(phi), cos_theta);
        return toWorld(local_ray, rec.vert.normal);
    }
    // given a ray, calculate the PdF of this ray
    float Lambertian::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection&rec) const
    {
        float cosine = glm::dot(wo, rec.vert.normal);
        if (cosine > 0.0f)
        {
            return cosine / PI;
        }
        else
        {
            return 0.0f;
        }
    }
    // given a ray, calculate the contribution of this ray
    glm::vec3 Lambertian::ScatterPdf(const glm::vec3 &wi,const glm::vec3 &wo, Intersection&rec) const
    {
        // calculate the contribution of diffuse model
        float cosalpha = glm::dot(rec.vert.normal, wo);
        if (cosalpha > 0.0f)
        {
            //f_r=albedo/PI
            auto attenuation = albedo->GetValue(rec.vert.u, rec.vert.v, rec.vert.pos) / PI;
            return attenuation;
        }
        else
        {
            return glm::vec3(0.0f);
        }
    }

}