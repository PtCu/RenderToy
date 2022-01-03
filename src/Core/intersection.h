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

#ifndef CORE_INTERSECTION_H_
#define CORE_INTERSECTION_H_
#include <glm/glm.hpp>
#include <core/defines.h>
#include <core/material.h>
#include <core/ray.h>
#include <geometry/vertex.h>
#include <core/bsdf.h>
namespace platinum
{
    struct HitRecord
    {
    public:

        HitRecord() = default;
       
        HitRecord(const Ray& _ray, const glm::vec3& pos = glm::vec3(0),
            const glm::vec3& normal = glm::vec3(0, 0, 1), float u = 0, float v = 0) : ray(_ray), vert(pos, normal, u, v) {}
        Ray ray;
        Vertex vert;
    };

    struct HitRst
    {
    public:
        explicit HitRst(bool hit = false) : is_hit(hit), material(NULL) {}
        bool is_hit;
        glm::vec3 emit;
        HitRecord record;
        std::shared_ptr<const Material> material;
        HitRst& operator=(const HitRst& e) {
            return *this;
        }
        static const HitRst InValid;
    };

    class Interaction {
    public:
        Interaction() = default;
        explicit Interaction(const glm::vec3& p) : p(p) {}
        Interaction(const glm::vec3& p, const glm::vec3& wo) : p(p), wo(normalize(wo)) {}
        Interaction(const glm::vec3& p, const glm::vec3& n, const glm::vec3& wo)
            : p(p), wo(glm::normalize(wo)), n(n) {}

        inline Ray spawnRay(const glm::vec3& d) const
        {
            glm::vec3 o = p;
            return Ray(o, d, std::numeric_limits<float>::max());
        }

        inline Ray spawnRayTo(const glm::vec3& p2) const
        {
            glm::vec3 origin = p;
            return Ray(origin, p2 - p, 1.f - ShadowEpsilon);
        }

        inline Ray spawnRayTo(const Interaction& it) const
        {
            glm::vec3 origin = p;
            glm::vec3 target = it.p;
            glm::vec3 d = target - origin;
            return Ray(origin, d, 1.f - ShadowEpsilon);
        }


        glm::vec3 p;			//surface point
        glm::vec3 wo;			//outgoing direction
        glm::vec3 n;			//normal vector
    };

    class SurfaceInteraction final : public Interaction
    {
    public:
        SurfaceInteraction() = default;
        SurfaceInteraction(const glm::vec3& p, const glm::vec2& uv, const glm::vec3& wo,
            const glm::vec3& dpdu, const glm::vec3& dpdv);

        glm::vec3 Le(const glm::vec3& w) const;

        void computeScatteringFunctions(const Ray& ray,
            bool allowMultipleLobes = false);


        BSDF* bsdf{ nullptr };
        glm::vec2 uv;
        glm::vec3 dpdu, dpdv;


    };
}
#endif
