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
   bool Dielectric::Scatter(Intersection &rec) const
   {
      glm::vec3 outward_normal;
      auto r_in = rec.ray;
      glm::vec3 reflected = Reflect(r_in->GetDirection(), rec.vert.normal);
      float ni_over_nt;
      auto attenuation = glm::vec3(1.0, 1.0, 1.0);
      glm::vec3 refracted;
      float reflect_prob;
      float cosine;
      //From inner to outer
      if (glm::dot(r_in->GetDirection(), rec.vert.normal) > 0)
      {
         outward_normal = -rec.vert.normal;
         ni_over_nt = ref_idx;
         cosine = glm::dot(r_in->GetDirection(), rec.vert.normal) / r_in->GetDirection().length();
         cosine = std::sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
      }
      //From outer to inner
      else
      {
         outward_normal = rec.vert.normal;
         ni_over_nt = 1.0f / ref_idx;
         cosine = -glm::dot(r_in->GetDirection(), rec.vert.normal) / r_in->GetDirection().length();
      }
      if (Refract(r_in->GetDirection(), outward_normal, ni_over_nt, refracted))
         reflect_prob = Schlick(cosine, ref_idx);
      else
         reflect_prob = 1.0;

      if (Random::RandomInUnitFloat() < reflect_prob)
         r_in->Update(rec.vert.pos, reflected, attenuation);
      else
         r_in->Update(rec.vert.pos, refracted, attenuation);

      return true;
   }
}