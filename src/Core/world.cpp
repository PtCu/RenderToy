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
    void World::AddObject(Object *obj)
    {
        this->list.push_back(obj);
        ++list_size;
    }
    void World::DestroyAll()
    {
        for (auto obj : list)
        {
            delete obj;
            obj = NULL;
        }
        list.clear();
        list_size = 0;
    }
    bool World::IntersectAll(const Ray &r, PFloat t_min, PFloat t_max, Intersection &rec) const
    {
        Intersection temp_rec;
        bool hit_anything = false;
        PFloat closest_so_far = t_max;
        for (int i = 0; i < list_size; i++)
        {
            if (list[i]->Intersect(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.time;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
} // namespace platinum
