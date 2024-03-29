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
#include "defines.h"

namespace platinum
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const glm::vec3 &o, const glm::vec3 &d);
        virtual ~Ray() = default;
        void Init(const glm::vec3 &o, const glm::vec3 &d);
        void Update(const glm::vec3 &o, const glm::vec3 &d, const glm::vec3 &a);
        glm::vec3 GetOrigin() const { return _origin; }
        glm::vec3 GetDirection() const { return _direction; }
        glm::vec3 GetInvDirection() const { return _inv_direction; }
        float GetMinTime() const { return min_t_; }
        float GetMaxTime() const { return _max_t; }
        glm::vec3 GetColor() const { return _color; }
        glm::vec3 PointAt(float t) const { return _origin + t * _direction; }
        int IsDirNeg(size_t i) const { return _is_neg_dir[i]; }
        void SetColor(const glm::vec3 &c);
        void SetTMax(float t) { _max_t = t; }
        void Transform(const glm::mat4 &transform);
        static const float min_t_;

    protected:
        virtual void DoNothing() {}

    private:
        glm::vec3 _origin;
        glm::vec3 _direction, _inv_direction;
        glm::vec3 _color;
        float _max_t;
        std::array<int, 3> _is_neg_dir;
       
    };
} // namespace platinum

#endif
