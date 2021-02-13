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

    template <typename T>
    inline PFloat Distance(const Point3<T> &p1, const Point3<T> &p2)
    {
        return (p1 - p2).Length();
    }

    template <typename T>
    inline PFloat SquaredDistance(const Point3<T> &p1, const Point3<T> &p2)
    {
        return (p1 - p2).SquaredLength();
    }

    template <typename T, typename U>
    inline Point3<T> operator*(U f, const Point3<T> &p)
    {
        return p * f;
    }

    template <typename T>
    Point3<T> Lerp(PFloat t, const Point3<T> &p0, const Point3<T> &p1)
    {
        return (1 - t) * p0 + t * p1;
    }

    template <typename T>
    Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2)
    {
        return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                         std::min(p1.z, p2.z));
    }

    template <typename T>
    Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2)
    {
        return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                         std::max(p1.z, p2.z));
    }

    template <typename T>
    Point3<T> Floor(const Point3<T> &p)
    {
        return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
    }

    template <typename T>
    Point3<T> Ceil(const Point3<T> &p)
    {
        return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
    }

    template <typename T>
    Point3<T> Abs(const Point3<T> &p)
    {
        return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
    }

    template <typename T>
    Point3<T> Permute(const Point3<T> &p, int x, int y, int z)
    {
        return Point3<T>(p[x], p[y], p[z]);
    }

    template <typename T>
    inline PFloat Distance(const Point2<T> &p1, const Point2<T> &p2)
    {
        return (p1 - p2).Length();
    }

    template <typename T>
    inline PFloat SquaredDistance(const Point2<T> &p1, const Point2<T> &p2)
    {
        return (p1 - p2).SquaredLength();
    }

    template <typename T, typename U>
    inline Point2<T> operator*(U f, const Point2<T> &p)
    {
        return p * f;
    }

    template <typename T>
    Point2<T> Floor(const Point2<T> &p)
    {
        return Point2<T>(std::floor(p.x), std::floor(p.y));
    }

    template <typename T>
    Point2<T> Ceil(const Point2<T> &p)
    {
        return Point2<T>(std::ceil(p.x), std::ceil(p.y));
    }

    template <typename T>
    Point2<T> Lerp(PFloat t, const Point2<T> &v0, const Point2<T> &v1)
    {
        return (1 - t) * v0 + t * v1;
    }

    template <typename T>
    Point2<T> Min(const Point2<T> &pa, const Point2<T> &pb)
    {
        return Point2<T>(std::min(pa.x, pb.x), std::min(pa.y, pb.y));
    }

    template <typename T>
    Point2<T> Max(const Point2<T> &pa, const Point2<T> &pb)
    {
        return Point2<T>(std::max(pa.x, pb.x), std::max(pa.y, pb.y));
    }

} // namespace platinum

#endif
