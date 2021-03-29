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
    World::~World()
    {
        destroyAll();
    }
    void World::destroyAll()
    {
        objects.clear();
    }
    void World::BuildBVH()
    {
        this->bvh_accel = std::unique_ptr<BVHAccel>(new BVHAccel(objects));
    }
    void World::AddObject(const std::shared_ptr<Object> &obj)
    {
        this->objects.push_back(obj);
    }
    void World::AddObject(const std::vector<std::shared_ptr<Object>> &obj)
    {
        this->objects.insert(objects.end(), obj.begin(), obj.end());
    }
    void World::AddObject(const std::vector<std::shared_ptr<Object>>::iterator &begin, const std::vector<std::shared_ptr<Object>>::iterator &end)
    {
        this->objects.insert(objects.end(), begin, end);
    }
    void World::Reset()
    {
        this->bvh_accel.reset();
        this->destroyAll();
    }
    Intersection World ::intersectAll(std::shared_ptr<Ray> &r) const
    {
        return this->bvh_accel->RayCast(r);
    }
    glm::vec3 World::CastRay(std::shared_ptr<Ray> &r) const
    {
        return CastRay(r, max_depth);
    }
    glm::vec3 World::CastRay(std::shared_ptr<Ray> &ray, int dep) const
    {
        if (dep == 0)
        {
            return glm::vec3(1.0001f / 255.0f);
        }
        auto rec = intersectAll(ray);
        if (rec.happened)
        {
            if (rec.material == NULL)
                return glm::vec3(0, 1, 0);
            if (rec.material->Scatter(rec))
                return CastRay(ray, dep - 1);
            else
                return ray->GetColor();
        }
        else
        {

            if (!default_light)
                return glm::vec3(1.0001f / 255.0f);

            //TODO: Make it configurable
            glm::vec3 unit_direction = glm::normalize(ray->GetDirection());
            float t = 0.5f * (unit_direction.y + 1.0f);
            return ray->GetColor() * ((1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.75, 0.85, 1.0));
        }
    }
    bool World::IntersectAll(std::shared_ptr<Ray> &r, Intersection &rec) const
    {
        Intersection temp_rec;
        bool hit_anything = false;
        float closest_so_far = std::numeric_limits<float>::max();
        for (int i = 0; i < objects.size(); i++)
        {
            temp_rec = objects[i]->Intersect(r);
            if (temp_rec.happened && temp_rec.ray->GetMaxTime() < closest_so_far)
            {
                hit_anything = true;
                closest_so_far = temp_rec.ray->GetMaxTime();
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
} // namespace platinum
