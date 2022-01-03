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

#include "isotropic.h"

namespace platinum
{
    Isotropic::Isotropic(const std::shared_ptr<Texture> &a) : texure_(a) {}

    bool Isotropic::ComputeScatteringFunctions(HitRst &rst) const
    {
        auto attenuation = texure_->GetValue(rst.record.vert.u_, rst.record.vert.v_, rst.record.vert.position_);
        rst.record.ray.Update(rst.record.vert.position_, Random::RandomInUnitSphere(), attenuation);
        return true;
    }
    // Sample a ray by Material properties
    glm::vec3 Isotropic::Sample(const glm::vec3 &d, HitRst &rst) const
    {
        return glm::vec3(0, 0, 0);
    }
    //Given a ray, calculate the PdF of this ray
    float Isotropic::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        return 0;
    }
    // brdf. Given a ray, calculate the contribution of this ray
    glm::vec3 Isotropic::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
    {
        return glm::vec3(0, 0, 0);
    }
    //The material_ itself emits light.
    glm::vec3 Isotropic::Emit() const
    {
        return glm::vec3(0, 0, 0);
    }
    bool Isotropic::IsEmit() const
    {
        return false;
    }

}