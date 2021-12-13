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

#include "t_camera.h"

namespace platinum
{
    std::shared_ptr<Ray> TCamera::GetRay(float s, float t) const
    {
        auto tray = std::make_shared<TRay>();
        float time = time0 + Random::RandomInUnitFloat() * (time1 - time0);
        Camera::GetRay(s, t, tray);
        // glm::vec3 rd = lens_radius * Random::RandomInUnitDisk();
        // glm::vec3 offset = u * rd.x + v * rd.y;
        // float time = time0 + Random::RandomInUnitFloat() * (time1 - time0);
        // auto ray = std::make_shared<TRay>(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
        tray->SetTime(time);
        return tray;
    }
}
