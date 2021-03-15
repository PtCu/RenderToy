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

using namespace std;
using namespace glm;
namespace platinum
{

    BVHAccel::BVHAccel(std::vector<shared_ptr<Object>> &p, int maxPrimsInNode,
                       SplitMethod splitMethod)
        : maxPrimsInNode(std::min(255, maxPrimsInNode)), splitMethod(splitMethod)
    {
        time_t start, stop;
        time(&start);
        if (p.empty())
            return;

        if (splitMethod == SplitMethod::HLBVH)
            ;
        else
            root = recursiveBuild(p.begin(), p.end());
        //TODO:
        //Other building method

        time(&stop);
        double diff = difftime(stop, start);
        int hrs = (int)diff / 3600;
        int mins = ((int)diff / 60) - (hrs * 60);
        int secs = (int)diff - (hrs * 3600) - (mins * 60);

        printf(
            "\rBVH Generation complete: \nTime Taken: %i hrs, %i mins, %i secs\n\n",
            hrs, mins, secs);
    }
    BVHAccel::BVHAccel(std::vector<shared_ptr<Object>>::iterator &begin, std::vector<shared_ptr<Object>>::iterator &end, int maxPrimsInNode,
                       SplitMethod splitMethod)
        : maxPrimsInNode(std::min(255, maxPrimsInNode)), splitMethod(splitMethod)
    {
        time_t start, stop;
        time(&start);
        if (begin == end)
            return;

        if (splitMethod == SplitMethod::HLBVH)
            ;
        else
            root = recursiveBuild(begin, end);
        //TODO:
        //Other building method

        time(&stop);
        double diff = difftime(stop, start);
        int hrs = (int)diff / 3600;
        int mins = ((int)diff / 60) - (hrs * 60);
        int secs = (int)diff - (hrs * 3600) - (mins * 60);

        printf(
            "\rBVH Generation complete: \nTime Taken: %i hrs, %i mins, %i secs\n\n",
            hrs, mins, secs);
    }

    shared_ptr<BVH_Node> BVHAccel::recursiveBuild(std::vector<shared_ptr<Object>>::iterator &begin, std::vector<shared_ptr<Object>>::iterator &end)
    {
        size_t num = end - begin;
        auto node = make_shared<BVH_Node>();

        // Compute bounding_box of all primitives in BVH node
        if (num == 1)
        {
            // Create leaf _BVHBuildNode_
            node->bounding_box = (*begin)->GetBoundingBox();
            node->object = (*begin);
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
        else if (num == 2)
        {
            node->left = recursiveBuild(begin, begin + 1);
            node->right = recursiveBuild(begin + 1, end);
            node->bounding_box = Union(node->left->bounding_box, node->right->bounding_box);
            return node;
        }
        else
        {
            //Choose split dimension
            AABB centroidBounds;
            for (auto iter = begin; iter != end; ++iter)
                centroidBounds.Expand((*iter)->GetBoundingBox().Centroid());
            int dim = centroidBounds.MaxExtent();

            //TODO:
            //Edge case: if identical bounding boxes exist

            //Do partition according to split method
            std::vector<shared_ptr<Object>>::iterator middle;
            switch (splitMethod)
            {
            case SplitMethod::MIDDLE:
                auto p_mid = centroidBounds.Centroid()[dim];
                middle = std::partition(begin, end,
                                        [dim, p_mid](auto p) {
                                            return p->GetBounds().Centroid()[dim] < pmid;
                                        });

                break;
            case SplitMethod::SAH:
                break;
            default:
                break;
            }

            node->left = recursiveBuild(begin, middle);
            node->right = recursiveBuild(middle, end);
            node->bounding_box = Union(node->left->bounding_box, node->right->bounding_box);
        }

        return node;
    }

    Intersection BVHAccel::RayCast(const Ray &ray) const
    {
        Intersection isect;
        if (!root)
            return isect;
        isect = BVHAccel::getIntersection(ray);
        return isect;
    }

    Intersection BVHAccel::getIntersection(const Ray &ray) const
    {
        // TODO Traverse the BVH to find intersection
        if (!root->bounding_box.IsHit(ray))
            return Intersection();
        Intersection inter, tmp_inter;
        stack<shared_ptr<BVH_Node>> s;
        s.push(root);
        while (!s.empty())
        {
            auto p = s.top();
            s.pop();
            if (!p->bounding_box.IsHit(ray))
                continue;
            if (p->left == NULL && p->right == NULL)
            {
                tmp_inter = p->object->Intersect(ray);
                if (tmp_inter.time < inter.time)
                    inter = std::move(tmp_inter);
            }
            s.push(p->left);
            s.push(p->left);
        }
        return inter;
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

}