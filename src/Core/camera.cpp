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
        _lower_left_corner = glm::vec3(-2.0, 1.0, -1.0);
        _horizontal = glm::vec3(4.0, 0.0, 0.0);
        _vertical = glm::vec3(0.0, -2.0, 0.0);
        _origin = glm::vec3(0.0, 0.0, 0.0);
    }
    Camera::Camera(const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& vup, float vfov, float aspect, float aperture, float focus_dist) :
        _origin(lookfrom), _lens_radius(aperture)
    {
        if (focus_dist == -1.0f)
            focus_dist = glm::distance(lookfrom, lookat);

        float theta = vfov / 180.0f * PI;
        float height = 2 * focus_dist * tan(theta / 2);
        float width = aspect * height;
        _origin = lookfrom;
        _front = glm::normalize(lookat - lookfrom);
        _right = glm::normalize(glm::cross(vup, -_front));
        _up = glm::cross(-_front, _right);
        _lower_left_corner = _origin + focus_dist * _front - width / 2 * _right - height / 2 * _up;
        _horizontal = width * _right;
        _vertical = height * _up;
    }

    std::shared_ptr<Ray> Camera::GetRay(float s, float t) const
    {
        auto ray = std::make_shared<Ray>(_origin,
            _lower_left_corner + s * _horizontal + t * _vertical - _origin);
        return ray;
    }
    void Camera::GetRay(float s, float t, std::shared_ptr<Ray> ray) const
    {
        glm::vec2 rd = _lens_radius * Random::RandomInUnitDisk();
        glm::vec3 _origin = _origin + rd.x * _right + rd.y * _up;
        glm::vec3 dir = _lower_left_corner + s * _horizontal + t * _vertical - _origin;
        ray->Init(_origin, dir);
    }
}
