/*
        common utility types and funcs.

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
    // some forward type declarations
    // forwards
    TT struct pointT; // 2D point representation with x, y coords
    TT struct sizeT;  // 2D size  representation with width, height dimensions
    TT struct rectT;  // 2D rectangle representation


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

    TT struct pointT
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
        inline pointT<T> operator*(const T value) const;
        inline pointT<T> operator/(const T value) const;
        inline pointT<T> operator*(const pointT<T> p) const;
        inline pointT<T> operator/(const pointT<T> p) const;

        // squared distance between two points
        inline T sqrdist(const pointT<T> &p) const;

        // "expand" point into rectangle centered around point
        inline rectT<T> expand(T value) const;
        inline rectT<T> expand(T _x, T _y) const;
    };

    // most common point types (i think)
    typedef pointT<float>  CPointF,     *PCPointF;
    typedef pointT<double> CPointD,     *PCPointD;
    typedef pointT<int>    CPoint,      *PCPoint;
    typedef pointT<short>  CSmallPoint, *PCSmallPoint;


    /*
     -------------------------------------------------------------------------------
     sizeT<T>
     -------------------------------------------------------------------------------
         2D size template
         simple struct for 2D size representation with some useful funcs
            width, height - width and height dimensions
    */

    TT struct sizeT
    {
        T width;
        T height;

        // constructors
        //     for 0 size
        inline sizeT();
        //     for "square" size (width = height)
        inline sizeT(T value);
        //     for usual size with indiviudal values for width and height
        inline sizeT(T w, T h);
        //     explicit constructor for quick conversion between different size types
        template <typename Tx> explicit inline sizeT(const sizeT<Tx> &size);

        // every day use operators
        inline sizeT<T> operator=(T value);
        inline bool operator==(const sizeT<T> p) const;
        inline bool operator!=(const sizeT<T> p) const;

        // "check" functions
        //     empty() returns true if either width and height are 0
        inline bool empty() const;
        //     null() return true if both width and height are 0
        inline bool null() const;

        // flip width and height values
        inline void flip();
    };

    // most common size types (i think)
    typedef sizeT<int>    CSize,       *PCSize;
    typedef sizeT<float>  CSizeF,      *PCSizeF;
    typedef sizeT<double> CSizeD,      *PCSizeD;
    typedef sizeT<short>  CSmallSize,  *PCSmallSize;


    /*
     -------------------------------------------------------------------------------
     rectT<T>
     -------------------------------------------------------------------------------
         2D rectangle template
         simple struct for 2D rectangle representation with some useful funcs
            left, top - left top corner coordinates
            right, bottom - right bottom corner coordinates

            right, bottom values are treated as NON INCLUSIVE edges
    */

    TT struct rectT
    {
        T left;
        T top;
        T right;
        T bottom;

        // constructors
        //     for empty rectangle at (0, 0)
        inline rectT();
        //     for rectangle with specific values for each corner
        inline rectT(T _left, T _top, T _right, T _bottom);
        //     for rectangle from two points
        inline rectT(const pointT<T> lefttop, const pointT<T> rightbottom);
        //     for rectangle from left top point and size
        inline rectT(const pointT<T> lefttop, const sizeT<T> size);
        //     explicit constructor for quick conversion between different rect types
        template <typename Tx> explicit inline rectT(const rectT<Tx> &rect);

        // make rectangle from center point and size
        static inline rectT<T> rectAt(const pointT<T> center, const sizeT<T> size);

        // every day use operators
        inline rectT<T> operator=(const sizeT<T> value);
        inline bool operator==(const rectT<T> p) const;
        inline bool operator!=(const rectT<T> p) const;
        //     adding/subracting point moves whole rect
        inline rectT<T> operator+(const pointT<T> p) const;
        inline rectT<T> operator-(const pointT<T> p) const;
        //     adding rect is "union" operation, composes rect which contains both
        inline rectT<T> operator+(const rectT<T> r) const;
        //     multiply by rect is "intersection" operation, computes rect intersection
        inline rectT<T> operator*(const rectT<T> r) const;
        //     implicit sizeT conversion, computes rect size (width and height)
        //     size is always positive and computed from normalized rect
        inline operator sizeT<T>() const;

        // "check" functions, same meaning as for pointT
        inline bool empty() const;
        inline bool null() const;

        // compute width() / height() of rectangle, could be negative!
        inline T width() const;
        inline T height() const;
        // rectangle "derivative" points
        inline pointT<T> getLeftTop() const;
        inline pointT<T> getRightBottom() const;
        inline pointT<T> getRightTop() const;
        inline pointT<T> getLeftBottom() const;
        inline pointT<T> getLeftCenter() const;
        inline pointT<T> getTopCenter() const;
        inline pointT<T> getRightCenter() const;
        inline pointT<T> getBottomCenter() const;
        inline pointT<T> getCenter() const;
        inline void setLeftTop(const pointT<T> p);
        inline void setRightBottom(const pointT<T> p);
        inline void setCenter(const pointT<T> p);
        // same as implicit conversion operation, explicit func
        inline sizeT<T> size() const;

        // margin and padding calculation, the difference only in +/- operation
        //     pad() subtract rect values
        inline rectT<T> pad(const rectT<T> padding) const;
        //     extend() add rect values
        inline rectT<T> extend(const rectT<T> margins) const;

        // expand or contract rect using point values
        inline rectT<T> inflate(const pointT<T> p) const;

        // explicit "union" and "intersection" operations (same as +* operators)
        inline rectT<T> unionwith(const rectT<T> r) const;
        inline rectT<T> intersectionwith(const rectT<T> r) const;

        // "test" functions
        //     test for intersection with other rectangle
        inline bool intersects(const rectT<T> r) const;
        //     test for point inclusion
        inline bool contains(const pointT<T> p) const;

        // compute point array bounds and assign them to rect values
        //     bounds are inclusive! std::numeric_limits required
        void bounds(const pointT<T> *p, size_t count);

        // rectangle normalization (make width and height positive)
        //     normalize inplace
        inline void normalize();
        //     return normalized version of itself
        inline rectT<T> normalized() const;
    };

    // most common rect types (i think)
    typedef rectT<int>    CRect,      *PCRect;
    typedef rectT<float>  CRectF,     *PCRectF;
    typedef rectT<double> CRectD,     *PCRectD;
    typedef rectT<short>  CSmallRect, *PCSmallRect;



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

    TT pointT<T> pointT<T>::operator*(const T value) const
    {
        return pointT<T>(x * value, y * value);
    }

    TT pointT<T> pointT<T>::operator/(const T value) const
    {
        return pointT<T>(x / value, y / value);
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

    TT rectT<T> pointT<T>::expand(T value) const
    {
        return rectT<T>(x - value, y - value, x + value, y + value);
    }

    TT rectT<T> pointT<T>::expand(T _x, T _y) const
    {
        return rectT<T>(x - _x, y - _y, x + _x, y + _y);
    }


    // sizeT<T> IMPLEMENTATION

    TT sizeT<T>::sizeT() :
        width(0), height(0)
    {}

    TT sizeT<T>::sizeT(T value) :
        width(value), height(value)
    {}

    TT sizeT<T>::sizeT(T w, T h) :
        width(w), height(h)
    {}

    TT template <typename Tx> sizeT<T>::sizeT(const sizeT<Tx> &size) :
        width(static_cast<T>(size.width)),
        height(static_cast<T>(size.height))
    {}

    TT sizeT<T> sizeT<T>::operator=(T value)
    {
        width = height = value;
        return *this;
    }

    TT bool sizeT<T>::operator==(const sizeT<T> p) const
    {
        return width == p.width && height == p.height;
    }

    TT bool sizeT<T>::operator!=(const sizeT<T> p) const
    {
        return width != p.width || height != p.height;
    }

    TT bool sizeT<T>::empty() const
    {
        return width == 0 || height == 0;
    }

    TT bool sizeT<T>::null() const
    {
        return width == 0 && height == 0;
    }

    TT void sizeT<T>::flip()
    {
        exchange(width, height);
    }


    // rectT<T> IMPLEMENTATION

    TT rectT<T>::rectT() :
        left(0), top(0), right(0), bottom(0)
    {}

    TT rectT<T>::rectT(T _left, T _top, T _right, T _bottom) :
        left(_left), top(_top), right(_right), bottom(_bottom)
    {}

    TT rectT<T>::rectT(const pointT<T> lefttop, const pointT<T> rightbottom) :
        left(lefttop.x), top(lefttop.y),
        right(rightbottom.x), bottom(rightbottom.y)
    {}

    TT rectT<T>::rectT(const pointT<T> lefttop, const sizeT<T> size) :
        left(lefttop.x), top(lefttop.y),
        right(lefttop.x + size.width), bottom(lefttop.y + size.height)
    {}

    TT template <typename Tx> rectT<T>::rectT(const rectT<Tx> &rect) :
        left(static_cast<T>(rect.left)),
        top(static_cast<T>(rect.top)),
        right(static_cast<T>(rect.right)),
        bottom(static_cast<T>(rect.bottom))
    {}

    TT rectT<T> rectT<T>::rectAt(const pointT<T> center, const sizeT<T> size)
    {
        return rectT<T>(pointT<T>(-size.width / 2, -size.height / 2), size);
    }

    TT rectT<T> rectT<T>::operator=(const sizeT<T> value)
    {
        left = top = 0;
        right = value.width;
        bottom = value.height;
        return *this;
    }

    TT bool rectT<T>::operator==(const rectT<T> p) const
    {
        return left == p.left && top == p.top &&
               right == p.right && bottom == p.bottom;
    }

    TT bool rectT<T>::operator!=(const rectT<T> p) const
    {
        return left != p.left || top != p.top ||
               right != p.right || bottom != p.bottom;
    }

    TT rectT<T> rectT<T>::operator+(const pointT<T> p) const
    {
        return rectT<T>(left + p.x, top + p.y, right + p.x, bottom + p.y);
    }

    TT rectT<T> rectT<T>::operator-(const pointT<T> p) const
    {
        return rectT<T>(left - p.x, top - p.y, right - p.x, bottom - p.y);
    }

    TT rectT<T> rectT<T>::operator+(const rectT<T> p) const
    {
        return unionwith(p);
    }

    TT rectT<T> rectT<T>::operator*(const rectT<T> p) const
    {
        return intersectionwith(p);
    }

    TT rectT<T>::operator sizeT<T>() const
    {
        return size();
    }

    TT bool rectT<T>::empty() const
    {
        return width() == 0 || height() == 0;
    }

    TT bool rectT<T>::null() const
    {
        return width() == 0 && height() == 0;
    }

    TT T rectT<T>::width() const
    {
        return right - left;
    }

    TT T rectT<T>::height() const
    {
        return bottom - top;
    }

    TT pointT<T> rectT<T>::getLeftTop() const
    {
        return pointT<T>(left, top);
    }

    TT pointT<T> rectT<T>::getRightBottom() const
    {
        return pointT<T>(right, bottom);
    }

    TT pointT<T> rectT<T>::getRightTop() const
    {
        return pointT<T>(right, top);
    }

    TT pointT<T> rectT<T>::getLeftBottom() const
    {
        return pointT<T>(left, bottom);
    }

    TT pointT<T> rectT<T>::getLeftCenter() const
    {
        return pointT<T>(left, top + height() / 2);
    }

    TT pointT<T> rectT<T>::getTopCenter() const
    {
        return pointT<T>(left + width() / 2, top);
    }

    template <typename T> pointT<T> rectT<T>::getRightCenter() const
    {
        return pointT<T>(right, top + height() / 2);
    }

    TT pointT<T> rectT<T>::getBottomCenter() const
    {
        return pointT<T>(left + width() / 2, bottom);
    }

    TT pointT<T> rectT<T>::getCenter() const
    {
        return pointT<T>(left + width() / 2, top + height() / 2);
    }

    TT void rectT<T>::setLeftTop(const pointT<T> p)
    {
        left = p.x;
        top = p.y;
    }

    TT void rectT<T>::setRightBottom(const pointT<T> p)
    {
        right = p.x;
        bottom = p.y;
    }

    TT void rectT<T>::setCenter(const pointT<T> p)
    {
        *this = rectT<T>(p - pointT<T>(width() / 2, height() / 2), size());
    }

    TT sizeT<T> rectT<T>::size() const
    {
        rectT<T> result = normalized();
        return sizeT<T>(result.width(), result.height());
    }

    TT rectT<T> rectT<T>::pad(const rectT<T> padding) const
    {
        T w = c_util::umax<T>(width() - padding.width(), 0);
        T h = c_util::umax<T>(height() - padding.height(), 0);
        return rectT<T>(pointT<T>(left + padding.left, top + padding.top), sizeT<T>(w, h));
    }

    TT rectT<T> rectT<T>::extend(const rectT<T> margins) const
    {
        return rectT<T>(
            left - margins.left, top - margins.top,
            right + margins.right, bottom + margins.bottom
        );
    }

    TT rectT<T> rectT<T>::inflate(const pointT<T> p) const
    {
        rectT<T> result = normalized();
        result.left -= p.x;
        result.right += p.x;
        result.top -= p.y;
        result.bottom += p.y;
        return result;
    }

    TT rectT<T> rectT<T>::unionwith(const rectT<T> r) const
    {
        rectT<T> A = normalized(), B = r.normalized();
        return rectT<T>(
            c_util::umin(A.left, B.left), c_util::umin(A.top, B.top),
            c_util::umax(A.right, B.right), c_util::umax(A.bottom, B.bottom)
        );
    }

    TT rectT<T> rectT<T>::intersectionwith(const rectT<T> r) const
    {
        rectT<T> A = normalized(), B = r.normalized();

        rectT<T> result(
            c_util::umax(A.left, B.left), c_util::umax(A.top, B.top),
            c_util::umin(A.right, B.right), c_util::umin(A.bottom, B.bottom)
         );

        if (result.right < result.left) {
            result.right = result.left;
        }
        if (result.bottom < result.top) {
            result.bottom = result.top;
        }

        return result;
    }

    TT bool rectT<T>::intersects(const rectT<T> r) const
    {
        rectT<T> A = normalized(), B = r.normalized();
        return
            (c_util::umin(A.right, B.right) > c_util::umax(A.left, B.left)) &&
            (c_util::umin(A.bottom, B.bottom) > c_util::umax(A.top, B.top));
    }

    TT bool rectT<T>::contains(const pointT<T> p) const
    {
        rectT<T> n = normalized();
        return (p.x >= n.left) && (p.x < n.right) &&
               (p.y >= n.top) && (p.y < bottom);
    }

    TT void rectT<T>::bounds(const pointT<T> *p, size_t count)
    {
        left = (std::numeric_limits<T>::max)();
        top = (std::numeric_limits<T>::max)();
        right = -(std::numeric_limits<T>::max)();
        bottom = -(std::numeric_limits<T>::max)();
        for (size_t n = 0; n < count; n++) {
            left = c_util::umin(p[n].x, left);
            top = c_util::umin(p[n].y, top);
            right = c_util::umax(p[n].x, right);
            bottom = c_util::umax(p[n].y, bottom);
        }
    }

    TT void rectT<T>::normalize()
    {
        left = c_util::umin(left, right);
        top = c_util::umin(top, bottom);
        right = c_util::umax(left, right);
        bottom = c_util::umax(top, bottom);
    }

    TT rectT<T> rectT<T>::normalized() const
    {
        return rectT<T>(
            c_util::umin(left, right), c_util::umin(top, bottom),
            c_util::umax(left, right), c_util::umax(top, bottom)
        );
    }

} // namespace c_util

// undefine internally used macro
#undef UF
#undef TT
