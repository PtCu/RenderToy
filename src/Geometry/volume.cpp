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

#include "volume.h"

namespace platinum
{
    Intersection Volume::Intersect(std::shared_ptr<Ray> &r) const
    {
        Intersection rec;
        if (boundary == NULL)
            return rec;

        float originTMax = r->GetMaxTime();

        auto bound_rec = boundary->Intersect(r);
        if (!bound_rec.happened)
            return rec;

        auto reverse_ray = std::make_shared<Ray>(r->PointAtT(r->GetMinTime() * 1.5f), -r->GetDirection());
        auto reverse_rec = boundary->Intersect(reverse_ray);

        float t0;
        float tMaxFromT0;
        if (reverse_rec.happened)
        {
            // 反向光线撞击到边界, 说明光线在内部, 则此时体积内部的起点为 光线起点
            // 此时以该起点的撞击结果即为前边的 bound_rec
            t0 = 0;
            tMaxFromT0 = bound_rec.ray->GetMaxTime();
            //t0HitRst = bound_rec;
        }
        else
        {
            // 否则说明光线在外部, 则此时体积内部的起点为 光线撞击处
            // 此时以该起点的撞击结果需计算
            t0 = bound_rec.ray->GetMaxTime();
            auto t0Ray = std::make_shared<Ray>(r->PointAtT(t0), r->GetDirection());
            Intersection t0HitRst = boundary->Intersect(t0Ray);

            //太薄
            if (!t0HitRst.happened)
            {
                r->SetTMax(originTMax);
                return rec;
            }

            tMaxFromT0 = t0HitRst.ray->GetMaxTime();
        }

        float t1 = glm::min(originTMax, t0 + tMaxFromT0);
        //此处的 len 未考虑 transform 的 scale
        float lenInVolume = (t1 - t0) * glm::length(r->GetDirection());

        // p = C * dL
        // p(L) = lim(n->inf, (1 - CL/n)^n) = exp(-CL)
        // L = -(1/C)ln(pL)
        float hitLen = -(1.0f / density) * log(Random::RandomInUnitFloat());

        if (hitLen >= lenInVolume)
        {
            r->SetTMax(originTMax);
            return rec;
        }

        float tFinal = t0 + hitLen / glm::length(r->GetDirection());
        r->SetTMax(tFinal);

        rec.happened = 1;
        rec.ray = r;
        rec.material = GetMaterial();

        return rec;
    }

}
