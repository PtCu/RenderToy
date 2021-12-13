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
        glm::vec3 GetOrigin() const { return origin_; }
        glm::vec3 GetDirection() const { return direction_; }
        glm::vec3 GetInvDirection() const { return inv_direction_; }
        float GetMinTime() const { return min_t_; }
        float GetMaxTime() const { return max_t_; }
        glm::vec3 GetColor() const { return color_; }
        glm::vec3 PointAt(float t) const { return origin_ + t * direction_; }
        int IsDirNeg(size_t i) const { return is_neg_dir_[i]; }
        void SetColor(const glm::vec3 &c);
        void SetTMax(float t) { max_t_ = t; }
        void Transform(const glm::mat4 &transform);
        static const float min_t_;

    protected:
        virtual void DoNothing() {}

    private:
        glm::vec3 origin_;
        glm::vec3 direction_, inv_direction_;
        glm::vec3 color_;
        float max_t_;
        std::array<int, 3> is_neg_dir_;
       
    };
} // namespace platinum

#endif
