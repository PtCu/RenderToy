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

#include "instance.h"

namespace platinum
{
    Instance::Instance(const glm::mat4 &transform, std::shared_ptr<Object> former, const std::shared_ptr<Material> &m)
        : transform(transform),
          inverseTransform(inverse(transform)),
          normalTransform(transpose(inverse(glm::mat3(transform)))),
          former(former),
          Object(m)

    {
        if (former == NULL)
        {
            return;
        }
        auto childBox = former->GetBoundingBox();
        if (!childBox.IsValid())
        {
            bounding_box = AABB();
            return;
        }

        glm::vec3 srcP[2] = {childBox.GetMin(), childBox.GetMax()};
        glm::vec3 min_p, max_p;
        for (size_t i = 0; i < 8; i++)
        {
            std::bitset<3> binVal(i);
            glm::vec3 cornerP = glm::vec3(srcP[binVal[2]].x, srcP[binVal[1]].y, srcP[binVal[0]].z);
            glm::vec4 tfmCornerPQ = transform * glm::vec4(cornerP, 1);
            auto tmp = glm::vec3(tfmCornerPQ) / tfmCornerPQ.w;
            min_p = glm::min(min_p, tmp);
            max_p = glm::max(max_p, tmp);
        }

        bounding_box = AABB(min_p, max_p);
    }


    Intersection Instance::Intersect(std::shared_ptr<Ray> &r) const
    {
        Intersection rec;
        if (former == NULL)
            return rec;

        r->Transform(inverseTransform);

        rec = former->Intersect(r);

        if (rec.happened)
        {
            if (GetMaterial() != NULL)
            {
                rec.material = GetMaterial();
            }
            rec.vert.Transform(transform, normalTransform);
        }

        r->Transform(transform);

        return rec;
    }

}