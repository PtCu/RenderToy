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
#include <functional>
#include "math/rand.h"
namespace platinum
{
    class Scene
    {
    public:
        Scene() : _max_depth(10), _use_default_light(true), _RussianRoulette(0.8f) {}
        Scene(bool use_default_light, bool use_path_tracer) : _max_depth(10), _use_default_light(use_default_light), _use_path_tracer(use_path_tracer), _RussianRoulette(0.8f) {}
        ~Scene();
        void AddObject(const std::shared_ptr<Object>& obj);
        void AddObject(const std::vector<std::shared_ptr<Object>>& obj);
        void AddObject(const std::vector<std::shared_ptr<Object>>::iterator& begin, const std::vector<std::shared_ptr<Object>>::iterator& end);
        void Reset();
        void BuildBVH();
        glm::vec3 CastRay(std::shared_ptr<Ray>& r) const;
        const std::vector<std::shared_ptr<Object>>& GetObjects() const { return _objects; }

    private:
        void destroyAll();
        glm::vec3 castRayPath(std::shared_ptr<Ray>& r) const;
        glm::vec3 castRayWhitted(std::shared_ptr<Ray>& r, int depth) const; //Using BVH tree to accelerate.
        HitRst intersectAll(std::shared_ptr<Ray>& r) const;
        void sampleLight(HitRst& inter, float& pdf) const;
        int _max_depth;
        std::unique_ptr<BVHAccel> _bvh_accel;
        std::vector<std::shared_ptr<Object>> _objects;
        bool _use_default_light, _use_path_tracer;
        float _RussianRoulette;
    };

} // namespace platinum

#endif
