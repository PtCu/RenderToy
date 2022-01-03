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

#include <core/object.h>
#include <glm/glm.hpp>
#include <core/defines.h>
#include <core/ray.h>
#include <core/intersection.h>
#include <core/bvh.h>
#include <functional>
#include <math/rand.h>
#include <core/light.h>
namespace platinum
{
    class Scene
    {
    public:
        Scene() : max_depth_(10), default_light(true), RussianRoulette(0.8) {}
        Scene(bool d_l, int _mode = 0) : max_depth_(10), default_light(d_l), mode(_mode), RussianRoulette(0.8) {}
        ~Scene();
        void AddObject(const std::shared_ptr<Object>& obj);
        void AddObject(const std::vector<std::shared_ptr<Object>>& obj);
        void AddObject(const std::vector<std::shared_ptr<Object>>::iterator& begin, const std::vector<std::shared_ptr<Object>>::iterator& end);
        void Reset();
        void BuildBVH();
        HitRst Hit(const Ray& r) const;
        glm::vec3 CastRay(const Ray& r) const;
        const std::vector<std::shared_ptr<Object>>& GetObjects() const { return objects_; }

        std::vector<std::shared_ptr<Light>>_lights;

    private:
        void destroyAll();
        glm::vec3 castRayPdf(const Ray& r) const;
        glm::vec3 castRay(const Ray& r, int depth) const; //Using BVH tree to accelerate.

        void sampleLight(HitRst& inter, float& pdf) const;
        int max_depth_;
        std::unique_ptr<BVHAccel> bvh_accel_;
        std::vector<std::shared_ptr<Object>> objects_;
        bool default_light;
        float RussianRoulette;
        int mode;
    };

} // namespace platinum

#endif
