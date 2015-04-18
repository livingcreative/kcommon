/*
        common geometric types and funcs.

    (c) livingcreative, 2015

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include "c_util.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>


// not to trash defs with long template declaration
#define TT template <typename T>
#define UF template <typename T> inline


namespace c_geometry
{
    // radians <-> degrees conversion
    UF T degrees(T radians);
    UF T radians(T degrees);

    // geometric position test result
    enum PositionTest
    {
        ptLiesOn,
        ptLeft,
        ptRight,
        ptIntersects
    };


    /*
     -------------------------------------------------------------------------------
     vec2<T>
     -------------------------------------------------------------------------------
         2D vector template
    */

    TT struct vec2
    {
        T x;
        T y;

        inline vec2();
        inline vec2(T value);
        inline vec2(T ix, T iy);
        template<typename Tp> explicit inline vec2(const c_util::pointT<Tp> &pt);

        inline bool operator==(const vec2<T> &v) const;
        inline bool operator!=(const vec2<T> &v) const;
        inline vec2<T> operator+(const vec2<T> &v) const;
        inline vec2<T> operator-(const vec2<T> &v) const;
        inline vec2<T> operator*(const vec2<T> &v) const;
        inline vec2<T> operator/(const vec2<T> &v) const;
        inline vec2<T> operator*(T scalar) const;
        inline vec2<T> operator/(T scalar) const;
        inline vec2<T> operator-() const;

        template<typename Tp> inline operator c_util::pointT<Tp>() const;

        inline vec2<T> left() const;
        inline vec2<T> right() const;
        inline T dp(const vec2<T> &v) const;
        inline vec2<T> norm() const;
        inline void normalize();
        inline T sqrlen() const;
        inline T length() const;
        inline T sqrdist(const vec2<T> &p) const;
        inline T distance(const vec2<T> &p) const;
        inline bool zero() const;
    };

    // common vector types definition
    typedef vec2<float> vec2f;
    typedef vec2<double> vec2d;


    /*
     -------------------------------------------------------------------------------
     vec3<T>
     -------------------------------------------------------------------------------
         3D vector template
    */

    TT struct vec3
    {
        T x;
        T y;
        T z;

        inline vec3();
        inline vec3(T value);
        inline vec3(const vec2<T> &v, T iz = 0);
        inline vec3(T ix, T iy, T iz);

        inline vec3<T> operator*(T v) const;
        inline vec3<T> operator+(const vec3<T> &v) const;
        inline vec3<T> operator-(const vec3<T> &v) const;

        inline T dp(const vec3<T> &v) const;
        inline vec3<T> cp(const vec3<T> &v) const;

        inline vec3<T> norm() const;
        inline void normalize();
        inline T sqrlen() const;
        inline T length() const;
        inline T sqrdist(const vec3<T> &p) const;
        inline T distance(const vec3<T> &p) const;
    };

    // common vector types definition
    typedef vec3<float> vec3f;
    typedef vec3<double> vec3d;


    /*
     -------------------------------------------------------------------------------
     vec4<T>
     -------------------------------------------------------------------------------
         4D vector template
    */

    TT struct vec4
    {
        T x;
        T y;
        T z;
        T w;

        inline vec4();
        inline vec4(T value);
        inline vec4(T ix, T iy, T iz, T iw = 1);

        operator vec3<T>() const;

        inline T dp(const vec4<T> &v) const;
    };

    typedef vec4<float> vec4f;
    typedef vec4<double> vec4d;


    /*
     -------------------------------------------------------------------------------
     ray2D<T>
     -------------------------------------------------------------------------------
         2D ray template
    */

    TT struct ray2D
    {
        vec2<T> origin;
        vec2<T> direction;

        inline ray2D();
        inline ray2D(const vec2<T> &_origin, const vec2<T> &_direction);

        inline T distance(const vec2<T> &p) const;

        inline bool parallel(const ray2D<T> &r) const;
        inline bool intersects(const ray2D<T> &r, vec2<T> &p) const;

        inline PositionTest test(const vec2<T> &p) const;
        inline PositionTest test(const vec2<T> &p, T eps) const;
    };

    typedef ray2D<float> ray2Df;
    typedef ray2D<double> ray2Dd;


    /*
     -------------------------------------------------------------------------------
     segment2D<T>
     -------------------------------------------------------------------------------
         2D segment template
    */

    TT struct segment2D
    {
        vec2<T> A;
        vec2<T> B;

        inline segment2D();
        inline segment2D(const vec2<T> &a, const vec2<T> &b);

        inline PositionTest test(const vec2<T> &p, T eps) const;
        inline T distance(const vec2<T> &p) const;
        inline bool intersects(const ray2D<T> &r) const;
        inline bool intersects(const segment2D<T> &s, vec2f &ip) const;
    };

    typedef segment2D<float> segment2Df;
    typedef segment2D<double> segment2Dd;



    UF bool dp_test(const vec2<T> &v1, const vec2<T> &v2)
    {
        T t = v1.dp(v2);
        return c_util::equal(t, T(0), FLT_EPSILON) || (t > 0);
    }


    /*
     -------------------------------------------------------------------------------
     ray3D<T>
     -------------------------------------------------------------------------------
         3D ray template
    */

    TT struct ray3D
    {
        vec3<T> origin;
        vec3<T> direction;

        inline ray3D();
        inline ray3D(const vec3<T> &_origin, const vec3<T> &_direction);

        inline T distance(const vec3<T> &p) const;

        inline bool intersects(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c, vec3<T> &p) const;
    };

    typedef ray3D<float> ray3Df;
    typedef ray3D<double> ray3Dd;


    /*
     -------------------------------------------------------------------------------
     mat2x2<T>
     -------------------------------------------------------------------------------
         2х2 matrix template for simple 2D transformations (scale, rotation, skew)
    */

    TT struct mat2x2
    {
        T m00;
        T m01;
        T m10;
        T m11;

        inline mat2x2();
        inline mat2x2(const vec2<T> &row0, const vec2<T> &row1);
        inline mat2x2(T _m00, T _m01, T _m10, T _m11);

        inline vec2<T> operator*(const vec2<T> &v) const;

        inline void identity();
        inline void transpose();
        inline void scale(T x, T y);
        inline void rotate(T angle);
    };

    typedef mat2x2<float> mat2x2f;
    typedef mat2x2<double> mat2x2d;


    /*
     -------------------------------------------------------------------------------
     mat3x2<T>
     -------------------------------------------------------------------------------
         3х2 matrix template for simple 2D transformations (scale, rotation, skew)
         and translation transformation
    */

    TT struct mat3x2
    {
        T m00;
        T m01;
        T m10;
        T m11;
        T m20;
        T m21;

        inline mat3x2();
        inline mat3x2(const vec2<T> &row0, const vec2<T> &row1, const vec2<T> row2);
        inline mat3x2(T _m00, T _m01, T _m10, T _m11, T _m20, T _m21);

        inline vec2<T> operator*(const vec2<T> &v) const;

        inline void identity();
        inline void translate(T x, T y);
        inline void scale(T x, T y);
        inline void rotate(T angle);
    };

    typedef mat3x2<float> mat3x2f;
    typedef mat3x2<double> mat3x2d;


    /*
     -------------------------------------------------------------------------------
     mat3x3<T>
     -------------------------------------------------------------------------------
         3х3 matrix template
    */

    TT struct mat3x3
    {
        T m[9];

        inline mat3x3();
        inline mat3x3(const vec3<T> &row0, const vec3<T> &row1, const vec3<T> &row2);

        inline operator const T* () const;

        inline const T* data() const;

        inline void identity();
    };

    typedef mat3x3<float> mat3x3f;
    typedef mat3x3<double> mat3x3d;



    /*
     -------------------------------------------------------------------------------
     mat4x4<T>
     -------------------------------------------------------------------------------
         4х4 matrix template
    */

    TT struct mat4x4
    {
        T m[16];

        inline mat4x4();
        inline mat4x4(const vec4<T> &row0, const vec4<T> &row1, const vec4<T> &row2, const vec4<T> &row3);

        inline vec3<T> operator*(const vec3<T> &v) const;
        inline vec4<T> operator*(const vec4<T> &v) const;
        inline mat4x4<T> operator*(const mat4x4<T> &m) const;
        inline operator const T*() const;

        inline const T* data() const;

        inline vec4<T> row(int n) const;
        inline vec4<T> col(int n) const;

        inline void identity();
        inline void transpose();
        inline void inverse();
        inline void translate(T x, T y, T z);
        inline void scale(T x, T y, T z);
        inline void rotatex(T angle);
        inline void rotatey(T angle);
        inline void rotatez(T angle);
        inline void lookat(const vec3<T> &from, const vec3<T> &to, const vec3<T> &up);

        inline void translateby(T x, T y, T z);
        inline void scaleby(T x, T y, T z);
        inline void rotatebyx(T angle);
        inline void rotatebyy(T angle);
        inline void rotatebyz(T angle);

        inline void projectionL(T fov, T aspect, T near_, T far_);
    };

    typedef mat4x4<float> mat4x4f;
    typedef mat4x4<double> mat4x4d;



    UF T degrees(T radians)
    {
        return radians * T(1.0 / M_PI) * T(180.0);
    }

    UF T radians(T degrees)
    {
        return degrees * T(M_PI) * T(1.0 / 180.0);
    }




    /*
     -------------------------------------------------------------------------------
     vec2<T> implementation
     -------------------------------------------------------------------------------
    */

    TT vec2<T>::vec2()
    {
        x = 0; y = 0;
    }

    TT vec2<T>::vec2(T value)
    {
        x = value; y = value;
    }

    TT vec2<T>::vec2(T ix, T iy)
    {
        x = ix; y = iy;
    }

    TT template <typename Tp> vec2<T>::vec2(const c_util::pointT<Tp> &pt)
    {
        x = static_cast<T>(pt.x);
        y = static_cast<T>(pt.y);
    }

    TT bool vec2<T>::operator==(const vec2<T> &v) const
    {
        return c_util::equal(x, v.x, FLT_EPSILON) && c_util::equal(y, v.y, FLT_EPSILON);
    }

    TT bool vec2<T>::operator!=(const vec2<T> &v) const
    {
        return !c_util::equal(x, v.x, FLT_EPSILON) || !c_util::equal(y, v.y, FLT_EPSILON);
    }

    TT vec2<T> vec2<T>::operator+(const vec2<T> &v) const
    {
        return vec2<T>(x + v.x, y + v.y);
    }

    TT vec2<T> vec2<T>::operator-(const vec2<T> &v) const
    {
        return vec2<T>(x - v.x, y - v.y);
    }

    TT vec2<T> vec2<T>::operator*(const vec2<T> &v) const
    {
        return vec2<T>(x * v.x, y * v.y);
    }

    TT vec2<T> vec2<T>::operator/(const vec2<T> &v) const
    {
        return vec2<T>(x / v.x, y / v.y);
    }

    TT vec2<T> vec2<T>::operator*(T scalar) const
    {
        return vec2<T>(x * scalar, y * scalar);
    }

    TT vec2<T> vec2<T>::operator/(T scalar) const
    {
        T inv = T(1) / scalar;
        return vec2<T>(x * inv, y * inv);
    }

    TT vec2<T> vec2<T>::operator-() const
    {
        return vec2<T>(-x, -y);
    }

    TT template <typename Tp> vec2<T>::operator c_util::pointT<Tp>() const
    {
        c_util::pointT<Tp> p;
        p.x = static_cast<Tp>(x + 0.5);
        p.y = static_cast<Tp>(y + 0.5);
        return p;
    }

    TT vec2<T> vec2<T>::left() const
    {
        return vec2<T>(-y, x);
    }

    TT vec2<T> vec2<T>::right() const
    {
        return vec2<T>(y, -x);
    }

    TT T vec2<T>::dp(const vec2<T> &v) const
    {
        return x * v.x + y * v.y;
    }

    TT vec2<T> vec2<T>::norm() const
    {
        T invlen = 1 / sqrt(x * x + y * y);
        return vec2<T>(x * invlen, y * invlen);
    }

    TT void vec2<T>::normalize()
    {
        T invlen = 1 / sqrt(x * x + y * y);
        x *= invlen;
        y *= invlen;
    }

    TT T vec2<T>::sqrlen() const
    {
        return x * x + y * y;
    }

    TT T vec2<T>::length() const
    {
        return sqrt(x * x + y * y);
    }

    TT T vec2<T>::sqrdist(const vec2<T> &p) const
    {
        return (p - *this).sqrlen();
    }

    TT T vec2<T>::distance(const vec2<T> &p) const
    {
        return (p - *this).length();
    }

    TT bool vec2<T>::zero() const
    {
        return c_util::equal(x, T(0), FLT_EPSILON) && c_util::equal(y, T(0), FLT_EPSILON);
    }



    /*
     -------------------------------------------------------------------------------
     vec3<T> implementation
     -------------------------------------------------------------------------------
    */

    TT vec3<T>::vec3()
    {
        x = 0; y = 0; z = 0;
    }

    TT vec3<T>::vec3(T value)
    {
        x = value; y = value; z = value;
    }

    TT vec3<T>::vec3(const vec2<T> &v, T iz = 0)
    {
        x = v.x; y = v.y; z = iz;
    }

    TT vec3<T>::vec3(T ix, T iy, T iz)
    {
        x = ix; y = iy; z = iz;
    }

    TT vec3<T> vec3<T>::operator*(T v) const
    {
        return vec3<T>(x * v, y * v, z * v);
    }

    TT vec3<T> vec3<T>::operator+(const vec3<T> &v) const
    {
        return vec3<T>(x + v.x, y + v.y, z + v.z);
    }

    TT vec3<T> vec3<T>::operator-(const vec3<T> &v) const
    {
        return vec3<T>(x - v.x, y - v.y, z - v.z);
    }


    TT vec3<T> vec3<T>::norm() const
    {
        T invlen = 1 / sqrt(x * x + y * y + z * z);
        return vec3<T>(x * invlen, y * invlen, z * invlen);
    }

    TT void vec3<T>::normalize()
    {
        T invlen = 1 / sqrt(x * x + y * y + z * z);
        x *= invlen;
        y *= invlen;
        z *= invlen;
    }

    TT T vec3<T>::sqrlen() const
    {
        return x * x + y * y + z * z;
    }

    TT T vec3<T>::length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    TT T vec3<T>::sqrdist(const vec3<T> &p) const
    {
        return (p - *this).sqrlen();
    }

    TT T vec3<T>::distance(const vec3<T> &p) const
    {
        return (p - *this).length();
    }

    TT T vec3<T>::dp(const vec3<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    TT vec3<T> vec3<T>::cp(const vec3<T> &v) const
    {
        return vec3<T>(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }



    /*
     -------------------------------------------------------------------------------
     vec4<T> implementation
     -------------------------------------------------------------------------------
    */

    TT vec4<T>::vec4()
    {
        x = 0; y = 0; z = 0; w = 1;
    }

    TT vec4<T>::vec4(T value)
    {
        x = value; y = value; z = value; w = 1;
    }

    TT vec4<T>::vec4(T ix, T iy, T iz, T iw)
    {
        x = ix; y = iy; z = iz; w = iw;
    }

    TT vec4<T>::operator vec3<T>() const
    {
        return vec3<T>(x, y, z);
    }

    TT T vec4<T>::dp(const vec4<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }



    /*
     -------------------------------------------------------------------------------
     ray2D<T> implementation
     -------------------------------------------------------------------------------
    */

    TT ray2D<T>::ray2D() :
        origin(),
        direction(T(1), T(0))
    {}

    TT ray2D<T>::ray2D(const vec2<T> &_origin, const vec2<T> &_direction) :
        origin(_origin),
        direction(_direction.norm())
    {}

    TT T ray2D<T>::distance(const vec2<T> &p) const
    {
        vec2<T> t = p - origin;
        if (t.zero()) {
            return T(0);
        } else {
            return origin.distance(p) * direction.dp(t.left().norm());
        }
    }

    TT bool ray2D<T>::parallel(const ray2D<T> &r) const
    {
        return (direction == r.direction) || (direction == -r.direction);
    }

    TT bool ray2D<T>::intersects(const ray2D<T> &r, vec2<T> &p) const
    {
        if (parallel(r)) {
            return false;
        } else {
            vec2<T> v = r.origin - origin;
            // there is no actual difference between taking left/right, but
            // taking dp from q to produce sine means
            // q should be right
            vec2<T> q = direction.right();
            T k = q.dp(v) / q.dp(r.direction);

            p = r.origin - r.direction * k;
            return dp_test(direction, p - origin) && dp_test(r.direction, p - r.origin);
        }
    }

    TT PositionTest ray2D<T>::test(const vec2<T> &p) const
    {
        return test(p, FLT_EPSILON);
    }

    TT PositionTest ray2D<T>::test(const vec2<T> &p, T eps) const
    {
        T t = direction.right().dp(p - origin);
        if (c_util::equal(t, T(0), eps)) {
            return ptLiesOn;
        } else if (t < T(0)) {
            return ptLeft;
        } else {
            return ptRight;
        }
    }



    /*
     -------------------------------------------------------------------------------
     segment2D<T> implementation
     -------------------------------------------------------------------------------
    */

    TT segment2D<T>::segment2D() :
        A(),
        B()
    {}

    TT segment2D<T>::segment2D(const vec2<T> &a, const vec2<T> &b) :
        A(a),
        B(b)
    {}

    TT PositionTest segment2D<T>::test(const vec2<T> &p, T eps) const
    {
        T t = (B - A).right().dp(p - A);
        if (c_util::equal(t, T(0), eps)) {
            return ptLiesOn;
        } else if (t < T(0)) {
            return ptLeft;
        } else {
            return ptRight;
        }
    }

    TT T segment2D<T>::distance(const vec2<T> &p) const
    {
        return ray2D<T>(A, B - A).distance(p);
    }

    TT bool segment2D<T>::intersects(const ray2D<T> &r) const
    {
        // point can be at segment ends inclusively
        // in eps radius
        ray2D<T> rT(A, B - A);
        vec2<T> ip;
        return rT.intersects(r, ip) && dp_test(-rT.direction, ip - B);
    }

    TT bool segment2D<T>::intersects(const segment2D<T> &s, vec2f &ip) const
    {
        ray2D<T> rA = ray2D<T>(A, B - A);
        ray2D<T> rB = ray2D<T>(s.A, s.B - s.A);
        return rA.intersects(rB, ip) && dp_test(rA.direction, B - ip) &&
               dp_test(rB.direction, s.B - ip);
    }



    /*
     -------------------------------------------------------------------------------
     ray3D<T> implementation
     -------------------------------------------------------------------------------
    */

    TT ray3D<T>::ray3D() :
        origin(),
        direction(T(1), T(0), T(0))
    {}

    TT ray3D<T>::ray3D(const vec3<T> &_origin, const vec3<T> &_direction) :
        origin(_origin),
        direction(_direction.norm())
    {}

    TT T ray3D<T>::distance(const vec3<T> &p) const
    {
        // TODO
        return T(0);
    }

    TT bool ray3D<T>::intersects(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c, vec3<T> &p) const
    {
        vec3<T> e1 = b - a;
        vec3<T> e2 = c - a;

        vec3<T> pv = direction.cp(e2);
        T det = e1.dp(pv);

        // TODO: epsilon
        if (det < T(0.0001))
            return false;

        det = T(1) / det;

        vec3<T> tv = origin - a;
        T u = tv.dp(pv) * det;
        if (u < T(0) || u > T(1))
            return false;

        vec3<T> qv = tv.cp(e1);
        T v = direction.dp(qv) * det;
        if (v < T(0) || (u + v) > T(1))
            return false;

        T t = e2.dp(qv) * det;
        if (t <= T(0))
            return false;

        p = origin + direction * t;
        return true;
    }



    /*
     -------------------------------------------------------------------------------
     mat2x2<T> implementation
     -------------------------------------------------------------------------------
    */

    TT mat2x2<T>::mat2x2()
    {
        identity();
    }

    TT mat2x2<T>::mat2x2(const vec2<T> &row0, const vec2<T> &row1) :
        m00(row0.x),
        m01(row0.y),
        m10(row1.x),
        m11(row1.y)
    {}

    TT mat2x2<T>::mat2x2(T _m00, T _m01, T _m10, T _m11) :
        m00(_m00),
        m01(_m01),
        m10(_m10),
        m11(_m11)
    {}

    TT vec2<T> mat2x2<T>::operator*(const vec2<T> &v) const
    {
        return vec2<T>(v.x * m00 + v.y * m10, v.x * m01 + v.y * m11);
    }

    TT void mat2x2<T>::identity()
    {
        m00 = T(1);
        m01 = T(0);
        m10 = T(0);
        m11 = T(1);
    }

    TT void mat2x2<T>::transpose()
    {
        mat2x2<T> t(m00, m10, m01, m11);
        this = t;
    }

    TT void mat2x2<T>::scale(T x, T y)
    {
        m00 = x;
        m01 = 0;
        m10 = 0;
        m11 = y;
    }

    TT void mat2x2<T>::rotate(T angle)
    {
        T s, c;
        angle = radians(angle);
        s = sin(angle);
        c = cos(angle);
        m00 = c;
        m01 = -s;
        m10 = s;
        m11 = c;
    }



    /*
     -------------------------------------------------------------------------------
     mat3x2<T> implementation
     -------------------------------------------------------------------------------
    */

    TT mat3x2<T>::mat3x2()
    {
        identity();
    }

    TT mat3x2<T>::mat3x2(const vec2<T> &row0, const vec2<T> &row1, const vec2<T> row2) :
        m00(row0.x),
        m01(row0.y),
        m10(row1.x),
        m11(row1.y),
        m20(row2.x),
        m21(row2.y)
    {}

    TT mat3x2<T>::mat3x2(T _m00, T _m01, T _m10, T _m11, T _m20, T _m21) :
        m00(_m00),
        m01(_m01),
        m10(_m10),
        m11(_m11),
        m20(_m20),
        m21(_m21)
    {}

    TT vec2<T> mat3x2<T>::operator*(const vec2<T> &v) const
    {
        return vec2<T>(
            v.x * m00 + v.y * m10 + m20,
            v.x * m01 + v.y * m11 + m21
        );
    }

    TT void mat3x2<T>::identity()
    {
        m00 = T(1);
        m01 = T(0);
        m10 = T(0);
        m11 = T(1);
        m20 = T(0);
        m21 = T(0);
    }

    TT void mat3x2<T>::translate(T x, T y)
    {
        m00 = T(1);
        m01 = T(0);
        m10 = T(0);
        m11 = T(1);
        m20 = T(x);
        m21 = T(y);
    }

    TT void mat3x2<T>::scale(T x, T y)
    {
        m00 = T(x);
        m01 = T(0);
        m10 = T(0);
        m11 = T(y);
        m20 = T(0);
        m21 = T(0);
    }

    TT void mat3x2<T>::rotate(T angle)
    {
        T s, c;
        angle = radians(angle);
        s = sin(angle);
        c = cos(angle);
        m00 = c;
        m01 = -s;
        m10 = s;
        m11 = c;
        m20 = T(0);
        m21 = T(0);
    }



    /*
     -------------------------------------------------------------------------------
     mat3x3<T> implementation
     -------------------------------------------------------------------------------
    */

    TT mat3x3<T>::mat3x3()
    {
        identity();
    }

    TT mat3x3<T>::mat3x3(const vec3<T> &row0, const vec3<T> &row1, const vec3<T> &row2)
    {
        m[0] = row0.x; m[1] = row0.y; m[2] = row0.z;
        m[3] = row1.x; m[4] = row1.y; m[5] = row1.z;
        m[6] = row2.x; m[7] = row2.y; m[8] = row2.z;
    }

    TT mat3x3<T>::operator const T*() const
    {
        return &m[0];
    }

    TT const T* mat3x3<T>::data() const
    {
        return &m[0];
    }

    TT void mat3x3<T>::identity()
    {
        m[0] = 1; m[1] = 0; m[2] = 0;
        m[3] = 0; m[4] = 1; m[5] = 0;
        m[6] = 0; m[7] = 0; m[8] = 1;
    }



    /*
     -------------------------------------------------------------------------------
     mat4x4<T> implementation
     -------------------------------------------------------------------------------
    */

    TT mat4x4<T>::mat4x4()
    {
        identity();
    }

    TT mat4x4<T>::mat4x4(const vec4<T> &row0, const vec4<T> &row1, const vec4<T> &row2, const vec4<T> &row3)
    {
        m[0] = row0.x; m[1] = row0.y; m[2] = row0.z; m[3] = row0.w;
        m[4] = row1.x; m[5] = row1.y; m[6] = row1.z; m[7] = row1.w;
        m[8] = row2.x; m[9] = row2.y; m[10] = row2.z; m[11] = row2.w;
        m[12] = row3.x; m[13] = row3.y; m[14] = row3.z; m[15] = row3.w;
    }

    TT vec3<T> mat4x4<T>::operator*(const vec3<T> &v) const
    {
        return vec3<T>(
            v.x * m[0] + v.y * m[4] + v.z * m[8] + m[12],
            v.x * m[1] + v.y * m[5] + v.z * m[9] + m[13],
            v.x * m[2] + v.y * m[6] + v.z * m[10] + m[14]
        );
    }

    TT vec4<T> mat4x4<T>::operator*(const vec4<T> &v) const
    {
        return vec4<T>(
            v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12],
            v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13],
            v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14],
            v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15]
        );
    }

    TT mat4x4<T> mat4x4<T>::operator*(const mat4x4<T> &m) const
    {
        return mat4x4<T>(
            vec4<T>(row(0).dp(m.col(0)), row(0).dp(m.col(1)), row(0).dp(m.col(2)), row(0).dp(m.col(3))),
            vec4<T>(row(1).dp(m.col(0)), row(1).dp(m.col(1)), row(1).dp(m.col(2)), row(1).dp(m.col(3))),
            vec4<T>(row(2).dp(m.col(0)), row(2).dp(m.col(1)), row(2).dp(m.col(2)), row(2).dp(m.col(3))),
            vec4<T>(row(3).dp(m.col(0)), row(3).dp(m.col(1)), row(3).dp(m.col(2)), row(3).dp(m.col(3)))
        );
    }

    TT mat4x4<T>::operator const T*() const
    {
        return &m[0];
    }

    TT const T* mat4x4<T>::data() const
    {
        return &m[0];
    }

    TT vec4<T> mat4x4<T>::row(int n) const
    {
        return vec4<T>(m[0 + n * 4], m[1 + n * 4], m[2 + n * 4], m[3 + n * 4]);
    }

    TT vec4<T> mat4x4<T>::col(int n) const
    {
        return vec4<T>(m[n + 0], m[n + 4], m[n + 8], m[n + 12]);
    }

    TT void mat4x4<T>::identity()
    {
        m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
        m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
        m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    TT void mat4x4<T>::transpose()
    {
        mat4x4<T> t(
            vec4<T>(m[0], m[1], m[2], m[3]),
            vec4<T>(m[4], m[5], m[6], m[7]),
            vec4<T>(m[8], m[9], m[10], m[11]),
            vec4<T>(m[12], m[13], m[14], m[15])
        );

        m[0] = t.m[0]; m[1] = t.m[4]; m[2] = t.m[8]; m[3] = t.m[12];
        m[4] = t.m[1]; m[5] = t.m[5]; m[6] = t.m[9]; m[7] = t.m[13];
        m[8] = t.m[2]; m[9] = t.m[6]; m[10] = t.m[10]; m[11] = t.m[14];
        m[12] = t.m[3]; m[13] = t.m[7]; m[14] = t.m[11]; m[15] = t.m[15];
    }

    TT void mat4x4<T>::inverse()
    {
        T inv[16];

        inv[0] = m[5]  * m[10] * m[15] - 
                 m[5]  * m[11] * m[14] - 
                 m[9]  * m[6]  * m[15] + 
                 m[9]  * m[7]  * m[14] +
                 m[13] * m[6]  * m[11] - 
                 m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] + 
                  m[4]  * m[11] * m[14] + 
                  m[8]  * m[6]  * m[15] - 
                  m[8]  * m[7]  * m[14] - 
                  m[12] * m[6]  * m[11] + 
                  m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9] * m[15] - 
                 m[4]  * m[11] * m[13] - 
                 m[8]  * m[5] * m[15] + 
                 m[8]  * m[7] * m[13] + 
                 m[12] * m[5] * m[11] - 
                 m[12] * m[7] * m[9];

        inv[12] = -m[4]  * m[9] * m[14] + 
                   m[4]  * m[10] * m[13] +
                   m[8]  * m[5] * m[14] - 
                   m[8]  * m[6] * m[13] - 
                   m[12] * m[5] * m[10] + 
                   m[12] * m[6] * m[9];

        inv[1] = -m[1]  * m[10] * m[15] + 
                  m[1]  * m[11] * m[14] + 
                  m[9]  * m[2] * m[15] - 
                  m[9]  * m[3] * m[14] - 
                  m[13] * m[2] * m[11] + 
                  m[13] * m[3] * m[10];

        inv[5] = m[0]  * m[10] * m[15] - 
                 m[0]  * m[11] * m[14] - 
                 m[8]  * m[2] * m[15] + 
                 m[8]  * m[3] * m[14] + 
                 m[12] * m[2] * m[11] - 
                 m[12] * m[3] * m[10];

        inv[9] = -m[0]  * m[9] * m[15] + 
                  m[0]  * m[11] * m[13] + 
                  m[8]  * m[1] * m[15] - 
                  m[8]  * m[3] * m[13] - 
                  m[12] * m[1] * m[11] + 
                  m[12] * m[3] * m[9];

        inv[13] = m[0]  * m[9] * m[14] - 
                  m[0]  * m[10] * m[13] - 
                  m[8]  * m[1] * m[14] + 
                  m[8]  * m[2] * m[13] + 
                  m[12] * m[1] * m[10] - 
                  m[12] * m[2] * m[9];

        inv[2] = m[1]  * m[6] * m[15] - 
                 m[1]  * m[7] * m[14] - 
                 m[5]  * m[2] * m[15] + 
                 m[5]  * m[3] * m[14] + 
                 m[13] * m[2] * m[7] - 
                 m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] + 
                  m[0]  * m[7] * m[14] + 
                  m[4]  * m[2] * m[15] - 
                  m[4]  * m[3] * m[14] - 
                  m[12] * m[2] * m[7] + 
                  m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] - 
                  m[0]  * m[7] * m[13] - 
                  m[4]  * m[1] * m[15] + 
                  m[4]  * m[3] * m[13] + 
                  m[12] * m[1] * m[7] - 
                  m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] + 
                   m[0]  * m[6] * m[13] + 
                   m[4]  * m[1] * m[14] - 
                   m[4]  * m[2] * m[13] - 
                   m[12] * m[1] * m[6] + 
                   m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] + 
                  m[1] * m[7] * m[10] + 
                  m[5] * m[2] * m[11] - 
                  m[5] * m[3] * m[10] - 
                  m[9] * m[2] * m[7] + 
                  m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] - 
                 m[0] * m[7] * m[10] - 
                 m[4] * m[2] * m[11] + 
                 m[4] * m[3] * m[10] + 
                 m[8] * m[2] * m[7] - 
                 m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] + 
                   m[0] * m[7] * m[9] + 
                   m[4] * m[1] * m[11] - 
                   m[4] * m[3] * m[9] - 
                   m[8] * m[1] * m[7] + 
                   m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] - 
                  m[0] * m[6] * m[9] - 
                  m[4] * m[1] * m[10] + 
                  m[4] * m[2] * m[9] + 
                  m[8] * m[1] * m[6] - 
                  m[8] * m[2] * m[5];

        T det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
            return;

        det = 1 / det;

        for (int n = 0; n < 16; ++n) {
            m[n] = inv[n] * det;
        }
    }

    TT void mat4x4<T>::translate(T x, T y, T z)
    {
        m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
        m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
        m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
        m[12] = x; m[13] = y; m[14] = z; m[15] = 1;
    }

    TT void mat4x4<T>::scale(T x, T y, T z)
    {
        m[0] = x; m[1] = 0; m[2] = 0; m[3] = 0;
        m[4] = 0; m[5] = y; m[6] = 0; m[7] = 0;
        m[8] = 0; m[9] = 0; m[10] = z; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    TT void mat4x4<T>::rotatex(T angle)
    {
        T a = radians(angle);
        T s = sin(a);
        T c = cos(a);

        m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
        m[4] = 0; m[5] = c; m[6] = s; m[7] = 0;
        m[8] = 0; m[9] = -s; m[10] = c; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    TT void mat4x4<T>::rotatey(T angle)
    {
        T a = radians(angle);
        T s = sin(a);
        T c = cos(a);

        m[0] = c; m[1] = 0; m[2] = -s; m[3] = 0;
        m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
        m[8] = s; m[9] = 0; m[10] = c; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    TT void mat4x4<T>::rotatez(T angle)
    {
        T a = radians(angle);
        T s = sin(a);
        T c = cos(a);

        m[0] = c; m[1] = s; m[2] = 0; m[3] = 0;
        m[4] = -s; m[5] = c; m[6] = 0; m[7] = 0;
        m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    }

    TT void mat4x4<T>::lookat(const vec3<T> &from, const vec3<T> &to, const vec3<T> &up)
    {
        vec3<T> zaxis = (to - from).norm();
        vec3<T> xaxis = up.cp(zaxis).norm();
        vec3<T> yaxis = zaxis.cp(xaxis);

        m[0] =  xaxis.x;         m[1] =  yaxis.x;         m[2] =  zaxis.x;        m[3] = 0;
        m[4] =  xaxis.y;         m[5] =  yaxis.y;         m[6] =  zaxis.y;        m[7] = 0;
        m[8] =  xaxis.z;         m[9] =  yaxis.z;         m[10] = zaxis.z;        m[11] = 0;
        m[12] = -xaxis.dp(from); m[13] = -yaxis.dp(from); m[14] = -zaxis.dp(from); m[15] = 1;
    }

    TT void mat4x4<T>::translateby(T x, T y, T z)
    {
        mat4x4<T> t;
        t.translate(x, y, z);
        *this = *this * t;
    }

    TT void mat4x4<T>::scaleby(T x, T y, T z)
    {
        mat4x4<T> t;
        t.scale(x, y, z);
        *this = *this * t;
    }

    TT void mat4x4<T>::rotatebyx(T angle)
    {
        mat4x4<T> t;
        t.rotatex(angle);
        *this = *this * t;
    }

    TT void mat4x4<T>::rotatebyy(T angle)
    {
        mat4x4<T> t;
        t.rotatey(angle);
        *this = *this * t;
    }

    TT void mat4x4<T>::rotatebyz(T angle)
    {
        mat4x4<T> t;
        t.rotatez(angle);
        *this = *this * t;
    }

    TT void mat4x4<T>::projectionL(T fov, T aspect, T near_, T far_)
    {
        T fov_r = radians(fov * T(0.5));
        T s = sin(fov_r);
        T c = cos(fov_r);

        if (abs(far_ - near_) < T(0.01) || abs(s) < T(0.01)) {
            return;
        }

        T ct = c / s;

        T w = ct / aspect;
        T h = 1 * ct;
        T Q = far_ / (far_ - near_);

        scale(w, h, Q);
        m[11] = 1;
        m[14] = -Q * near_;
        m[15] = 0;
    }

} // namespace c_geometry

// undefine internally used macro
#undef UF
#undef TT
