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

#ifndef CORE_BVH_H_
#define CORE_BVH_H_

#include <core/defines.h>
#include <core/object.h>
#include <core/intersection.h>
#include <core/aabb.h>
#include <math/rand.h>

namespace platinum
{
    struct BVH_Node
    {
        AABB bounding_box;
        std::shared_ptr<BVH_Node> left, right;
        std::shared_ptr<Object> objects;
        float area;
        BVH_Node() : bounding_box(AABB()), left(NULL), right(NULL), area(0) {}
    };

    class BVHAccel
    {
    public: // BVHAccel Public Types
        enum class SplitMethod
        {
            MIDDLE,
            SAH,
            HLBVH
        };
        explicit BVHAccel(SplitMethod sm = SplitMethod::MIDDLE) : split_method_(sm) {}
        // BVHAccel Public Methods
        BVHAccel(std::vector<std::shared_ptr<Object>>& p, SplitMethod split_method_ = SplitMethod::MIDDLE);
        BVHAccel(std::vector<std::shared_ptr<Object>>::iterator& begin, std::vector<std::shared_ptr<Object>>::iterator& end, SplitMethod split_method_ = SplitMethod::MIDDLE);
        ~BVHAccel() = default;
        HitRst RayCast(const Ray& r) const;
        std::shared_ptr<BVH_Node> GetRoot() { return root_; }
        void Sample(HitRst& inter, float& pdf) const;

    protected:
        // BVHAccel Private Methods
        std::shared_ptr<BVH_Node> recursiveBuild(std::vector<std::shared_ptr<Object>>::iterator begin, std::vector<std::shared_ptr<Object>>::iterator end);
        HitRst getIntersection_rec(std::shared_ptr<BVH_Node> node, const Ray& r) const;
        HitRst getIntersection(const Ray& r) const;
        void getSample(std::shared_ptr<BVH_Node> node, float p, HitRst& pos, float& pdf) const;
        // BVHAccel Private Data
        const SplitMethod split_method_;
        std::shared_ptr<BVH_Node> root_;
    };

}
#endif