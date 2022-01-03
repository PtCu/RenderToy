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

#include "metal.h"

namespace platinum
{
    Metal::Metal(const std::shared_ptr<Texture> &a, float f) : albedo_(a)
    {
        f < 1 ? fuzz_ = f : fuzz_ = 1;
    }
    Metal::Metal(const glm::vec3 &a, float f)
    {
        albedo_ = std::make_shared<ConstTexture>(a);
        f < 1 ? fuzz_ = f : fuzz_ = 1;
    }

    bool Metal::ComputeScatteringFunctions(HitRst &rst) const
    {
        glm::vec3 reflected = Reflect(rst.record.ray.GetDirection(), rst.record.vert.normal_) + fuzz_ * Random::RandomInUnitSphere();
        if (glm::dot(reflected, rst.record.vert.normal_) < 0)
        {
            rst.record.ray.SetColor(glm::vec3(0, 0, 0));
            return false;
        }
        auto attenuation = albedo_->GetValue(rst.record.vert.u_, rst.record.vert.v_, rst.record.vert.position_);
        rst.record.ray.Update(rst.record.vert.position_, reflected, attenuation);
        return true;
    }
    // Sample a ray by Material properties
    glm::vec3 Metal::Sample(const glm::vec3 &d, HitRst &rst) const
    {
        return glm::vec3(0, 0, 0);
    }
    //Given a ray, calculate the PdF of this ray
    float Metal::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        return 0;
    }
    // brdf. Given a ray, calculate the contribution of this ray
    glm::vec3 Metal::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        return glm::vec3(0, 0, 0);
    }
    //The material_ itself emits light.
    glm::vec3 Metal::Emit() const
    {
        return glm::vec3(0, 0, 0);
    }
    bool Metal::IsEmit() const
    {
        return false;
    }
}
