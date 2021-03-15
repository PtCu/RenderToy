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

#include "defines.h"
#include "object.h"
#include "ray.h"
#include "intersection.h"
#include "aabb.h"

namespace platinum
{
    struct BVH_Node
    {
        AABB bounding_box;
        std::shared_ptr<BVH_Node> left, right;
        std::shared_ptr<Object> object;
        BVH_Node() : bounding_box(AABB()), left(NULL), right(NULL), object(NULL) {}
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
        // BVHAccel Public Methods
        BVHAccel(std::vector<shared_ptr<Object>> &p, int maxPrimsInNode = 1, SplitMethod splitMethod = SplitMethod::MIDDLE);

        BVHAccel(std::vector<shared_ptr<Object>>::iterator &begin, std::vector<shared_ptr<Object>>::iterator &end, int maxPrimsInNode = 1, SplitMethod splitMethod = SplitMethod::MIDDLE);

        ~BVHAccel();

        Intersection RayCast(const Ray &ray) const;

        shared_ptr<BVH_Node> GetRoot() { return root; }

    protected:
        // BVHAccel Private Methods
        shared_ptr<BVH_Node> recursiveBuild(std::vector<shared_ptr<Object>>::iterator &begin, std::vector<shared_ptr<Object>>::iterator &end);

        Intersection getIntersection(const Ray &ray) const;
        // BVHAccel Private Data
        const int maxPrimsInNode;
        const SplitMethod splitMethod;
        shared_ptr<BVH_Node> root;
    };

}

#endif