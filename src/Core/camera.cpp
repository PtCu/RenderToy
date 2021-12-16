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

#include "camera.h"

namespace platinum
{
    //For test
    Camera::Camera()
    {
        lower_left_corner = glm::vec3(-2.0, 1.0, -1.0);
        horizontal = glm::vec3(4.0, 0.0, 0.0);
        vertical = glm::vec3(0.0, -2.0, 0.0);
        origin_ = glm::vec3(0.0, 0.0, 0.0);
    }
    Camera::Camera(const glm::vec3 &lookfrom, const glm::vec3 &lookat, const glm::vec3 &vup, float vfov, float aspect, float aperture, float focus_dist) : origin_(lookfrom), lens_radius(aperture)
    {
        // lens_radius = aperture / 2;
        // float theta = vfov * PI / 180;
        // float half_height = tan(theta / 2);
        // float half_width = aspect * half_height;
        // origin_ = lookfrom;
        // w = glm::normalize(glm::vec3(lookfrom - lookat));
        // u = glm::normalize(glm::cross(vup, w));
        // v = glm::cross(w, u);
        // lower_left_corner = origin_ - half_width * focusDist * u - half_height * focusDist * v - focusDist * w;
        // horizontal = 2 * half_width * focusDist * u;
        // vertical = 2 * half_height * focusDist * v;

        if (focus_dist == -1.0f)
            focus_dist = glm::distance(lookfrom, lookat);

        float theta = vfov / 180.0f * PI;
        float height = 2 * focus_dist * tan(theta / 2);
        float width = aspect * height;
        origin_ = lookfrom;
        front = glm::normalize(lookat - lookfrom);
        right = glm::normalize(glm::cross(vup, -front));
        up = glm::cross(-front, right);
        lower_left_corner = origin_ + focus_dist * front - width / 2 * right - height / 2 * up;
        horizontal = width * right;
        vertical = height * up;
    }

    std::shared_ptr<Ray> Camera::GetRay(float s, float t) const
    {
        auto ray = std::make_shared<Ray>(origin_,
                                         lower_left_corner + s * horizontal + t * vertical - origin_);
        return ray;
    }
    void Camera::GetRay(float s, float t, std::shared_ptr<Ray> ray) const
    {
        glm::vec2 rd = lens_radius * Random::RandomInUnitDisk();
        glm::vec3 _origin = origin_ + rd.x * right + rd.y * up;
        glm::vec3 dir = lower_left_corner + s * horizontal + t * vertical - origin_;
        ray->Init(origin_, dir);
    }
}
