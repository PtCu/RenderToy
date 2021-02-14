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
#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <assert.h>
#include <string.h>


// Platform-specific definitions
#if defined(_WIN32) || defined(_WIN64)
#define PLT_IS_WINDOWS
#endif

#ifdef PBRT_FLOAT_AS_DOUBLE
using PFloat = double;
#else
using PFloat = float;
#endif

#include <stdint.h>
#include <float.h>
#include <intrin.h>


static constexpr PFloat ShadowEpsilon = 0.0001f;
static constexpr PFloat Pi = 3.14159265358979323846;
static constexpr PFloat InvPi = 0.31830988618379067154;
static constexpr PFloat Inv2Pi = 0.15915494309189533577;
static constexpr PFloat Inv4Pi = 0.07957747154594766788;
static constexpr PFloat PiOver2 = 1.57079632679489661923;
static constexpr PFloat PiOver4 = 0.78539816339744830961;
static constexpr PFloat Sqrt2 = 1.41421356237309504880;

template<typename T>
class Vector2;
template<typename T>
class Vector3;
template<typename T>
class Point2;
template<typename T>
class Point3;
template<typename T>
class Normal3;
class Camera;
class Material;
