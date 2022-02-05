/*
        common geometric types and funcs.

    (c) livingcreative, 2015

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once

#include "c_util.h"

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
        typedef T type;

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
        inline vec2<T>& operator+=(const vec2<T> &v);
        inline vec2<T>& operator-=(const vec2<T> &v);
        inline vec2<T> operator*(const vec2<T> &v) const;
        inline vec2<T> operator/(const vec2<T> &v) const;
        inline vec2<T> operator*(T scalar) const;
        inline vec2<T> operator/(T scalar) const;
        inline vec2<T>& operator*=(T scalar);
        inline vec2<T>& operator/=(T scalar);
        inline vec2<T> operator-() const;

        template<typename Tp> inline c_util::pointT<Tp> topoint() const;
        template<typename Tp> inline c_util::pointT<Tp> topointrounded() const;

        inline bool equal(const vec2<T> &v, T eps) const;

        inline vec2<T> left() const;
        inline vec2<T> right() const;
        inline T dp(const vec2<T> &v) const;
        inline T cp(const vec2<T> &v) const;
        inline vec2<T> proj(const vec2<T> &v) const;
        inline vec2<T> unitproj(const vec2<T> &v) const;
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
        typedef T type;

        T x;
        T y;
        T z;

        inline vec3();
        inline vec3(T value);
        inline vec3(const vec2<T> &v, T iz = 0);
        inline vec3(T ix, T iy, T iz);

        operator vec2<T>() const;

        inline vec3<T> operator*(T v) const;
        inline vec3<T> operator+(const vec3<T> &v) const;
        inline vec3<T> operator-(const vec3<T> &v) const;
        inline vec3<T> operator-() const;
        inline vec3<T>& operator+=(const vec3<T> &v);
        inline vec3<T>& operator-=(const vec3<T> &v);
        inline vec3<T> operator*(const vec3<T> &v) const;
        inline vec3<T> operator/(const vec3<T> &v) const;

        inline T dp(const vec3<T> &v) const;
        inline vec3<T> cp(const vec3<T> &v) const;
        inline vec3<T> proj(const vec3<T> &v) const;
        inline vec3<T> unitproj(const vec3<T> &v) const;
        inline vec3<T> norm() const;
        inline void normalize();
        inline T sqrlen() const;
        inline T length() const;
        inline T sqrdist(const vec3<T> &p) const;
        inline T distance(const vec3<T> &p) const;

        inline vec3<T> componentwisemin(const vec3<T> &p) const;
        inline vec3<T> componentwisemax(const vec3<T> &p) const;
        inline vec3<T> componentwiseclamp(const vec3<T> &a, const vec3<T> &b) const;
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
        typedef T type;

        T x;
        T y;
        T z;
        T w;

        inline vec4();
        inline vec4(T value);
        inline vec4(T ix, T iy, T iz, T iw = 1);
        inline vec4(const vec2<T> &v, T iz = 0, T iw = 1);
        inline vec4(const vec3<T> &v, T iw = 1);

        operator vec2<T>() const;
        operator vec3<T>() const;

        inline vec4<T> operator*(T scalar) const;
        inline vec4<T> operator/(T scalar) const;

        inline T dp(const vec4<T> &v) const;

        inline vec4<T> norm() const;
        inline void normalize();
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
        typedef T type;

        vec2<T> origin;
        vec2<T> direction;

        inline ray2D();
        inline ray2D(const vec2<T> &_origin, const vec2<T> &_direction);

        inline T distance(const vec2<T> &p) const;
        inline T sqrdist(const vec2<T> &p) const;

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
        typedef T type;

        vec2<T> A;
        vec2<T> B;

        inline segment2D();
        inline segment2D(const vec2<T> &a, const vec2<T> &b);

        inline T length() const;
        inline T sqrlen() const;
        inline vec2<T> dir() const;
        inline vec2<T> normal() const;
        inline vec2<T> vec() const;
        inline vec2<T> proj(const vec2<T> &v) const;

        inline PositionTest test(const vec2<T> &p, T eps) const;
        inline T distance(const vec2<T> &p) const;
        inline T sqrdist(const vec2<T> &p) const;
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
        typedef T type;

        vec3<T> origin;
        vec3<T> direction;

        inline ray3D();
        inline ray3D(const vec3<T> &_origin, const vec3<T> &_direction);

        inline T distance(const vec3<T> &p) const;

        inline bool intersects(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c, vec3<T> &p) const;
        inline bool intersects(const vec3<T> &aa, const vec3<T> &bb) const;

        inline ray3D operator-() const;
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
        typedef T type;

        T m00;
        T m01;
        T m10;
        T m11;

        inline mat2x2();
        inline mat2x2(const vec2<T> &col0, const vec2<T> &col1);
        inline mat2x2(T _m00, T _m01, T _m10, T _m11);

        inline vec2<T> operator*(const vec2<T> &v) const;
        inline mat2x2<T> operator*(const mat2x2<T> &m) const;

        inline void identity();
        inline void transpose();
        inline void scale(T x, T y);
        inline void rotate(T angle);

        inline void scaleby(T x, T y);
        inline void rotateby(T angle);

        struct construct
        {
            static inline mat2x2<T> identity();
            static inline mat2x2<T> scale(T x, T y);
            static inline mat2x2<T> rotate(T angle);
        };
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
        typedef T type;

        T m00;
        T m01;
        T m10;
        T m11;
        T m20;
        T m21;

        inline mat3x2();
        inline mat3x2(const vec2<T> &col0, const vec2<T> &col1);
        inline mat3x2(const vec3<T> &col0, const vec3<T> &col1);
        inline mat3x2(T _m00, T _m01, T _m10, T _m11, T _m20, T _m21);

        inline vec2<T> operator*(const vec2<T> &v) const;
        inline mat3x2<T> operator*(const mat3x2<T> &m) const;

        inline void identity();
        inline void translate(T x, T y);
        inline void scale(T x, T y);
        inline void rotate(T angle);

        inline void translateby(T x, T y);
        inline void scaleby(T x, T y);
        inline void rotateby(T angle);

        struct construct
        {
            static inline mat3x2<T> identity();
            static inline mat3x2<T> translate(T x, T y);
            static inline mat3x2<T> scale(T x, T y);
            static inline mat3x2<T> rotate(T angle);
        };
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
        typedef T type;

        T m[9];

        inline mat3x3();
        inline mat3x3(const vec3<T> &col0, const vec3<T> &col1, const vec3<T> &col2);
        inline mat3x3(
            T _m00, T _m01, T _m02,
            T _m10, T _m11, T _m12,
            T _m20, T _m21, T _m22
        );

        inline operator const T* () const;

        inline const T* data() const;

        inline void identity();

        struct construct
        {
            static inline mat3x3<T> identity();
        };
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
        typedef T type;

        T m[16];

        inline mat4x4();
        inline mat4x4(const mat3x3<T> &source);
        inline mat4x4(const vec3<T> &col0, const vec3<T> &col1, const vec3<T> &col2);
        inline mat4x4(const vec4<T> &col0, const vec4<T> &col1, const vec4<T> &col2, const vec4<T> &col3);
        inline mat4x4(
            T _m00, T _m01, T _m02, T _m03,
            T _m10, T _m11, T _m12, T _m13,
            T _m20, T _m21, T _m22, T _m23,
            T _m30, T _m31, T _m32, T _m33
        );

        inline vec3<T> operator*(const vec3<T> &v) const;
        inline vec4<T> operator*(const vec4<T> &v) const;
        inline mat4x4<T> operator*(const mat4x4<T> &m) const;
        inline operator const T*() const;

        inline const T* data() const;

        inline vec4<T> row(int n) const;
        inline vec4<T> col(int n) const;

        inline void shrink();

        inline void identity();
        inline void transpose();
        inline void inverse();
        inline void translate(T x, T y, T z);
        inline void scale(T x, T y, T z);
        inline void rotate(T angle, const vec3<T> &axis);
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

        inline void extractrotation(T &x, T &y, T &z);
        inline void extractscale(T &x, T &y, T &z);

        struct construct
        {
            static inline mat4x4<T> identity();
            static inline mat4x4<T> translate(T x, T y, T z);
            static inline mat4x4<T> scale(T x, T y, T z);
            static inline mat4x4<T> rotate(T angle, const vec3<T> &axis);
        };
    };

    typedef mat4x4<float> mat4x4f;
    typedef mat4x4<double> mat4x4d;


    /*
     -------------------------------------------------------------------------------
     plane3D<T>
     -------------------------------------------------------------------------------
         3D plane template
    */

    TT struct plane3D
    {
        typedef T type;

        T A;
        T B;
        T C;
        T D;

        inline plane3D();
        inline plane3D(T a, T b, T c, T d);
        inline plane3D(const vec3<T> &_normal, T _distance);
        inline plane3D(const vec3<T> &_normal, const vec3<T> &_origin);
        explicit inline plane3D(const vec4<T> &_plane);
        inline plane3D(const vec3<T> &v1, const vec3<T> &v2, const vec3<T> &v3);

        inline plane3D<T> opposite() const;

        inline vec3<T> normal() const;
        inline T distance() const;
        inline vec3<T> origin() const;
        inline vec3<T> unitx() const;
        inline vec3<T> unity() const;
        inline vec3<T> unitz() const;
        inline void basis(vec3<T> _basis[3]) const;
        inline void basis(vec3<T> &x, vec3<T> &y, vec3<T> &z) const;
        inline void basis(mat3x3<T> &m) const;

        inline void normalize();

        inline T distance(const vec3<T> &p) const;
        inline bool intersects(const ray3D<T> &ray, vec3<T> &ip) const;
        inline bool intersects(const ray3D<T> &ray, vec3<T> &ip, T &d) const;
        inline bool intersectsbothsides(const ray3D<T> &ray, vec3<T> &ip) const;
        inline bool intersectsbothsides(const ray3D<T> &ray, vec3<T> &ip, T &d) const;
        //inline bool intersects(const segment3D<T> &ray, vec3<T> &ip) const;
        //inline bool intersects(const segment3D<T> &ray, vec3<T> &ip, T &d) const;
        inline vec2<T> proj(const vec3<T> &p) const;
        inline vec2<T> proj(const vec3<T> &_origin, const vec3<T> &p) const;
        inline void proj(const vec3<T> *points, size_t count, vec2<T> *result) const;
        inline void proj(const vec3<T> &_origin, const vec3<T> *points, size_t count, vec2<T> *result) const;

        static inline vec2<T> proj(const vec3<T> &_origin, const vec3<T> &p, const vec3<T> &x, const vec3<T> &y);
        static inline vec2<T> proj(const vec3<T> &_origin, const vec3<T> &p, const mat3x3<T> &basismatrix);
        static inline void proj(const vec3<T> &_origin, const vec3<T> *points, size_t count, const vec3<T> &x, const vec3<T> &y, vec2<T> *result);
        static inline void proj(const vec3<T> &_origin, const vec3<T> *points, size_t count, const mat3x3<T> &basismatrix, vec2<T> *result);
    };

    typedef plane3D<float> plane3Df;
    typedef plane3D<double> plane3Dd;



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

    TT vec2<T>& vec2<T>::operator+=(const vec2<T> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    TT vec2<T>& vec2<T>::operator-=(const vec2<T> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
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

    TT vec2<T>& vec2<T>::operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    TT vec2<T>& vec2<T>::operator/=(T scalar)
    {
        T inv = T(1) / scalar;
        x *= inv;
        y *= inv;
        return *this;
    }

    TT vec2<T> vec2<T>::operator-() const
    {
        return vec2<T>(-x, -y);
    }

    TT template <typename Tp> c_util::pointT<Tp> vec2<T>::topoint() const
    {
        return c_util::pointT<Tp>(
            static_cast<Tp>(x),
            static_cast<Tp>(y)
        );
    }

    TT template <typename Tp> c_util::pointT<Tp> vec2<T>::topointrounded() const
    {
        return c_util::pointT<Tp>(
            static_cast<Tp>(x + T(0.5)),
            static_cast<Tp>(y + T(0.5))
        );
    }

    TT bool vec2<T>::equal(const vec2<T> &v, T eps) const
    {
        return c_util::equal(x, v.x, eps) && c_util::equal(y, v.y, eps);
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

    TT T vec2<T>::cp(const vec2<T> &v) const
    {
        // computed as cross product between two 3D vectors
        // with z coord = 0
        // only z coord returned as result (since x and y always be 0)
        return x * v.y - y * v.x;
    }

    TT vec2<T> vec2<T>::proj(const vec2<T> &v) const
    {
        vec2<T> n = norm();
        return n * n.dp(v);
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

    TT vec3<T>::vec3(const vec2<T> &v, T iz)
    {
        x = v.x; y = v.y; z = iz;
    }

    TT vec3<T>::vec3(T ix, T iy, T iz)
    {
        x = ix; y = iy; z = iz;
    }

    TT vec3<T>::operator vec2<T>() const
    {
        return vec2<T>(x, y);
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

    TT vec3<T> vec3<T>::operator-() const
    {
        return vec3<T>(-x, -y, -z);
    }

    TT vec3<T>& vec3<T>::operator+=(const vec3<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    TT vec3<T>& vec3<T>::operator-=(const vec3<T> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }


    TT vec3<T> vec3<T>::operator*(const vec3<T> &v) const
    {
        return vec3<T>(x * v.x, y * v.y, z * v.z);
    }

    TT vec3<T> vec3<T>::operator/(const vec3<T> &v) const
    {
        return vec3<T>(x / v.x, y / v.y, z / v.z);
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

    TT vec3<T> vec3<T>::proj(const vec3<T> &v) const
    {
        vec3<T> n = norm();
        return n * n.dp(v);
    }

    TT vec3<T> vec3<T>::unitproj(const vec3<T> &v) const
    {
        return v * v.dp(v);
    }

    TT vec3<T> vec3<T>::componentwisemin(const vec3<T> &p) const
    {
        return vec3<T>(
            c_util::umin(x, p.x),
            c_util::umin(y, p.y),
            c_util::umin(z, p.z)
        );
    }

    TT vec3<T> vec3<T>::componentwisemax(const vec3<T> &p) const
    {
        return vec3<T>(
            c_util::umax(x, p.x),
            c_util::umax(y, p.y),
            c_util::umax(z, p.z)
        );
    }

    TT vec3<T> vec3<T>::componentwiseclamp(const vec3<T> &a, const vec3<T> &b) const
    {
        return componentwisemax(a).componentwisemin(b);
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

    TT vec4<T>::vec4(const vec2<T> &v, T iz, T iw)
    {
        x = v.x; y = v.y; z = iz; w = iw;
    }

    TT vec4<T>::vec4(const vec3<T> &v, T iw)
    {
        x = v.x; y = v.y; z = v.z; w = iw;
    }

    TT vec4<T>::operator vec2<T>() const
    {
        return vec2<T>(x, y);
    }

    TT vec4<T>::operator vec3<T>() const
    {
        return vec3<T>(x, y, z);
    }

    TT vec4<T> vec4<T>::operator*(T scalar) const
    {
        return vec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    TT vec4<T> vec4<T>::operator/(T scalar) const
    {
        T inv = T(1) / scalar;
        return vec4<T>(x * inv, y * inv, z * inv, w * inv);
    }

    TT T vec4<T>::dp(const vec4<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    TT vec4<T> vec4<T>::norm() const
    {
        T invlen = 1 / sqrt(x * x + y * y + z * z + w * w);
        return vec4<T>(x * invlen, y * invlen, z * invlen, w * invlen);
    }

    TT void vec4<T>::normalize()
    {
        T invlen = 1 / sqrt(x * x + y * y + z * z + w * w);
        x *= invlen;
        y *= invlen;
        z *= invlen;
        w *= invlen;
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

    TT T ray2D<T>::sqrdist(const vec2<T> &p) const
    {
        vec2<T> t = p - origin;
        if (t.zero()) {
            return T(0);
        } else {
            return origin.sqrdist(p) * direction.dp(t.left().norm());
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

    TT T segment2D<T>::length() const
    {
        return A.distance(B);
    }

    TT T segment2D<T>::sqrlen() const
    {
        return A.sqrdist(B);
    }

    TT vec2<T> segment2D<T>::dir() const
    {
        return (B - A).norm();
    }

    TT vec2<T> segment2D<T>::normal() const
    {
        return dir().right();
    }

    TT vec2<T> segment2D<T>::vec() const
    {
        return B - A;
    }

    TT vec2<T> segment2D<T>::proj(const vec2<T> &v) const
    {
        return vec().proj(v - A) + A;
    }

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

    TT T segment2D<T>::sqrdist(const vec2<T> &p) const
    {
        return ray2D<T>(A, B - A).sqrdist(p);
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

    TT bool ray3D<T>::intersects(const vec3<T> &aa, const vec3<T> &bb) const
    {
        vec3<T> invn = vec3<T>(1) / direction;

        vec3<T> t1 = (aa - origin) * invn;
        vec3<T> t2 = (bb - origin) * invn;

        T tmin = c_util::umin(t1.x, t2.x);
        T tmax = c_util::umax(t1.x, t2.x);
        tmin = umax(tmin, umin(t1.y, t2.y));
        tmax = umin(tmax, umax(t1.y, t2.y));
        tmin = umax(tmin, umin(t1.z, t2.z));
        tmax = umin(tmax, umax(t1.z, t2.z));
 
        return tmax >= tmin && tmax >= 0;
    }

    TT ray3D<T> ray3D<T>::operator-() const
    {
        ray3D<T> result;
        result.origin = origin;
        result.direction = -direction;
        return result;
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

    TT mat2x2<T>::mat2x2(const vec2<T> &col0, const vec2<T> &col1) :
        m00(col0.x),
        m01(col1.x),
        m10(col0.y),
        m11(col1.y)
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

    TT mat2x2<T> mat2x2<T>::operator*(const mat2x2<T> &m) const
    {
        return mat2x2<T>(
            m00 * m.m00 + m01 * m.m10,
            m00 * m.m01 + m01 * m.m11,
            m10 * m.m00 + m11 * m.m10,
            m10 * m.m01 + m11 * m.m11
        );
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

    TT void mat2x2<T>::scaleby(T x, T y)
    {
        mat2x2<T> t;
        t.scale(x, y);
        *this = *this * t;
    }

    TT void mat2x2<T>::rotateby(T angle)
    {
        mat2x2<T> t;
        t.rotate(angle);
        *this = *this * t;
    }

    TT mat2x2<T> mat2x2<T>::construct::identity()
    {
        return mat2x2<T>();
    }

    TT mat2x2<T> mat2x2<T>::construct::scale(T x, T y)
    {
        mat2x2<T> result;
        result.scale(x, y);
        return result;
    }

    TT mat2x2<T> mat2x2<T>::construct::rotate(T angle)
    {
        mat2x2<T> result;
        result.rotate(angle);
        return result;
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

    TT mat3x2<T>::mat3x2(const vec2<T> &col0, const vec2<T> &col1) :
        m00(col0.x),
        m01(col1.x),
        m10(col0.y),
        m11(col1.y),
        m20(0),
        m21(0)
    {}

    TT mat3x2<T>::mat3x2(const vec3<T> &col0, const vec3<T> &col1) :
        m00(col0.x),
        m01(col1.x),
        m10(col0.y),
        m11(col1.y),
        m20(col0.z),
        m21(col1.z)
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

    TT mat3x2<T> mat3x2<T>::operator*(const mat3x2<T> &m) const
    {
        return mat3x2<T>(
            m00 * m.m00 + m01 * m.m10,
            m00 * m.m01 + m01 * m.m11,
            m10 * m.m00 + m11 * m.m10,
            m10 * m.m01 + m11 * m.m11,
            m20 * m.m00 + m21 * m.m10 + m.m20,
            m20 * m.m01 + m21 * m.m11 + m.m21
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

    TT void mat3x2<T>::translateby(T x, T y)
    {
        mat3x2<T> t;
        t.translate(x, y);
        *this = *this * t;
    }

    TT void mat3x2<T>::scaleby(T x, T y)
    {
        mat3x2<T> t;
        t.scale(x, y);
        *this = *this * t;
    }

    TT void mat3x2<T>::rotateby(T angle)
    {
        mat3x2<T> t;
        t.rotate(angle);
        *this = *this * t;
    }

    TT mat3x2<T> mat3x2<T>::construct::identity()
    {
        return mat3x2<T>();
    }

    TT mat3x2<T> mat3x2<T>::construct::translate(T x, T y)
    {
        mat3x2<T> result;
        result.translate(x, y);
        return result;
    }

    TT mat3x2<T> mat3x2<T>::construct::scale(T x, T y)
    {
        mat3x2<T> result;
        result.scale(x, y);
        return result;
    }

    TT mat3x2<T> mat3x2<T>::construct::rotate(T angle)
    {
        mat3x2<T> result;
        result.rotate(angle);
        return result;
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

    TT mat3x3<T>::mat3x3(const vec3<T> &col0, const vec3<T> &col1, const vec3<T> &col2)
    {
        m[0] = col0.x; m[1] = col1.x; m[2] = col2.x;
        m[3] = col0.y; m[4] = col1.y; m[5] = col2.y;
        m[6] = col0.z; m[7] = col1.z; m[8] = col2.z;
    }

    TT mat3x3<T>::mat3x3(
        T _m00, T _m01, T _m02,
        T _m10, T _m11, T _m12,
        T _m20, T _m21, T _m22
    )
    {
        m[0] = _m00; m[1] = _m01; m[2] = _m02;
        m[3] = _m10; m[4] = _m11; m[5] = _m12;
        m[6] = _m20; m[7] = _m21; m[8] = _m22;
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

    TT mat3x3<T> mat3x3<T>::construct::identity()
    {
        return mat3x3<T>();
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

    TT mat4x4<T>::mat4x4(const mat3x3<T> &source)
    {
        m[0]  = source.m[0]; m[1]  = source.m[1]; m[2]  = source.m[2]; m[3]  = 0;
        m[4]  = source.m[3]; m[5]  = source.m[4]; m[6]  = source.m[5]; m[7]  = 0;
        m[8]  = source.m[6]; m[9]  = source.m[7]; m[10] = source.m[8]; m[11] = 0;
        m[12] = 0;           m[13] = 0;           m[14] = 0;           m[15] = 1;
    }

    TT mat4x4<T>::mat4x4(const vec3<T> &col0, const vec3<T> &col1, const vec3<T> &col2)
    {
        m[0]  = col0.x; m[1]  = col1.x; m[2]  = col2.x; m[3]  = 0;
        m[4]  = col0.y; m[5]  = col1.y; m[6]  = col2.y; m[7]  = 0;
        m[8]  = col0.z; m[9]  = col1.z; m[10] = col2.z; m[11] = 0;
        m[12] = 0;      m[13] = 0;      m[14] = 0;      m[15] = 1;
    }

    TT mat4x4<T>::mat4x4(const vec4<T> &col0, const vec4<T> &col1, const vec4<T> &col2, const vec4<T> &col3)
    {
        m[0]  = col0.x; m[1]  = col1.x; m[2]  = col2.x; m[3]  = col3.x;
        m[4]  = col0.y; m[5]  = col1.y; m[6]  = col2.y; m[7]  = col3.y;
        m[8]  = col0.z; m[9]  = col1.z; m[10] = col2.z; m[11] = col3.z;
        m[12] = col0.w; m[13] = col1.w; m[14] = col2.w; m[15] = col3.w;
    }

    TT mat4x4<T>::mat4x4(
        T _m00, T _m01, T _m02, T _m03,
        T _m10, T _m11, T _m12, T _m13,
        T _m20, T _m21, T _m22, T _m23,
        T _m30, T _m31, T _m32, T _m33
    )
    {
        m[0]  = _m00; m[1]  = _m01; m[2]  = _m02; m[3]  = _m03;
        m[4]  = _m10; m[5]  = _m11; m[6]  = _m12; m[7]  = _m13;
        m[8]  = _m20; m[9]  = _m21; m[10] = _m22; m[11] = _m23;
        m[12] = _m30; m[13] = _m31; m[14] = _m32; m[15] = _m33;
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
            row(0).dp(m.col(0)), row(0).dp(m.col(1)), row(0).dp(m.col(2)), row(0).dp(m.col(3)),
            row(1).dp(m.col(0)), row(1).dp(m.col(1)), row(1).dp(m.col(2)), row(1).dp(m.col(3)),
            row(2).dp(m.col(0)), row(2).dp(m.col(1)), row(2).dp(m.col(2)), row(2).dp(m.col(3)),
            row(3).dp(m.col(0)), row(3).dp(m.col(1)), row(3).dp(m.col(2)), row(3).dp(m.col(3))
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

    TT void mat4x4<T>::shrink()
    {
        m[3] = 0; m[7] = 0; m[11] = 0;
        m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
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
        mat4x4<T> t(*this);

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

    TT void mat4x4<T>::rotate(T angle, const vec3<T> &axis)
    {
        T a = radians(angle);
        T s = sin(a);
        T c = cos(a);
        T omc = 1 - c;

        m[0] = omc * axis.x * axis.x + c;
        m[1] = omc * axis.x * axis.y - axis.z * s;
        m[2] = omc * axis.z * axis.x + axis.y * s;
        m[3] = 0;

        m[4] = omc * axis.x * axis.y + axis.z * s;
        m[5] = omc * axis.y * axis.y + c;
        m[6] = omc * axis.y * axis.z - axis.x * s;
        m[7] = 0;

        m[8] = omc * axis.z * axis.x - axis.y * s;
        m[9] = omc * axis.y * axis.z + axis.x * s;
        m[10] = omc * axis.z * axis.z + c;
        m[11] = 0;

        m[12] = 0;
        m[13] = 0;
        m[14] = 0;
        m[15] = 1;
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

        if (std::abs(far_ - near_) < T(0.01) || std::abs(s) < T(0.01)) {
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

    TT void mat4x4<T>::extractrotation(T &x, T &y, T &z)
    {
        vec3<T> rows[3] = {
            row(0),
            row(1),
            row(2)
        };

        // compute X scale factor and normalize first row
        rows[0] = rows[0] * rows[0].length();

        // compute XY shear factor and make 2nd row orthogonal to 1st
        T xy = rows[0].dp(rows[1]);
        rows[1] += rows[0] * -xy;

        // now, compute Y scale and normalize 2nd row
        rows[1] = rows[1] * rows[1].length();

        // compute XZ and YZ shears, orthogonalize 3rd row
        T xz = rows[0].dp(rows[2]);
        rows[2] += rows[0] * -xz;

        T yz = rows[1].dp(rows[2]);
        rows[2] += rows[1] *  -yz;

        // next, get Z scale and normalize 3rd row
        rows[2] = rows[2] * rows[2].length();

        // At this point, the matrix (in rows[]) is orthonormal.
        // Check for a coordinate system flip.  If the determinant
        // is -1, then negate the matrix and the scaling factors.
        if (rows[0].dp(rows[1].cp(rows[2])) < 0) {
            rows[0] = rows[0] * -1;
            rows[1] = rows[1] * -1;
            rows[2] = rows[2] * -1;
        }

        // now, get the rotations out, as described in the gem
        y = asin(-rows[0].z);
        if (cos(y) != 0) {
            x = degrees(atan2(rows[1].z, rows[2].z));
            z = degrees(atan2(rows[0].y, rows[0].x));
        } else {
            x = degrees(atan2(rows[1].x, rows[1].y));
            z = 0;
        }
        y = degrees(y);
    }

    TT void mat4x4<T>::extractscale(T &x, T &y, T &z)
    {

    }

    TT mat4x4<T> mat4x4<T>::construct::identity()
    {
        return mat4x4<T>();
    }

    TT mat4x4<T> mat4x4<T>::construct::translate(T x, T y, T z)
    {
        mat4x4<T> result;
        result.translate(x, y, z);
        return result;
    }

    TT mat4x4<T> mat4x4<T>::construct::scale(T x, T y, T z)
    {
        mat4x4<T> result;
        result.scale(x, y, z);
        return result;
    }

    TT mat4x4<T> mat4x4<T>::construct::rotate(T angle, const vec3<T> &axis)
    {
        mat4x4<T> result;
        result.rotate(angle, axis);
        return result;
    }



    /*
     -------------------------------------------------------------------------------
     plane3D<T> implementation
     -------------------------------------------------------------------------------
    */

    TT plane3D<T>::plane3D() :
        A(0), B(0), C(1), D(0)
    {}

    TT plane3D<T>::plane3D(T a, T b, T c, T d) :
        A(a), B(b), C(c), D(d)
    {}

    TT plane3D<T>::plane3D(const vec3<T> &_normal, T _distance) :
        A(_normal.x), B(_normal.y), C(_normal.z), D(_distance)
    {}

    TT plane3D<T>::plane3D(const vec3<T> &_normal, const vec3<T> &_origin) :
        A(_normal.x), B(_normal.y), C(_normal.z), D(_normal.dp(_origin))
    {}

    TT plane3D<T>::plane3D(const vec4<T> &_plane) :
        A(_plane.x), B(_plane.y), C(_plane.z), D(_plane.w)
    {}

    TT plane3D<T>::plane3D(const vec3<T> &v1, const vec3<T> &v2, const vec3<T> &v3)
    {
        vec3<T> normal((v2 - v1).cp(v3 - v1));
        normal.normalize();

        A = normal.x;
        B = normal.y;
        C = normal.z;
        D = normal.dp(v1);
    }

    TT plane3D<T> plane3D<T>::opposite() const
    {
        return plane3D<T>(-A, -B, -C, D);
    }

    TT vec3<T> plane3D<T>::normal() const
    {
        return vec3<T>(A, B, C);
    }

    TT T plane3D<T>::distance() const
    {
        return D;
    }

    TT vec3<T> plane3D<T>::origin() const
    {
        return normal() * D;
    }

    TT vec3<T> plane3D<T>::unitx() const
    {
        vec3<T> x, y, z;
        basis(x, y, z);
        return x;
    }

    TT vec3<T> plane3D<T>::unity() const
    {
        vec3<T> x, y, z;
        basis(x, y, z);
        return y;
    }

    TT vec3<T> plane3D<T>::unitz() const
    {
        return vec3<T>(A, B, C);
    }

    TT void plane3D<T>::basis(vec3<T> _basis[3]) const
    {
        basis(_basis[0], _basis[1], _basis[2]);
    }

    TT void plane3D<T>::basis(vec3<T> &x, vec3<T> &y, vec3<T> &z) const
    {
        z = normal();
        x = vec3f(0, 0, 1).cp(z);
        if (x.sqrlen() <= FLT_EPSILON) {
            x = vec3f(0, 1, 0).cp(z);
        }
        x.normalize();
        y = z.cp(x);
    }

    TT void plane3D<T>::basis(mat3x3<T> &m) const
    {
        vec3<T> x, y, z;
        basis(x, y, z);

        m.m[0] = x.x;
        m.m[1] = y.x;
        m.m[2] = z.x;

        m.m[3] = x.y;
        m.m[4] = y.y;
        m.m[5] = z.y;

        m.m[6] = x.z;
        m.m[7] = y.z;
        m.m[8] = z.z;
    }

    TT void plane3D<T>::normalize()
    {
        vec3<T> n = normal();
        n.normalize();

        A = n.x; B = n.y; C = n.z;
    }

    TT T plane3D<T>::distance(const vec3<T> &p) const
    {
        vec3<T> n = normal();
        return n.dp(p - n * D);
    }

    TT bool plane3D<T>::intersects(const ray3D<T> &ray, vec3<T> &ip) const
    {
        T d;
        return intersects(ray, ip, d);
    }

    TT bool plane3D<T>::intersects(const ray3D<T> &ray, vec3<T> &ip, T &d) const
    {
        vec3<T> n = normal();
        T vd = ray.direction.dp(n);
        if (vd < 0) {
            T v0 = (n * D - ray.origin).dp(n);
            T t = v0 / vd;
            if (t > 0) {
                d = t;
                ip = ray.origin + ray.direction * t;
                return true;
            }
        }

        return false;
    }

    TT bool plane3D<T>::intersectsbothsides(const ray3D<T> &ray, vec3<T> &ip) const
    {
        T d;
        return intersectsbothsides(ray, ip, d);
    }

    TT bool plane3D<T>::intersectsbothsides(const ray3D<T> &ray, vec3<T> &ip, T &d) const
    {
        vec3<T> n = normal();
        T vd = ray.direction.dp(n);
        if (vd != 0) {
            T v0 = (n * D - ray.origin).dp(n);
            T t = v0 / vd;
            if (t > 0) {
                d = t;
                ip = ray.origin + ray.direction * t;
                return true;
            }
        }

        return false;
    }

    TT vec2<T> plane3D<T>::proj(const vec3<T> &p) const
    {
        return proj(origin(), p);
    }

    TT vec2<T> plane3D<T>::proj(const vec3<T> &_origin, const vec3<T> &p) const
    {
        vec3<T> x, y, z;
        basis(x, y, z);
        return proj(_origin, p, x, y);
    }

    TT void plane3D<T>::proj(const vec3<T> *points, size_t count, vec2<T> *result) const
    {
        proj(origin(), points, count, result);
    }

    TT void plane3D<T>::proj(const vec3<T> &_origin, const vec3<T> *points, size_t count, vec2<T> *result) const
    {
        vec3<T> x, y, z;
        basis(x, y, z);
        proj(_origin, points, count, x, y, result);
    }

    TT vec2<T> plane3D<T>::proj(const vec3<T> &_origin, const vec3<T> &p, const vec3<T> &x, const vec3<T> &y)
    {
        return vec2<T>((p - _origin).dp(x), (p - _origin).dp(y));
    }

    TT vec2<T> plane3D<T>::proj(const vec3<T> &_origin, const vec3<T> &p, const mat3x3<T> &basismatrix)
    {
        return proj(
            _origin, p,
            vec2<T>(basismatrix.m[0], basismatrix.m[3]),
            vec2<T>(basismatrix.m[1], basismatrix.m[4])
        );
    }

    TT void plane3D<T>::proj(const vec3<T> &_origin, const vec3<T> *points, size_t count, const vec3<T> &x, const vec3<T> &y, vec2<T> *result)
    {
        for (size_t n = 0; n < count; ++n) {
            *result++ = proj(_origin, *points++, x, y);
        }
    }

    TT void plane3D<T>::proj(const vec3<T> &_origin, const vec3<T> *points, size_t count, const mat3x3<T> &basismatrix, vec2<T> *result)
    {
        proj(
            _origin, points, count,
            vec2<T>(basismatrix.m[0], basismatrix.m[3]),
            vec2<T>(basismatrix.m[1], basismatrix.m[4]),
            result
        );
    }

} // namespace c_geometry

// undefine internally used macro
#undef UF
#undef TT
