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

#include "../Core/platinum.h"

namespace platinum
{
    template <typename T>
    class Normal3
    {
    public:
        // Normal3 Public Methods
        Normal3() { x = y = z = 0; }
        Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
        Normal3<T> operator-() const { return Normal3(-x, -y, -z); }
        Normal3<T> operator+(const Normal3<T> &n) const
        {
            return Normal3<T>(x + n.x, y + n.y, z + n.z);
        }

        Normal3<T> &operator+=(const Normal3<T> &n)
        {
            x += n.x;
            y += n.y;
            z += n.z;
            return *this;
        }
        Normal3<T> operator-(const Normal3<T> &n) const
        {
            return Normal3<T>(x - n.x, y - n.y, z - n.z);
        }

        Normal3<T> &operator-=(const Normal3<T> &n)
        {
            x -= n.x;
            y -= n.y;
            z -= n.z;
            return *this;
        }
        template <typename U>
        Normal3<T> operator*(U f) const
        {
            return Normal3<T>(f * x, f * y, f * z);
        }

        template <typename U>
        Normal3<T> &operator*=(U f)
        {
            x *= f;
            y *= f;
            z *= f;
            return *this;
        }
        template <typename U>
        Normal3<T> operator/(U f) const
        {
            PFloat inv = (PFloat)1 / f;
            return Normal3<T>(x * inv, y * inv, z * inv);
        }

        template <typename U>
        Normal3<T> &operator/=(U f)
        {
            PFloat inv = (PFloat)1 / f;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }
        PFloat squaredLength() const { return x * x + y * y + z * z; }
        PFloat Length() const { return std::sqrt(squaredLength()); }

        Normal3<T>(const Normal3<T> &n)
        {
            x = n.x;
            y = n.y;
            z = n.z;
        }

        Normal3<T> &operator=(const Normal3<T> &n)
        {
            x = n.x;
            y = n.y;
            z = n.z;
            return *this;
        }
        explicit Normal3<T>(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}
        bool operator==(const Normal3<T> &n) const
        {
            return x == n.x && y == n.y && z == n.z;
        }
        bool operator!=(const Normal3<T> &n) const
        {
            return x != n.x || y != n.y || z != n.z;
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

        T x, y, z;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Normal3<T> &v)
    {
        os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
        return os;
    }

    template <typename T, typename U>
    inline Normal3<T> operator*(U f, const Normal3<T> &n)
    {
        return Normal3<T>(f * n.x, f * n.y, f * n.z);
    }

    template <typename T>
    inline Normal3<T> Normalize(const Normal3<T> &n)
    {
        return n / n.Length();
    }

    template <typename T>
    inline T Dot(const Normal3<T> &n1, const Normal3<T> &n2)
    {
        return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
    }

    template <typename T>
    inline T absDot(const Normal3<T> &n1, const Normal3<T> &n2)
    {
        return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
    }

    template <typename T>
    inline Normal3<T> Faceforward(const Normal3<T> &n, const Normal3<T> &n2)
    {
        return (Dot(n, n2) < 0.f) ? -n : n;
    }

    template <typename T>
    Normal3<T> Abs(const Normal3<T> &v)
    {
        return Normal3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
    }
    using Normal3f = Normal3<PFloat>;

} // namespace platinum