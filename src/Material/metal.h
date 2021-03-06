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

#ifndef METAL_H
#define METAL_H
#include "../Math/rand.h"
#include "../Core/material.h"
#include "../Core/texture.h"
#include "../Texture/constTexture.h"

namespace platinum
{
   class Metal : public Material
   {
   public:
      Metal(const std::shared_ptr<Texture> &a, float f);
      Metal(const glm::vec3 &a, float f);

      bool Scatter(Intersection &rec) const final;
      // Sample a ray by Material properties
      glm::vec3 Sample(const glm::vec3 &d, Intersection &rec) const override;
      //Given a ray, calculate the PdF of this ray
      float Pdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection &rec) const override;
      // brdf. Given a ray, calculate the contribution of this ray
      glm::vec3 ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, Intersection &rec) const override;
      //The material itself emits light.
      glm::vec3 Emit() const override;
      bool IsEmit() const override;

   private:
      std::shared_ptr<Texture> albedo;
      float fuzz; //Zero is no perturbation
   };
} // namespace platinum

#endif