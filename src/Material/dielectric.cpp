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

namespace platinum{
    bool Dielectric:: Scatter(const Ray &r_in, const Intersection &rec, glm::vec3 &attenuation, Ray &scattered) const
      {
         glm::vec3 outward_normal;
         glm::vec3 reflected = Reflect(r_in.GetDirection(), rec.normal);
         PFloat ni_over_nt;
         attenuation = glm::vec3(1.0, 1.0, 1.0);
         glm::vec3 refracted;
         PFloat reflect_prob;
         PFloat cosine;
         if (glm::dot(r_in.GetDirection(), rec.normal) > 0)
         {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            // cosine = ref_idx * glm::dot(r_in.GetDirection(), rec.normal) / r_in.GetDirection().length();
            cosine = glm::dot(r_in.GetDirection(), rec.normal) / r_in.GetDirection().length();
            cosine = std::sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
         }
         else
         {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -glm::dot(r_in.GetDirection(), rec.normal) / r_in.GetDirection().length();
         }
         if (Refract(r_in.GetDirection(), outward_normal, ni_over_nt, refracted))
            reflect_prob = Schlick(cosine, ref_idx);
         else
            reflect_prob = 1.0;
         if (Random::RandomInUnitFloat() < reflect_prob)
            scattered = Ray(rec.point, reflected);
         else
            scattered = Ray(rec.point, refracted);
         return true;
      }
}