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

#ifndef POINT_H
#define POINT_H

#include "../Core/platinum.h"
namespace platinum
{
    template <typename T>
    class Point2
    {
    public:
        // Point2 Public Methods
        explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) {}
        Point2() : x(0), y(0) {}
        Point2(T xx, T yy) : x(xx), y(yy) {}

        Point2(const Point2<T> &p)
        {
            x = p.x;
            y = p.y;
        }

        template <typename U>
        explicit Point2(const Point2<U> &p)
        {
            x = (T)p.x;
            y = (T)p.y;
        }

        template <typename U>
        explicit Point2(const Vector2<U> &p)
        {
            x = (T)p.x;
            y = (T)p.y;
        }
        template <typename U>
        explicit operator Vector2<U>() const
        {
            return Vector2<U>(x, y);
        }

        Point2<T> &operator=(const Point2<T> &p)
        {

            x = p.x;
            y = p.y;
            return *this;
        }

        Point2<T> operator+(const Vector2<T> &v) const
        {

            return Point2<T>(x + v.x, y + v.y);
        }

        Point2<T> &operator+=(const Vector2<T> &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }
        Vector2<T> operator-(const Point2<T> &p) const
        {

            return Vector2<T>(x - p.x, y - p.y);
        }

        Point2<T> operator-(const Vector2<T> &v) const
        {
            DCHECK(!v.HasNaNs());
            return Point2<T>(x - v.x, y - v.y);
        }
        Point2<T> operator-() const { return Point2<T>(-x, -y); }
        Point2<T> &operator-=(const Vector2<T> &v)
        {
            DCHECK(!v.HasNaNs());
            x -= v.x;
            y -= v.y;
            return *this;
        }
        Point2<T> &operator+=(const Point2<T> &p)
        {
            DCHECK(!p.HasNaNs());
            x += p.x;
            y += p.y;
            return *this;
        }
        Point2<T> operator+(const Point2<T> &p) const
        {
            DCHECK(!p.HasNaNs());
            return Point2<T>(x + p.x, y + p.y);
        }
        template <typename U>
        Point2<T> operator*(U f) const
        {
            return Point2<T>(f * x, f * y);
        }
        template <typename U>
        Point2<T> &operator*=(U f)
        {
            x *= f;
            y *= f;
            return *this;
        }
        template <typename U>
        Point2<T> operator/(U f) const
        {
            CHECK_NE(f, 0);
            PPFloat inv = (PPFloat)1 / f;
            return Point2<T>(inv * x, inv * y);
        }
        template <typename U>
        Point2<T> &operator/=(U f)
        {
            CHECK_NE(f, 0);
            PPFloat inv = (PPFloat)1 / f;
            x *= inv;
            y *= inv;
            return *this;
        }
        T operator[](int i) const
        {
            DCHECK(i >= 0 && i <= 1);
            if (i == 0)
                return x;
            return y;
        }

        T &operator[](int i)
        {
            DCHECK(i >= 0 && i <= 1);
            if (i == 0)
                return x;
            return y;
        }
        bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }
        bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }
        bool HasNaNs() const { return isNaN(x) || isNaN(y); }

        T x, y;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Point2<T> &v)
    {
        os << "[ " << v.x << ", " << v.y << " ]";
        return os;
    }

    template <typename T>
    class Point3
    {
    public:
        // Point3 Public Methods
        Point3() { x = y = z = 0; }
        Point3(T x, T y, T z) : x(x), y(y), z(z) {}
        template <typename U>
        explicit Point3(const Point3<U> &p)
            : x((T)p.x), y((T)p.y), z((T)p.z) {}
        template <typename U>
        explicit operator Vector3<U>() const
        {
            return Vector3<U>(x, y, z);
        }

        Point3(const Point3<T> &p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
        }

        Point3<T> &operator=(const Point3<T> &p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
            return *this;
        }

        Point3<T> operator+(const Vector3<T> &v) const
        {
            return Point3<T>(x + v.x, y + v.y, z + v.z);
        }
        Point3<T> &operator+=(const Vector3<T> &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        Vector3<T> operator-(const Point3<T> &p) const
        {
            return Vector3<T>(x - p.x, y - p.y, z - p.z);
        }
        Point3<T> operator-(const Vector3<T> &v) const
        {
            return Point3<T>(x - v.x, y - v.y, z - v.z);
        }
        Point3<T> &operator-=(const Vector3<T> &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        Point3<T> &operator+=(const Point3<T> &p)
        {
            x += p.x;
            y += p.y;
            z += p.z;
            return *this;
        }
        Point3<T> operator+(const Point3<T> &p) const
        {
            return Point3<T>(x + p.x, y + p.y, z + p.z);
        }
        template <typename U>
        Point3<T> operator*(U f) const
        {
            return Point3<T>(f * x, f * y, f * z);
        }
        template <typename U>
        Point3<T> &operator*=(U f)
        {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }
        template <typename U>
        Point3<T> operator/(U f) const
        {
            PFloat inv = (PFloat)1 / f;
            return Point3<T>(inv * x, inv * y, inv * z);
        }
        template <typename U>
        Point3<T> &operator/=(U f)
        {
            PFloat inv = (PFloat)1 / f;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
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
        bool operator==(const Point3<T> &p) const
        {
            return x == p.x && y == p.y && z == p.z;
        }
        bool operator!=(const Point3<T> &p) const
        {
            return x != p.x || y != p.y || z != p.z;
        }
        Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

        T x, y, z;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Point3<T> &v)
    {
        os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
        return os;
    }

    using Point2f = Point2<PFloat>;
    using Poinst2i = Point2<int>;
    using Point3f = Point3<PFloat>;
    using Point3i = Point3<int>;
} // namespace platinum

#endif
