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

#include "ray.h"

namespace platinum
{
    const float Ray::min_t_ = 10e-4;

    Ray::Ray(const glm::vec3 &o, const glm::vec3 &d) : _origin(o), _direction(d)
    {
        _max_t = std::numeric_limits<float>::max();
        _color = glm::vec3(1.0);
        _inv_direction = {1.0f / d.x, 1.0f / d.y, 1.0f / d.z};
        _is_neg_dir = {d.x < 0, d.y < 0, d.z < 0};
    }
    void Ray::Init(const glm::vec3 &o, const glm::vec3 &d)
    {
        this->_origin = o;
        this->_direction = d;
        this->_inv_direction = {1.0f / d.x, 1.0f / d.y, 1.0f / d.z};
        this->_is_neg_dir = {d.x < 0, d.y < 0, d.z < 0};
        this->_color = glm::vec3(1.0);
        this->_max_t = std::numeric_limits<float>::max();
    }
    void Ray::Update(const glm::vec3 &o, const glm::vec3 &d, const glm::vec3 &a)
    {
        this->_origin = o;
        this->_direction = d;
        this->_inv_direction = {1.0f / d.x, 1.0f / d.y, 1.0f / d.z};
        this->_is_neg_dir = {d.x < 0, d.y < 0, d.z < 0};
        this->_color *= a;
        this->_max_t = std::numeric_limits<float>::max();
    }
    void Ray::SetColor(const glm::vec3 &c)
    {
        _color *= c;
    }

    void Ray::Transform(const glm::mat4 &transform)
    {
        this->_direction = glm::mat3(transform) * _direction;
        auto originQ = transform * glm::vec4(_origin, 1.0f);
        this->_origin = glm::vec3(originQ) / originQ.w;
    }
}