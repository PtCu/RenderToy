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

#ifndef CORE_RAY_H_
#define CORE_RAY_H_

#include <glm/glm.hpp>
#include <core/defines.h>

namespace platinum
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const glm::vec3& o, const glm::vec3& d, float t_max = std::numeric_limits<float>::max())
            : _origin(o), _dir(glm::normalize(d)), _t_max(t_max) {

            color_ = glm::vec3(1.0);
            inv_direction_ = { 1.0f / d.x, 1.0f / d.y, 1.0f / d.z };
            is_neg_dir_ = { d.x < 0, d.y < 0, d.z < 0 };
        }
        virtual ~Ray() = default;
        void Init(const glm::vec3& o, const glm::vec3& d);
        void Update(const glm::vec3& o, const glm::vec3& d, const glm::vec3& a);
        glm::vec3 GetOrigin() const { return _origin; }
        glm::vec3 GetDirection() const { return _dir; }
        glm::vec3 GetInvDirection() const { return inv_direction_; }
        float GetMinTime() const { return min_t_; }
        float GetMaxTime() const { return _t_max; }
        glm::vec3 GetColor() const { return color_; }
        glm::vec3 PointAt(float t) const { return _origin + t * _dir; }
        int IsDirNeg(size_t i) const { return is_neg_dir_[i]; }
        void SetColor(const glm::vec3& c);
        void SetTMax(float t) { _t_max = t; }
        void Transform(const glm::mat4& transform);
        static const float min_t_;
        float GetTime() const { return _time; }
        void SetTime(float t) { _time = t; }
    protected:
        virtual void DoNothing() {}

    private:
        glm::vec3 _origin;
        glm::vec3 _dir, inv_direction_;
        glm::vec3 color_;
        float _t_max;
        std::array<int, 3> is_neg_dir_;
        float _time;

    };
} // namespace platinum

#endif
