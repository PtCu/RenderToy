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

#ifndef CORE_WORLD_H_
#define CORE_WORLD_H_

#include "object.h"
#include <glm/glm.hpp>
#include "defines.h"
#include "ray.h"
#include "intersection.h"
#include "bvh.h"

namespace platinum
{
    class World
    {
    public:
        World() {}
        bool IntersectAll(const Ray &r, Intersection &rec) const;  //Brute method for stage 1
        void AddObject(std::shared_ptr<Object> obj);
        void DestroyAll();
        void BuildBVH();
        glm::vec3 CastRay(const Ray &ray,int depth) const; //Using BVH tree to accelerate.
        const std::vector<std::shared_ptr<Object>> &GetObjects() const { return objects; }

    private:
        int max_depth = 10;
        Intersection intersectAll(const Ray &ray) const;
        std::unique_ptr<BVHAccel> bvh_accel;
        std::vector<std::shared_ptr<Object>> objects;
    };

} // namespace platinum

#endif
