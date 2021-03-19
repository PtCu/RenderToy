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

#ifndef CORE_INTERSECTION_H_
#define CORE_INTERSECTION_H_
#include <glm/glm.hpp>
#include "defines.h"
#include "material.h"
#include "ray.h"
namespace platinum
{
    struct Intersection
    {
        glm::vec3 point;
        glm::vec3 normal;
        float time;
        float u;
        float v;
        std::shared_ptr<Material> material;
        std::shared_ptr<Ray> ray;
        bool happened;
        Intersection()
        {
            point = {0, 0, 0};
            normal = {0, 0, 0};
            time = std::numeric_limits<float>::max();
            material = NULL;
            ray = NULL;
            happened = false;
        };
    }; // namespace platinum
}
#endif
