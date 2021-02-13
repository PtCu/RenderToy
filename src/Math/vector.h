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

#ifndef VECTOR_H
#define VECTOR_H

#include "../Core/platinum.h"
namespace platinum
{
    template <typename T>
    class Vector2
    {
    public:
        Vector2() : x(0), y(0) {}
        Vector2(T xx, T yy) : x(xx), y(yy) {}
        explicit Vector2(const Point2<T> &p) : x(p.x), y(p.y) {}
        explicit Vector2(const Point3<T> &p) : x(p.x), y(p.y) {}

        Vector2(const Vector2<T> &v)
        {
            x = v.x;
            y = v.y;
        }
        Vector2<T> &operator=(const Vector2<T> &v)
        {
            x = v.x;
            y = v.y;
            return *this;
        }

        Vector2<T> operator+(const Vector2<T> &v) const
        {
            return Vector2(x + v.x, y + v.y);
        }

        Vector2<T> &operator+=(const Vector2<T> &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }
        Vector2<T> operator-(const Vector2<T> &v) const
        {
            return Vector2(x - v.x, y - v.y);
        }

        Vector2<T> &operator-=(const Vector2<T> &v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        bool operator==(const Vector2<T> &v) const { return x == v.x && y == v.y; }
        bool operator!=(const Vector2<T> &v) const { return x != v.x || y != v.y; }
        template <typename U>
        Vector2<T> operator*(U f) const
        {
            return Vector2<T>(f * x, f * y);
        }

        template <typename U>
        Vector2<T> &operator*=(U f)
        {
            x *= f;
            y *= f;
            return *this;
        }
        template <typename U>
        Vector2<T> operator/(U f) const
        {
            PFloat inv = (PFloat)1 / f;
            return Vector2<T>(x * inv, y * inv);
        }

        template <typename U>
        Vector2<T> &operator/=(U f)
        {
            PFloat inv = (PFloat)1 / f;
            x *= inv;
            y *= inv;
            return *this;
        }
        Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
        T operator[](int i) const
        {
            if (i == 0)
                return x;
            return y;
        }

        T &operator[](int i)
        {
            if (i == 0)
                return x;
            return y;
        }
        PFloat SquaredLength() const { return x * x + y * y; }
        PFloat Length() const { return std::sqrt(SquaredLength()); }

        T x, y;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Vector2<T> &v)
    {
        os << "[ " << v.x << ", " << v.y << " ]";
        return os;
    }

    using Vector2f = Vector2<PFloat>;
    using Vector2i = Vector2<int>;

        template <typename T>
    class Vector3
    {
    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        explicit Vector3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {}

        Vector3(const Vector3<T> &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }

        Vector3<T> &operator=(const Vector3<T> &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }
        Vector3<T> operator+(const Vector3<T> &v) const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }
        Vector3<T> &operator+=(const Vector3<T> &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        Vector3<T> operator-(const Vector3<T> &v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }
        Vector3<T> &operator-=(const Vector3<T> &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        bool operator==(const Vector3<T> &v) const
        {
            return x == v.x && y == v.y && z == v.z;
        }
        bool operator!=(const Vector3<T> &v) const
        {
            return x != v.x || y != v.y || z != v.z;
        }
        T operator[](int i) const
        {
            if (i == 0)
                return x;
            if (i == 1)
                return y;
            return z;
        }
        T &operator[](int i)
        {
            if (i == 0)
                return x;
            if (i == 1)
                return y;
            return z;
        }

        template <typename U>
        Vector3<T> operator*(U s) const
        {
            return Vector3<T>(s * x, s * y, s * z);
        }
        template <typename U>
        Vector3<T> &operator*=(U s)
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        template <typename U>
        Vector3<T> operator/(U f) const
        {
            PFloat inv = (PFloat)1 / f;
            return Vector3<T>(x * inv, y * inv, z * inv);
        }

        template <typename U>
        Vector3<T> &operator/=(U f)
        {
            PFloat inv = (PFloat)1 / f;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }
        Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
        PFloat SquaredLength() const { return x * x + y * y + z * z; }
        PFloat Length() const { return std::sqrt(SquaredLength()); }

        // Vector3 Public Data
        T x, y, z;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Vector3<T> &v)
    {
        os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
        return os;
    }

    template <typename T,typename U>
    inline Vector3<T> operator*(U t, const Vector3<T> &v)
    {
        return Vector3<T>(t * v.x, t * v.y, t * v.z);
    }

    using Vector3f = Vector3<PFloat>;
    using Vector3i = Vector3<int>;

    
} // namespace platinum

#endif
