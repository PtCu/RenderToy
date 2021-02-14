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

#include "platinum.h"
#include "../Math/point.h"
#include "../Math/vector.h"
#include "../Math/rand.h"
#include "material.h"

namespace platinum
{
    class Camera
    {
        /**
         * @brief Construct a new Camera object
         * @param  lookfrom         The position camera is.
         * @param  lookat           The direction camera looking at.
         * @param  vup              View up vector, specifying the extent of sideways tilt.
         * @param  vfov             Field of view, top to bottom in degrees.
         * @param  aspect           The ratio of fov in width to fov in height.
         * @param  aperture         Size of aperture.
         * @param  focusDist       My Param doc
         */
        Camera(Point3f lookfrom, Vector3f lookat, Vector3f vup, PFloat vfov, PFloat aspect, PFloat aperture, PFloat focusDist)
        {
            lens_radius = aperture / 2;
            PFloat theta = vfov * Pi / 180;
            PFloat half_height = tan(theta / 2);
            PFloat half_width = aspect * half_height;
            origin = lookfrom;
            w = Vector3f(lookfrom - lookat).Normalized();
            u = Cross(vup, w).Normalized();
            v = Cross(w, u);
            lower_left_corner = origin - half_width * focusDist * u - half_height * focusDist * v - focusDist * w;
            horizontal = 2 * half_width * focusDist * u;
            vertical = 2 * half_height * focusDist * v;
        }

        Ray GetRay(PFloat s, PFloat t, bool isMotionBlur = false)
        {
            if (isMotionBlur)
            {
                Vector3f rd = lens_radius * Random::RandomInUnitDisk();
                Vector3f offset = u * rd.x + v * rd.y;
                float time = time0 + Random::drand48() * (time1 - time0);
                return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
            }
            return Ray(origin,
                       lower_left_corner + s * horizontal + t * vertical - origin);
        }

        Point3f origin;
        Point3f lower_left_corner;
        Vector3f horizontal;
        Vector3f vertical;
        Vector3f u, v, w; //A set of orthonormal basis, to describe orentation of camera.
        PFloat lens_radius;
        PFloat time0, time1; // new variables for shutter open/close times
    };
    
} // namespace platinum

#endif
