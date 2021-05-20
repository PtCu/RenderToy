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
    Light::Light(const glm::vec3 &color, float linear, float quadratic)
        : tex(std::make_shared<ConstTexture>(color)), linear(linear), quadratic(quadratic) {}

    Light::Light(std::shared_ptr<Texture> lightTex, float linear, float quadratic)
        : tex(lightTex), linear(linear), quadratic(quadratic) {}

    bool Light::Scatter(Intersection &rec) const
    {
        float d = rec.ray->GetMaxTime() * glm::length(rec.ray->GetDirection());
        float attDis;
        if (linear == 0.0 && quadratic == 0.0)
            attDis = 1;
        else
        {
            if (isnan(d))
                attDis = 0;
            else
                attDis = 1.0f / (1.0f + d * (linear + quadratic * d));
        }
        float attAngle = abs(glm::dot(glm::normalize(rec.ray->GetDirection()), rec.vert.normal));
        rec.ray->SetColor(attDis * attAngle * tex->GetValue(rec.vert.u, rec.vert.v, rec.vert.pos));
        return false;
    }
    glm::vec3 Light::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection &rec) const
    {
        return glm::vec3(0, 0, 0);
    }
    // Sample a ray by Material properties
    glm::vec3 Light::Sample(const glm::vec3 &d, Intersection &rec) const
    {
        return glm::vec3(0, 0, 0);
    }
    //Given a ray, calculate the PdF of this ray
    float Light::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection &rec) const
    {
        return 0;
    }
    //The material itself emits light.
    glm::vec3 Light::Emit() const
    {
        return tex->GetValue(0, 0, glm::vec3(0));
    }
    bool Light::IsEmit() const
    {
        return true;
    }
}
