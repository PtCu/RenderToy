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
    Lambertian::Lambertian(const std::shared_ptr<Texture> &a) : albedo_(a) {}
    Lambertian::Lambertian(const glm::vec3 &a)
    {
        albedo_ = std::make_shared<ConstTexture>(a);
    }
    bool Lambertian::ComputeScatteringFunctions(HitRst &rst) const
    {
        auto reflected = glm::vec3(rst.record.vert.normal_) + Random::RandomInUnitSphere();
        auto attenuation = albedo_->GetValue(rst.record.vert.u_, rst.record.vert.v_, rst.record.vert.position_);
        rst.record.ray.Update(rst.record.vert.position_, reflected, attenuation);
        return true;
    }

    // sample a ray by Material properties
    glm::vec3 Lambertian::Sample(const glm::vec3 &d, HitRst &rst) const
    {
        // uniform sample on the hemisphere
        // See chapter 6.
        // x_1 is for phi, x_2 is for theta
        float x_1 = Random::RandomInUnitFloat(), x_2 = Random::RandomInUnitFloat();
        float cos_theta = std::fabs(1.0f - 2.0f * x_1);
        float r = std::sqrt(1.0f - cos_theta * cos_theta), phi = 2 * PI * x_2;
        glm::vec3 local_ray(r * std::cos(phi), r * std::sin(phi), cos_theta);
        return toWorld(local_ray, rst.record.vert.normal_);
    }
    // given a ray, calculate the PdF of this ray
    float Lambertian::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        float cosine = glm::dot(wo, rst.record.vert.normal_);
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
    glm::vec3 Lambertian::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        // calculate the contribution of diffuse model
        float cosalpha = glm::dot(rst.record.vert.normal_, wo);
        //出射方向和法线方程成钝角时，不在上半球面内，不计算
        if (cosalpha > 0.0f)
        {
            //f_r=albedo/PI
            auto attenuation = albedo_->GetValue(rst.record.vert.u_, rst.record.vert.v_, rst.record.vert.position_) / PI;
            return attenuation;
        }
        else
        {
            return glm::vec3(0.0f);
        }
    }
    glm::vec3 Lambertian::Emit() const
    {
        return glm::vec3(0, 0, 0);
    }
    bool Lambertian::IsEmit() const
    {
        return false;
    }

}