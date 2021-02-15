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

#ifndef CORE_MATERIAL_H_
#define CORE_MATERIAL_H_

#include "ray.h"
#include "intersection.h"
#include "../Math/vector.h"
namespace platinum
{
    class Material
    {
    public:
        virtual bool Scatter(const Ray &r_in, const Intersection &rec, glm::vec3 &attenuation, Ray &scattered) const = 0;

    protected:
        /**
         * @brief 
         * @param  v                Incident light. 
         * @param  n                Normal.
         * @param  ni_over_nt       Refractive index, 
         * @param  refracted        Emergent light.
         * @return true 
         * @return false 
         */
        bool Refract(const glm::vec3 &v, const glm::vec3 &n, PFloat ni_over_nt, glm::vec3 &refracted) const
        {
            glm::vec3 uv = v.Normalized();
            PFloat dt = Dot(uv, n);
            PFloat discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
            if (discriminant > 0)
            {
                refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
                return true;
            }
            else
                return false;
        }

        glm::vec3 Reflect(const glm::vec3 &v, const glm::vec3 &n) const
        {
            return glm::vec3(v - 2 * Dot(v, n) * n);
        }

        PFloat Schlick(PFloat cosine, PFloat refIdx) const
        {
            PFloat r0 = (1 - refIdx) / (1 + refIdx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
    };

} // namespace platinum

#endif
