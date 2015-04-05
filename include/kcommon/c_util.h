/*
        common utility types and  funcs.

    (c) livingcreative, 2015

    https://github.com/livingcreative/kcommon

    feel free to use and modify
*/

#pragma once


// not to trash defs with long template declaration
#define TT template <typename T>
#define UF template <typename T> inline


namespace c_util
{
    /*
     -------------------------------------------------------------------------------
     HELPER FUNCTIONS
     -------------------------------------------------------------------------------
    */

    // common min/max functions. ugly "u" prefix is used to avoid conflict with
    // similar preprocessor definitions
    UF T umin(const T a, const T b);
    UF T umax(const T a, const T b);

    // simple exchange function, used to swap two values with help of third variable
    //     i don't know why you should use this instead of std::swap
    UF void exchange(T &a, T &b);

    // clamp value to range [a, b] inclusive
    //     a < b is a must
    //     not to use in critical code path and massive computations unless
    //     you sure your compiler can really optimize it
    UF void clampvalue(T &x, const T a, const T b);
    UF T clamp(const T x, const T a, const T b);

    // "pack" and "exapand" value to/back from normalized range [0, 1] from/to [a, b] range
    //     use with floating point values only (float, double)
    UF T normalizevalue(const T value, const T a, const T b);
    UF T expandvalue(const T normalized, const T a, const T b);

    // just linear blend from a to b using factor (should be in range [0, 1])
    //     use with floating point values only (float, double)
    UF T mix(const T a, const T b, const T factor);

    // don't know why anybody may want to use these next funcs
    //     result = m1 * m2 / d
    UF T muldiv(const T m1, const T m2, const T d);
    //     "round" integer divide, use with integer values only
    //     if division reminder is greater than a divisor half, result is incremented by 1
    UF T rounddiv(const T a, const T b);
    //     "round" floating point value to int, just (int)(value + 0.5)
    template <typename R, typename T> inline R round(const T value);
    UF int roundint(const T value);

    // floating point equality comparision with epsilon value
    //     it uses "abs" function, so it should be defined somewhere,
    //     one from <stdlib.h> or <cmath> is suitable
    UF bool equal(const T a, const T b, const T e);
    // inclusive range check value
    //     a < b is a must
    UF bool inrange(const T value, const T a, const T b);

    // "booleanize" value
    //     result is either 0 or 1
    UF int bint(const T value);
    // take value sign only
    //     result is -1 for negative value, 0 for zero and +1 for positive value
    UF T sign(const T value);


    /*
     -------------------------------------------------------------------------------
     pointT<T>
     -------------------------------------------------------------------------------
         2D point template
         simple struct for 2D point representation with some useful funcs
            x, y - point coordinates
    */

    template <typename T>
    struct pointT
    {
        T x;
        T y;

        // constructors
        //     for 0 coord point
        inline pointT();
        //     same single value for every coord
        inline pointT(T value);
        //     individual coordinate values
        inline pointT(T _x, T _y);
        //     explicit constructor for quick conversion between different point types
        template <typename Tx> explicit inline pointT(const pointT<Tx> &point);

        // every day use operators (maybe except * and /)
        inline pointT<T> operator=(T value);
        inline bool      operator==(const pointT<T> p) const;
        inline bool      operator!=(const pointT<T> p) const;
        inline pointT<T> operator+(const pointT<T> p) const;
        inline pointT<T> operator-(const pointT<T> p) const;
        inline pointT<T> operator-() const;
        inline pointT<T> operator*(const pointT<T> p) const;
        inline pointT<T> operator/(const pointT<T> p) const;

        // squared distance between two points
        inline T sqrdist(const pointT<T> &p) const;
    };

    // most common point types (i think)
    typedef pointT<float>  CPointF,     *PCPointF;
    typedef pointT<double> CPointD,     *PCPointD;
    typedef pointT<int>    CPoint,      *PCPoint;
    typedef pointT<short>  CSmallPoint, *PCSmallPoint;



    ////////////////////////////////////////////////////////////////////////////////

    // HELPER FUNCTIONS IMPLEMENTATION

    UF T umin(const T a, const T b)
    {
        return (a < b) ? a : b;
    }

    UF T umax(const T a, const T b)
    {
        return (a > b) ? a : b;
    }

    UF void exchange(T &a, T &b)
    {
        T t = a;
        a = b;
        b = t;
    }

    UF void clampvalue(T &x, const T a, const T b)
    {
        x = umax(a, umin(x, b));
    }

    UF T clamp(const T x, const T a, const T b)
    {
        return umax(a, umin(x, b));
    }

    UF T normalizevalue(const T value, const T a, const T b)
    {
        return clamp((value - a) / (b - a), T(0), T(1));
    }

    UF T expandvalue(const T normalized, const T a, const T b)
    {
        return normalized * (b - a) + a;
    }

    UF T mix(const T a, const T b, const T factor)
    {
        return a * (T(1) - factor) + b * factor;
    }

    UF T muldiv(const T m1, const T m2, const T d)
    {
        return (m1 * m2) / d;
    }

    UF T rounddiv(const T a, const T b)
    {
        T result = a / b;
        if ((a % b) > (b / 2)) {
            ++result;
        }
        return result;
    }

    template <typename R, typename T> inline R round(const T value)
    {
        return static_cast<R>(value + T(0.5));
    }

    UF int roundint(const T value)
    {
        return round<int>(value);
    }

    UF bool equal(const T a, const T b, const T e)
    {
        return abs(a - b) < e;
    }

    UF bool inrange(const T value, const T a, const T b)
    {
        return (value >= a) && (value <= b);
    }

    UF int bint(const T value)
    {
        return value == 0 ? 0 : 1;
    }

    UF T sign(const T value)
    {
        if (value < 0) {
            return T(-1);
        }

        if (value > 0) {
            return T(+1);
        }

        return T(0);
    }


    // pointT<T> IMPLEMENTATION

    TT pointT<T>::pointT() :
        x(0), y(0)
    {}

    TT pointT<T>::pointT(T value) :
        x(value), y(value)
    {}

    TT pointT<T>::pointT(T _x, T _y) :
        x(_x), y(_y)
    {}

    TT template <typename Tx> pointT<T>::pointT(const pointT<Tx> &point) :
        x(static_cast<T>(point.x)),
        y(static_cast<T>(point.y))
    {}

    TT pointT<T> pointT<T>::operator=(T value)
    {
        x = y = value;
        return *this;
    }

    TT bool pointT<T>::operator==(const pointT<T> p) const
    {
        return x == p.x && y == p.y;
    }

    TT bool pointT<T>::operator!=(const pointT<T> p) const
    {
        return x != p.x || y != p.y;
    }

    TT pointT<T> pointT<T>::operator+(const pointT<T> p) const
    {
        return pointT<T>(x + p.x, y + p.y);
    }

    TT pointT<T> pointT<T>::operator-(const pointT<T> p) const
    {
        return pointT<T>(x - p.x, y - p.y);
    }

    TT pointT<T> pointT<T>::operator-() const
    {
        return pointT<T>(-x, -y);
    }

    TT pointT<T> pointT<T>::operator*(const pointT<T> p) const
    {
        return pointT<T>(x * p.x, y * p.y);
    }

    TT pointT<T> pointT<T>::operator/(const pointT<T> p) const
    {
        return pointT<T>(x / p.x, y / p.y);
    }

    TT T pointT<T>::sqrdist(const pointT<T> &p) const
    {
        return (p.x - x) * (p.y - y);
    }

} // namespace c_util

// undefine internally used macro
#undef UF
#undef TT
