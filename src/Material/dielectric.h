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

#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "core/material.h"
#include "math/rand.h"
#include "core/texture.h"
namespace platinum
{
   class Dielectric : public Material
   {
   public:
      Dielectric(float ri);
      virtual bool Scatter(HitRst& rst) const;
      // Sample a ray by Material properties
      virtual glm::vec3 Sample(const glm::vec3& d, HitRst& rst) const;
      //Given a ray, calculate the PdF of this ray
      virtual float Pdf(const glm::vec3& wi, const glm::vec3& wo, HitRst& rst) const;
      // brdf. Given a ray, calculate the contribution of this ray
      virtual glm::vec3 ScatterPdf(const glm::vec3& wi, const glm::vec3& wo, HitRst& rst) const;
      //The material_ itself emits light.
      virtual glm::vec3 Emit() const;
      virtual bool IsEmit() const;

   private:
      std::shared_ptr<Texture> _albedo;
      //ref_idx: 物体外部介质的折射率η和物体内部折射率η'之比：η/η'。
      float _ref_idx;
   };

} // namespace platinum

#endif
