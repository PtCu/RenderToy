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

#ifndef CORE_CAMERA_H_
#define CORE_CAMERA_H_

#include "defines.h"
#include "../Math/rand.h"
#include "material.h"

namespace platinum
{
    class Camera
    {
    public:
        //For test
        Camera();
       
        Camera(const glm::vec3& lookfrom,const glm::vec3& lookat, const glm::vec3& vup, float vfov, float aspect, float aperture, float focusDist);
        virtual ~Camera() = default;
        virtual std::shared_ptr<Ray> GetRay(float s, float t) const;

    protected:
        void GetRay(float s, float t, std::shared_ptr<Ray> ray) const;
        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
        glm::vec3 front, up, right; //A set of orthonormal basis, to describe orentation of camera.
        float lens_radius;
    };

} // namespace platinum

#endif
