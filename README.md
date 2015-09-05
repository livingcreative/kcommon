# kcommon
Common bicycles which will be used in every other repo

## Overview

To use any of kcommon headers add "kcommon/include" to include path. Example of including c_util header:  
`#include "kcommon/c_util.h"`

You could use following headers:
 - c_util.h     - common functions and types
 - c_geometry.h - common functions and types for geometry calculations and linear algebra

## c_util.h

### Overview

This header contains common generic functions and types. All functions have comments and almost self-descriptive.
There are several useful `struct` templates for *point*, *size* and *rectangle* representations. All stuff is declared under `c_util` namespace.

**pointT<T>** template is intended to represent simple 2D point with `x` and `y` coordinates. Point can be constructed from single value (same for both x and y) or pair of values. Two points can be added or subtracted with each other like 2D vectors. Point can be multiplied or divided by scalar value.

**sizeT<T>** template is intended to represent simple 2D dimensions `width` and `height`. All functions of size template are self-descriptive and have comments in header.

**rectT<T>** template is intended to represent 2D rectangle with `left`, `top`, `right` and `bottom`. Rectangle can be "denormalized", this means that its *width* or *height* could be negative (e.g., left is greater than right). The `size()` method or implicit casting to `sizeT` always return normalized (positive) rectangle dimensions. Also, `inflate()`, `unionwith()`, `intersectionwith()`, `intersects()` and `contains()` use normalized internal copy of original rectangle to produce correct result.

### Dependencies
> To use `equal()` function you should define `abs(value)` function, which returns absolute value.  
One from &lt;stdlib.h&gt; or &lt;cmath&gt; is suitable, include one of these headers before

> The `rectT<T>::bounds()` function uses `std::numeric_limits`. You should include &lt;limits&gt; in order to use this function.

## c_geometry.h

### Overview

This header contains functions and types related to geometry. Handy structs for vectors and matrices have common set of methods and organized similalry. Vector types represent n-dimensional points (or vectors) in space. These types are `vec2`, `vec3` and `vec4`. Matrix types represent rectangular matrices with different sizes. These types are `mat2x2`, `mat3x2`, `mat3x3` and `mat4x4`. Other useful types are `ray` and `segment` for 2D and 3D versions of rays (straight infinte line originated at certain point) and segments (straight line between to points).
