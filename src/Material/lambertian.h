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

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../Core/material.h"
#include "../Math/rand.h"
#include "../Core/texture.h"
#include "../Texture/constTexture.h"

namespace platinum
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const std::shared_ptr<Texture> &a) : albedo(a) {}
        Lambertian(const glm::vec3 &a)
        {
            albedo = std::make_shared<ConstTexture>(a);
        }
        virtual bool Scatter(Intersection &rec) const;
          // sample a ray by Material properties
        virtual glm::vec3 Sample(const glm::vec3 &wi, const glm::vec3 &N)=0;
        // given a ray, calculate the PdF of this ray
        virtual float Pdf(const glm::vec3 &wo, Intersection &rec)=0;
        // given a ray, calculate the contribution of this ray
        virtual glm::vec3 Eval(const glm::vec3 &wo, Intersection &rec)=0;
    private:
        std::shared_ptr<Texture> albedo;
    };
} // namespace platinum

#endif
