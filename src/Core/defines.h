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

//Core/
// Global Include Files

#ifndef CORE_DEFINES_H_
#define CORE_DEFINES_H_

#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <float.h>

// #include <intrin.h>

namespace platinum
{
// Platform-specific definitions
#if defined(_WIN32) || defined(_WIN64)
#define PLT_IS_WINDOWS
#endif

    static constexpr float ShadowEpsilon = 0.0001f;
    static constexpr float Pi = 3.14159265358979323846f;
    static constexpr float InvPi = 0.31830988618379067154f;
    static constexpr float Inv2Pi = 0.15915494309189533577f;
    static constexpr float Inv4Pi = 0.07957747154594766788f;
    static constexpr float PiOver2 = 1.57079632679489661923f;
    static constexpr float PiOver4 = 0.78539816339744830961f;
    static constexpr float Sqrt2 = 1.41421356237309504880f;

    template <typename T>
    class Vector2;
    template <typename T>
    class Vector3;
    template <typename T>
    class Point2;
    template <typename T>
    class Point3;
    template <typename T>
    class Normal3;
    class Camera;
    class Material;
    struct Intersection;
    class World;
    class Ray;
    class Object;
    class AABB;

} // namespace platinum
#endif