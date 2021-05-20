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
    Metal::Metal(const std::shared_ptr<Texture> &a, float f) : albedo(a)
    {
        f < 1 ? fuzz = f : fuzz = 1;
    }
    Metal::Metal(const glm::vec3 &a, float f)
    {
        albedo = std::make_shared<ConstTexture>(a);
        f < 1 ? fuzz = f : fuzz = 1;
    }

    bool Metal::Scatter(Intersection &rec) const
    {
        glm::vec3 reflected = Reflect(rec.ray->GetDirection(), rec.vert.normal) + fuzz * Random::RandomInUnitSphere();
        if (glm::dot(reflected, rec.vert.normal) < 0)
        {
            rec.ray->SetColor(glm::vec3(0, 0, 0));
            return false;
        }
        auto attenuation = albedo->GetValue(rec.vert.u, rec.vert.v, rec.vert.pos);
        rec.ray->Update(rec.vert.pos, reflected, attenuation);
        return true;
    }
    // Sample a ray by Material properties
    glm::vec3 Metal::Sample(const glm::vec3 &d, Intersection &rec) const
    {
        return glm::vec3(0, 0, 0);
    }
    //Given a ray, calculate the PdF of this ray
    float Metal::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection &rec) const
    {
        return 0;
    }
    // brdf. Given a ray, calculate the contribution of this ray
    glm::vec3 Metal::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection &rec) const
    {
        return glm::vec3(0, 0, 0);
    }
    //The material itself emits light.
    glm::vec3 Metal::Emit() const
    {
        return glm::vec3(0, 0, 0);
    }
    bool Metal::IsEmit() const
    {
        return false;
    }
}
