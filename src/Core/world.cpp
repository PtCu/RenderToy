// The MIT License (MIT)

// Copyright (c) 2021 PtCU

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

#include "world.h"

namespace platinum
{
    void World::BuildBVH()
    {
        this->bvh_accel = std::unique_ptr<BVHAccel>(new BVHAccel(objects));
    }
    void World::AddObject(std::shared_ptr<Object> obj)
    {
        this->objects.push_back(obj);
    }
    void World::DestroyAll()
    {
        // for (auto obj : list)
        // {
        //     delete obj;
        //     obj = NULL;
        // }
        objects.clear();
    }
    Intersection World ::intersectAll(const Ray &ray) const
    {
        return this->bvh_accel->RayCast(ray);
    }
    glm::vec3 World::CastRay(const Ray &ray, int depth) const
    {
        if (depth > max_depth)
        {
            return glm::vec3(0, 0, 0);
        }
        auto rec = intersectAll(ray);
        if (rec.happened)
        {
            glm::vec3 attenuation;
            Ray scattered;
            if (rec.material->Scatter(ray, rec, attenuation, scattered))
            {
                return attenuation * CastRay(scattered, depth + 1);
            }
            return glm::vec3(0, 0, 0);
        }
        else
        {
            //TODO: Make it configurable
            glm::vec3 unit_direction = glm::normalize(ray.GetDirection());
            float t = 0.5f * (unit_direction.y + 1.0f);
            return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
        }
    }
    bool World::IntersectAll(const Ray &r, Intersection &rec) const
    {
        Intersection temp_rec;
        bool hit_anything = false;
        float closest_so_far = std::numeric_limits<float>::max();
        for (int i = 0; i < objects.size(); i++)
        {
            temp_rec = objects[i]->Intersect(r);
            if (temp_rec.happened && temp_rec.time < closest_so_far)
            {
                hit_anything = true;
                closest_so_far = temp_rec.time;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
} // namespace platinum
