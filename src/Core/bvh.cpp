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

#include "bvh.h"
#include "spdlog/spdlog.h"
#include <fstream>

using namespace std;
using namespace glm;
using namespace platinum;

BVHAccel::BVHAccel(vector<shared_ptr<Object>> &p,
                   SplitMethod splitMethod)
    : splitMethod(splitMethod)
{
    // time_t start, stop;
    // time(&start);
    if (p.empty())
        return;

    if (splitMethod == SplitMethod::HLBVH)
        ;
    else
        root = recursiveBuild(p.begin(), p.end());
    //TODO:
    //Other building method
}
BVHAccel::BVHAccel(vector<shared_ptr<Object>>::iterator &begin, vector<shared_ptr<Object>>::iterator &end,
                   SplitMethod splitMethod)
    : splitMethod(splitMethod)
{
    // time_t start, stop;
    // time(&start);
    if (begin == end)
        return;

    if (splitMethod == SplitMethod::HLBVH)
        ;
    else
        root = recursiveBuild(begin, end);
    //TODO:
    //Other building method
}

shared_ptr<BVH_Node> BVHAccel::recursiveBuild(vector<shared_ptr<Object>>::iterator begin, vector<shared_ptr<Object>>::iterator end)
{
    size_t num = end - begin;
    if (num == 0)
        return NULL;
    auto node = make_shared<BVH_Node>();
    // Compute bounding_box of all primitives in BVH node
    if (num == 1)
    {
        // Create leaf _BVHBuildNode_
        node->bounding_box = (*begin)->GetBoundingBox();
        node->objects = *begin;
        node->left = nullptr;
        node->right = nullptr;
        node->area = (*begin)->GetArea();
        return node;
    }
    else if (num == 2)
    {
        node->left = recursiveBuild(begin, begin + 1);
        node->right = recursiveBuild(begin + 1, end);
        node->bounding_box = Union(node->left->bounding_box, node->right->bounding_box);
        node->area = node->left->area + node->right->area;
        return node;
    }
    else
    {
        //Choose split dimension
        AABB centroidBounds;
        for (auto iter = begin; iter != end; ++iter)
            centroidBounds.Expand((*iter)->GetBoundingBox().Centroid());
        int dim = centroidBounds.MaxExtent();

        // if (centroidBounds.GetMax()[dim] == centroidBounds.GetMin()[dim])
        // {
        // }
        //Do partition according to split method
        std::vector<shared_ptr<Object>>::iterator middle;
        float p_mid = 0;
        switch (splitMethod)
        {
        case SplitMethod::MIDDLE:
            p_mid = centroidBounds.Centroid()[dim];
            middle = std::partition(begin, end,
                                    [dim, p_mid](auto p)
                                    { return p->GetBoundingBox().Centroid()[dim] < p_mid; });

            // //Edge case: if identical bounding boxes exist
            // if (middle - begin == 0)
            // {
            //     node->left = node->right = NULL;
            //     node->bounding_box = (*begin)->GetBoundingBox();
            // for (auto &iter = begin; iter != end; ++iter)
            // {
            //     node->objects.push_back(*iter);
            // }
            //     node->objects = *begin;
            //     return node;
            // }
            break;
        case SplitMethod::SAH:
            break;
        default:
            break;
        }
        node->left = recursiveBuild(begin, middle);
        node->right = recursiveBuild(middle, end);
        node->bounding_box = Union(node->left->bounding_box, node->right->bounding_box);
        node->area = node->left->area + node->right->area;
    }

    return node;
}

Intersection BVHAccel::RayCast(std::shared_ptr<Ray> &r) const
{
    Intersection isect;
    // isect = BVHAccel::getIntersection(r);
    isect = BVHAccel::getIntersection_rec(root, r);
    return isect;
}
Intersection BVHAccel::getIntersection_rec(std::shared_ptr<BVH_Node> node, std::shared_ptr<Ray> &r) const
{
    // TODO Traverse the BVH to find intersection
    //如果和盒子没相交，就必不可能和盒子内的物体相交
    if (!node->bounding_box.IsHit(r))
        return Intersection();

    if (!node->left && !node->right)
    {
        return node->objects->Intersect(r);
        // Intersection tmp_inter, inter;
        // for (auto &obj : node->objects)
        // {
        //     tmp_inter = obj->Intersect(r);

        //     if (tmp_inter.happened && (inter.happened == false || tmp_inter.ray->GetMaxTime() < inter.ray->GetMaxTime()))
        //     {
        //         // inter = std::move(tmp_inter);
        //         inter = tmp_inter;
        //     }
        // }
        // return inter;
    }

    Intersection hit1, hit2;
    hit1 = getIntersection_rec(node->left, r);
    hit2 = getIntersection_rec(node->right, r);
    if (!hit1.happened)
    {
        return hit2;
    }
    else if (!hit2.happened)
    {
        return hit1;
    }
    else
    {
        return hit1.ray->GetMaxTime() < hit2.ray->GetMaxTime() ? hit1 : hit2;
    }
}
Intersection BVHAccel::getIntersection(std::shared_ptr<Ray> &r) const
{
    // TODO Traverse the BVH to find intersection
    if (!root->bounding_box.IsHit(r))
        return Intersection();
    Intersection inter, tmp_inter;
    stack<shared_ptr<BVH_Node>> s;
    s.push(root);
    while (!s.empty())
    {
        //如果单独为unqiue_ptr就会被自动释放掉。可以用unique_ptr + raw pointer
        auto p = s.top();
        s.pop();
        if (p == NULL)
            continue;
        if (!p->bounding_box.IsHit(r))
            continue;
        if (p->left == NULL && p->right == NULL)
        {
            tmp_inter = p->objects->Intersect(r);
            if (tmp_inter.happened && (inter.happened == false || tmp_inter.ray->GetMaxTime() < inter.ray->GetMaxTime()))
            {
                // inter = std::move(tmp_inter);
                inter = tmp_inter;
            }
        }

        if (p->right)
            s.push(p->right);
        if (p->left)
            s.push(p->left);
    }
    return inter;
}

void BVHAccel::Sample(Intersection &inter, float &pdf) const
{
    float p = std::sqrt(Random::RandomInUnitFloat()) * root->area;
    getSample(root, p, inter, pdf);
    pdf /= root->area;
}
void BVHAccel::getSample(std::shared_ptr<BVH_Node> node, float p, Intersection &pos, float &pdf) const
{
    if (node->left == nullptr || node->right == nullptr)
    {
        node->objects->Sample(pos, pdf);
        pdf *= node->area;
        return;
    }
    if (p < node->left->area)
        getSample(node->left, p, pos, pdf);
    else
        getSample(node->right, p - node->left->area, pos, pdf);
}
// BVH_Node::BVH_Node(vector<shared_ptr<Object>> &objects)
// {
//     if (objects.size() == 0)
//         return;
//     Build(objects.begin(), objects.end());
// }
// BVH_Node::BVH_Node(std::vector<std::shared_ptr<Object>>::iterator begin, std::vector<std::shared_ptr<Object>>::iterator end)
// {
//     Build(begin, end);
// }
// void BVH_Node::Build(std::vector<std::shared_ptr<Object>>::iterator begin,std::vector<std::shared_ptr<Object>>::iterator end)
// {
//     size_t num = end - begin;

//     if (num == 1)
//     {
//         left = *begin;
//         right = NULL;
//         bounding_box = left->GetBoundingBox();
//         return;
//     }
//     if (num == 2)
//     {
//         left = *begin;
//         right = *(begin + 1);
//         bounding_box = Union(left->GetBoundingBox(), right->GetBoundingBox());
//         return;
//     }
//     for (auto iter = begin; iter != end; ++iter)
//     {
//         bounding_box.Expand((*iter)->GetBoundingBox());
//     }
//     int dim = bounding_box.MaxExtent();
//     switch (dim)
//     {
//     case 0:
//         std::sort(begin, end, [](auto f1, auto f2) {
//             return (*f1)->GetBounds().Centroid().x <
//                    (*f2)->GetBounds().Centroid().x;
//         });
//         break;
//     case 1:
//         std::sort(begin, end, [](auto f1, auto f2) {
//             return (*f1)->GetBounds().Centroid().y <
//                    (*f2)->GetBounds().Centroid().y;
//         });
//         break;
//     case 2:
//         std::sort(begin, end, [](auto f1, auto f2) {
//             return (*f1)->GetBounds().Centroid().z <
//                    (*f2)->GetBounds().Centroid().z;
//         });
//         break;
//     }

//     auto middle = begin + (end - begin) / 2;
//     left = make_shared<BVH_Node>(begin, middle);
//     right = make_shared<BVH_Node>(middle, end);

// }
