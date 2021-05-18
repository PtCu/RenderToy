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

#ifndef MATERIAL_LIGHT_H_
#define MATERIAL_LIGHT_H_

#include "../Core/material.h"
#include "../Math/rand.h"
#include "../Core/texture.h"
#include "../Texture/constTexture.h"

namespace platinum
{
    class Light : public Material
    {
    public:
        Light(const glm::vec3 &color, float linear = 0.0f, float quadratic = 0.0f);
        Light(std::shared_ptr<Texture> lightTex, float linear = 0.0f, float quadratic = 0.0f);
        virtual bool Scatter(Intersection &rec) const;
        // Sample a ray by Material properties
        virtual glm::vec3 Sample(const glm::vec3 &d, Intersection &rec) const;
        //Given a ray, calculate the PdF of this ray
        virtual float Pdf(const glm::vec3 &wi, const glm::vec3 &wo, const glm::vec3 &N) const;
        // brdf. Given a ray, calculate the contribution of this ray
        virtual glm::vec3 ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, const glm::vec3 &N) const;
        //The material itself emits light.
        virtual glm::vec3 Emit() const;
        virtual bool IsEmit() const;

    private:
        std::shared_ptr<Texture> tex;
        float linear;
        float quadratic;
    };

} // namespace platinum

#endif