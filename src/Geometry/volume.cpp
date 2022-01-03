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
    void Volume::Sample(HitRst& inter, float& pdf) const
    {
        boundary_->Sample(inter, pdf);
    }
    float Volume::GetArea() const
    {
        return boundary_->GetArea();
    }
    HitRst Volume::Intersect(const Ray& r)
    {


        if (boundary_ == NULL)
            return HitRst::InValid;

        float origin_t_max = r.GetMaxTime();

        auto bound_rst = boundary_->Intersect(r);
        if (!bound_rst.is_hit)
            return HitRst::InValid;

        Ray reverse_ray(r.PointAt(r.GetMinTime() * 1.5f), -r.GetDirection());
        auto reverse_rec = boundary_->Intersect(reverse_ray);

        float t0;
        float t_max_from_t0;
        if (reverse_rec.is_hit)
        {
            // 反向光线撞击到边界, 说明光线在内部, 则此时体积内部的起点为 光线起点
            // 此时以该起点的撞击结果即为前边的 bound_rst
            t0 = 0;
            t_max_from_t0 = bound_rst.record.ray.GetMaxTime();
            //t0_rec = bound_rst;
        }
        else
        {
            // 否则说明光线在外部, 则此时体积内部的起点为 光线撞击处
            // 此时以该起点的撞击结果需计算
            t0 = bound_rst.record.ray.GetMaxTime();
            Ray t0Ray(r.PointAt(t0), r.GetDirection());
            HitRst t0_rec = boundary_->Intersect(t0Ray);

            //太薄
            if (!t0_rec.is_hit)
            {
                //  r.SetTMax(origin_t_max);
                return HitRst::InValid;
            }

            t_max_from_t0 = t0_rec.record.ray.GetMaxTime();
        }

        float t1 = glm::min(origin_t_max, t0 + t_max_from_t0);
        //此处的 len 未考虑 transform 的 scale
        float dis_in_vol = (t1 - t0) * glm::length(r.GetDirection());

        // p = C * dL
        // p(L) = lim(n->inf, (1 - CL/n)^n) = exp(-CL)
        // L = -(1/C)ln(pL)
        float hit_dis = -(1.0f / density_) * log(Random::RandomInUnitFloat());

        if (hit_dis >= dis_in_vol)
        {
            // r.SetTMax(origin_t_max);
            return HitRst::InValid;
        }

        float tFinal = t0 + hit_dis / glm::length(r.GetDirection());

        HitRst rst;
        rst.is_hit = 1;
        rst.record = HitRecord(r, r.PointAt(tFinal));
        rst.material = GetMaterial();
        rst.record.ray = r;
        rst.record.ray.SetTMax(tFinal);
        return rst;
    }

}
