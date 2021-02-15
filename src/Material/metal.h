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

#include "../Core/material.h"
#include "../Math/rand.h"
namespace platinum
{
   class Metal : public Material
   {
   public:
      Metal(const glm::vec3 &a, PFloat f) : albedo(a)
      {
         f < 1 ? fuzz = f : fuzz = 1;
      }
      virtual bool Scatter(const Ray &r_in, const Intersection &rec, glm::vec3 &attenuation, Ray &scattered) const
      {
         glm::vec3 reflected = Reflect(r_in.GetDirection(), rec.normal);
         scattered = Ray(rec.point, reflected + fuzz * Random::RandomInUnitSphere());
         attenuation = albedo;
         return (glm::dot(scattered.GetDirection(), rec.normal) > 0);
      }
      glm::vec3 albedo;
      PFloat fuzz; //Zero is no perturbation
   };
} // namespace platinum

#endif