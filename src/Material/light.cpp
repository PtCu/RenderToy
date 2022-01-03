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

#include "light.h"

namespace platinum
{
    MaterailLight::MaterailLight(const glm::vec3 &color_, float linear, float quadratic)
        : texure_(std::make_shared<ConstTexture>(color_)), linear_(linear), quadratic_(quadratic) {}

    MaterailLight::MaterailLight(std::shared_ptr<Texture> lightTex, float linear, float quadratic)
        : texure_(lightTex), linear_(linear), quadratic_(quadratic) {}

    bool MaterailLight::ComputeScatteringFunctions(HitRst &rst) const
    {
        float d = rst.record.ray.GetMaxTime() * glm::length(rst.record.ray.GetDirection());
        float attDis;
        if (linear_ == 0.0 && quadratic_ == 0.0)
            attDis = 1;
        else
        {
            if (std::isnan(d))
                attDis = 0;
            else
                attDis = 1.0f / (1.0f + d * (linear_ + quadratic_ * d));
        }
        float attAngle = abs(glm::dot(glm::normalize(rst.record.ray.GetDirection()), rst.record.vert.normal_));
        rst.record.ray.SetColor(attDis * attAngle * texure_->GetValue(rst.record.vert.u_, rst.record.vert.v_, rst.record.vert.position_));
        return false;
    }
    glm::vec3 MaterailLight::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        return glm::vec3(0, 0, 0);
    }
    // Sample a ray by Material properties
    glm::vec3 MaterailLight::Sample(const glm::vec3 &d, HitRst &rst) const
    {
        return glm::vec3(0, 0, 0);
    }
    //Given a ray, calculate the PdF of this ray
    float MaterailLight::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        return 0;
    }
    //The material_ itself emits light.
    glm::vec3 MaterailLight::Emit() const
    {
        return texure_->GetValue(0, 0, glm::vec3(0));
    }
    bool MaterailLight::IsEmit() const
    {
        return true;
    }
}
