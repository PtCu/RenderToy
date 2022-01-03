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

#include "dielectric.h"

namespace platinum
{
   Dielectric::Dielectric(float ri) : ref_idx_(ri) {}
   bool Dielectric::ComputeScatteringFunctions(HitRst &rst) const
   {
      glm::vec3 outward_normal;
      auto r_in = rst.record.ray;
      glm::vec3 reflected = Reflect(r_in.GetDirection(), rst.record.vert.normal_);
      float ni_over_nt;
      auto attenuation = glm::vec3(1.0, 1.0, 1.0);
      glm::vec3 refracted;
      float reflect_prob;
      float cosine;
      //From inner to outer
      if (glm::dot(r_in.GetDirection(), rst.record.vert.normal_) > 0)
      {
         outward_normal = -rst.record.vert.normal_;
         ni_over_nt = ref_idx_;
         cosine = glm::length(glm::dot(r_in.GetDirection(), rst.record.vert.normal_) / r_in.GetDirection());
         cosine = std::sqrt(1 - ref_idx_ * ref_idx_ * (1 - cosine * cosine));
      }
      //From outer to inner
      else
      {
         outward_normal = rst.record.vert.normal_;
         ni_over_nt = 1.0f / ref_idx_;
         cosine = -glm::length(glm::dot(r_in.GetDirection(), rst.record.vert.normal_) / r_in.GetDirection());
      }
      if (Refract(r_in.GetDirection(), outward_normal, ni_over_nt, refracted))
         reflect_prob = Schlick(cosine, ref_idx_);
      else
         reflect_prob = 1.0;

      if (Random::RandomInUnitFloat() < reflect_prob)
         r_in.Update(rst.record.vert.position_, reflected, attenuation);
      else
         r_in.Update(rst.record.vert.position_, refracted, attenuation);

      return true;
   }

   // Sample a ray by Material properties
   glm::vec3 Dielectric::Sample(const glm::vec3 &d, HitRst &rst) const
   {
      return glm::vec3(0, 0, 0);
   }
   //Given a ray, calculate the PdF of this ray
   float Dielectric::Pdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
   {
      return 0;
   }
   // brdf. Given a ray, calculate the contribution of this ray
   glm::vec3 Dielectric::ScatterPdf(const glm::vec3 &wi, const glm::vec3 &wo, HitRst &rst) const
   {
      return glm::vec3(0, 0, 0);
   }
   //The material_ itself emits light.
   glm::vec3 Dielectric::Emit() const
   {
      return glm::vec3(0, 0, 0);
   }
   bool Dielectric::IsEmit() const
   {
      return false;
   }
}