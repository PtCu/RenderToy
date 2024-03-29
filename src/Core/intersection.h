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
#include "vertex.h"

namespace platinum
{
    struct HitRecord
    {
        HitRecord(std::shared_ptr<Ray> _ray = NULL, const glm::vec3 &pos = glm::vec3(0),
                  const glm::vec3 &normal = glm::vec3(0, 0, 1), float u = 0, float v = 0) : ray(_ray), vert(pos, normal, u, v) {}
        std::shared_ptr<Ray> ray;
        Vertex vert;
    };

    struct HitRst
    {
        HitRst(bool hit = false) : is_hit(hit), material_(NULL) {}
        bool is_hit;
        glm::vec3 emit;
        HitRecord record;
        std::shared_ptr<const Material> material_;
        static const HitRst InValid;
    };

}
#endif
