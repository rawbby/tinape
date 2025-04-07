#include <numeric.hpp>
#include <assert.hpp>
#include <geometry.h>

#include <cmath>
#include <type_traits>

template<typename T>
constexpr T
SqrtAdapter(T v)
{
  return static_cast<T>(std::sqrt(v));
}

template<typename T>
void
testVec2(T (*sqrtFunc)(T))
{
  static_assert(!IsVec4<Vec2<T>>);
  static_assert(!IsVec3<Vec2<T>>);
  static_assert(IsVec2<Vec2<T>>);

  // Default constructor
  Vec2<T> v1;
  ASSERT_EQ(v1.x, T{}, "Vec2 default constructor: x should be zero");
  ASSERT_EQ(v1.y, T{}, "Vec2 default constructor: y should be zero");

  // Parameterized constructor
  Vec2<T> v2(T(3), T(4));
  ASSERT_EQ(v2.x, T(3), "Vec2 parameterized constructor: x");
  ASSERT_EQ(v2.y, T(4), "Vec2 parameterized constructor: y");

  // Conversion (copy) constructor
  Vec2<T> v3(v2);
  ASSERT_EQ(v3.x, T(3), "Vec2 copy constructor: x");
  ASSERT_EQ(v3.y, T(4), "Vec2 copy constructor: y");

  // Assignment operator
  Vec2<T> v4;
  v4 = v2;
  ASSERT_EQ(v4.x, T(3), "Vec2 assignment operator: x");
  ASSERT_EQ(v4.y, T(4), "Vec2 assignment operator: y");

  // Addition operator
  Vec2<T> v5 = v2 + Vec2<T>(T(1), T(2));
  ASSERT_EQ(v5.x, T(4), "Vec2 addition operator: x");
  ASSERT_EQ(v5.y, T(6), "Vec2 addition operator: y");

  // Subtraction operator
  Vec2<T> v6 = v2 - Vec2<T>(T(1), T(2));
  ASSERT_EQ(v6.x, T(2), "Vec2 subtraction operator: x");
  ASSERT_EQ(v6.y, T(2), "Vec2 subtraction operator: y");

  // Scalar multiplication operator
  Vec2<T> v7 = v2 * T(2);
  ASSERT_EQ(v7.x, T(6), "Vec2 multiplication operator: x");
  ASSERT_EQ(v7.y, T(8), "Vec2 multiplication operator: y");

  // Scalar division operator
  if constexpr (std::is_floating_point_v<T>) {
    Vec2<T> v8 = v2 / T(2);
    ASSERT_EQ_TOLERANCE(v8.x, T(1.5), T(1e-5), "Vec2 division operator: x");
    ASSERT_EQ_TOLERANCE(v8.y, T(2), T(1e-5), "Vec2 division operator: y");
  } else {
    Vec2<T> v8 = v2 / T(2);
    ASSERT_EQ(v8.x, T(1), "Vec2 division operator (i32): x");
    ASSERT_EQ(v8.y, T(2), "Vec2 division operator (i32): y");
  }

  // Unary negation operator
  Vec2<T> v9 = -v2;
  ASSERT_EQ(v9.x, -T(3), "Vec2 unary negation: x");
  ASSERT_EQ(v9.y, -T(4), "Vec2 unary negation: y");

  // Equality / inequality operators
  Vec2<T> v10(T(3), T(4));
  ASSERT(v2 == v10, "Vec2 equality operator");
  ASSERT(!(v2 != v10), "Vec2 inequality operator (false case)");

  Vec2<T> v11(T(5), T(6));
  ASSERT(v2 != v11, "Vec2 inequality operator (true case)");

  // Abs function
  Vec2<T> v12(-T(3), T(4));
  Vec2<T> absv = Abs(v12);
  ASSERT_EQ(absv.x, T(3), "Vec2 Abs: x");
  ASSERT_EQ(absv.y, T(4), "Vec2 Abs: y");

  // Dot product
  T dot = Dot(v2, v2); // 3*3 + 4*4 = 25
  ASSERT_EQ(dot, T(25), "Vec2 Dot product");

  // Length function
  T len = Length(v2, sqrtFunc);
  if constexpr (std::is_floating_point_v<T>) {
    ASSERT_EQ_TOLERANCE(len, T(5), T(1e-5), "Vec2 Length function");
  } else {
    ASSERT_EQ(len, T(5), "Vec2 Length function (i32)");
  }

  // Normalize function
  Vec2<T> norm = Normalize(v2, sqrtFunc);
  if constexpr (std::is_floating_point_v<T>) {
    T normLen = Length(norm, sqrtFunc);
    ASSERT_EQ_TOLERANCE(normLen, T(1), T(1e-5), "Vec2 Normalize: length should be 1");
  } else {
    // Integer division will yield 0 in normalization
    ASSERT_EQ(norm.x, T(0), "Vec2 Normalize (i32): x");
    ASSERT_EQ(norm.y, T(0), "Vec2 Normalize (i32): y");
  }
}

template<typename T>
void
testVec3(T (*sqrtFunc)(T))
{
  static_assert(!IsVec4<Vec3<T>>);
  static_assert(IsVec3<Vec3<T>>);
  static_assert(!IsVec2<Vec3<T>>);

  // Default constructor
  Vec3<T> v1;
  ASSERT_EQ(v1.x, T{}, "Vec3 default constructor: x should be zero");
  ASSERT_EQ(v1.y, T{}, "Vec3 default constructor: y should be zero");
  ASSERT_EQ(v1.z, T{}, "Vec3 default constructor: z should be zero");

  // Parameterized constructor
  Vec3<T> v2(T(3), T(4), T(5));
  ASSERT_EQ(v2.x, T(3), "Vec3 parameterized constructor: x");
  ASSERT_EQ(v2.y, T(4), "Vec3 parameterized constructor: y");
  ASSERT_EQ(v2.z, T(5), "Vec3 parameterized constructor: z");

  // Copy constructor
  Vec3<T> v3(v2);
  ASSERT_EQ(v3.x, T(3), "Vec3 copy constructor: x");
  ASSERT_EQ(v3.y, T(4), "Vec3 copy constructor: y");
  ASSERT_EQ(v3.z, T(5), "Vec3 copy constructor: z");

  // Assignment operator
  Vec3<T> v4;
  v4 = v2;
  ASSERT_EQ(v4.x, T(3), "Vec3 assignment operator: x");
  ASSERT_EQ(v4.y, T(4), "Vec3 assignment operator: y");
  ASSERT_EQ(v4.z, T(5), "Vec3 assignment operator: z");

  // Addition operator
  Vec3<T> v5 = v2 + Vec3<T>(T(1), T(2), T(3));
  ASSERT_EQ(v5.x, T(4), "Vec3 addition operator: x");
  ASSERT_EQ(v5.y, T(6), "Vec3 addition operator: y");
  ASSERT_EQ(v5.z, T(8), "Vec3 addition operator: z");

  // Subtraction operator
  Vec3<T> v6 = v2 - Vec3<T>(T(1), T(2), T(3));
  ASSERT_EQ(v6.x, T(2), "Vec3 subtraction operator: x");
  ASSERT_EQ(v6.y, T(2), "Vec3 subtraction operator: y");
  ASSERT_EQ(v6.z, T(2), "Vec3 subtraction operator: z");

  // Scalar multiplication operator
  Vec3<T> v7 = v2 * T(2);
  ASSERT_EQ(v7.x, T(6), "Vec3 multiplication operator: x");
  ASSERT_EQ(v7.y, T(8), "Vec3 multiplication operator: y");
  ASSERT_EQ(v7.z, T(10), "Vec3 multiplication operator: z");

  // Scalar division operator
  if constexpr (std::is_floating_point_v<T>) {
    Vec3<T> v8 = v2 / T(2);
    ASSERT_EQ_TOLERANCE(v8.x, T(1.5), T(1e-5), "Vec3 division operator: x");
    ASSERT_EQ_TOLERANCE(v8.y, T(2), T(1e-5), "Vec3 division operator: y");
    ASSERT_EQ_TOLERANCE(v8.z, T(2.5), T(1e-5), "Vec3 division operator: z");
  } else {
    Vec3<T> v8 = v2 / T(2);
    ASSERT_EQ(v8.x, T(1), "Vec3 division operator (i32): x");
    ASSERT_EQ(v8.y, T(2), "Vec3 division operator (i32): y");
    ASSERT_EQ(v8.z, T(2), "Vec3 division operator (i32): z");
  }

  // Unary negation operator
  Vec3<T> v9 = -v2;
  ASSERT_EQ(v9.x, -T(3), "Vec3 unary negation: x");
  ASSERT_EQ(v9.y, -T(4), "Vec3 unary negation: y");
  ASSERT_EQ(v9.z, -T(5), "Vec3 unary negation: z");

  // Equality / inequality operators
  Vec3<T> v10(T(3), T(4), T(5));
  ASSERT(v2 == v10, "Vec3 equality operator");
  ASSERT(!(v2 != v10), "Vec3 inequality operator (false case)");

  Vec3<T> v11(T(6), T(7), T(8));
  ASSERT(v2 != v11, "Vec3 inequality operator (true case)");

  // Abs function
  Vec3<T> v12(-T(3), T(4), -T(5));
  Vec3<T> absv = Abs(v12);
  ASSERT_EQ(absv.x, T(3), "Vec3 Abs: x");
  ASSERT_EQ(absv.y, T(4), "Vec3 Abs: y");
  ASSERT_EQ(absv.z, T(5), "Vec3 Abs: z");

  // Dot product
  T dot = Dot(v2, v2); // 3*3 + 4*4 + 5*5 = 9+16+25 = 50
  ASSERT_EQ(dot, T(50), "Vec3 Dot product");

  // Length function
  T len = Length(v2, sqrtFunc);
  if constexpr (std::is_floating_point_v<T>) {
    ASSERT_EQ_TOLERANCE(len, std::sqrt(T(50)), T(1e-5), "Vec3 Length function");
  } else {
    ASSERT_EQ(len, T(static_cast<i32>(std::sqrt(50))), "Vec3 Length function (i32)");
  }

  // Normalize function
  Vec3<T> norm = Normalize(v2, sqrtFunc);
  if constexpr (std::is_floating_point_v<T>) {
    T normLen = Length(norm, sqrtFunc);
    ASSERT_EQ_TOLERANCE(normLen, T(1), T(1e-5), "Vec3 Normalize: length should be 1");
  } else {
    ASSERT_EQ(norm.x, T(0), "Vec3 Normalize (i32): x");
    ASSERT_EQ(norm.y, T(0), "Vec3 Normalize (i32): y");
    ASSERT_EQ(norm.z, T(0), "Vec3 Normalize (i32): z");
  }
}

template<typename T>
void
testVec4(T (*sqrtFunc)(T))
{
  static_assert(IsVec4<Vec4<T>>);
  static_assert(!IsVec3<Vec4<T>>);
  static_assert(!IsVec2<Vec4<T>>);

  // Default constructor
  Vec4<T> v1;
  ASSERT_EQ(v1.x, T{}, "Vec4 default constructor: x should be zero");
  ASSERT_EQ(v1.y, T{}, "Vec4 default constructor: y should be zero");
  ASSERT_EQ(v1.z, T{}, "Vec4 default constructor: z should be zero");
  ASSERT_EQ(v1.w, T{}, "Vec4 default constructor: w should be zero");

  // Parameterized constructor
  Vec4<T> v2(T(3), T(4), T(5), T(6));
  ASSERT_EQ(v2.x, T(3), "Vec4 parameterized constructor: x");
  ASSERT_EQ(v2.y, T(4), "Vec4 parameterized constructor: y");
  ASSERT_EQ(v2.z, T(5), "Vec4 parameterized constructor: z");
  ASSERT_EQ(v2.w, T(6), "Vec4 parameterized constructor: w");

  // Copy constructor
  Vec4<T> v3(v2);
  ASSERT_EQ(v3.x, T(3), "Vec4 copy constructor: x");
  ASSERT_EQ(v3.y, T(4), "Vec4 copy constructor: y");
  ASSERT_EQ(v3.z, T(5), "Vec4 copy constructor: z");
  ASSERT_EQ(v3.w, T(6), "Vec4 copy constructor: w");

  // Assignment operator
  Vec4<T> v4;
  v4 = v2;
  ASSERT_EQ(v4.x, T(3), "Vec4 assignment operator: x");
  ASSERT_EQ(v4.y, T(4), "Vec4 assignment operator: y");
  ASSERT_EQ(v4.z, T(5), "Vec4 assignment operator: z");
  ASSERT_EQ(v4.w, T(6), "Vec4 assignment operator: w");

  // Addition operator
  Vec4<T> v5 = v2 + Vec4<T>(T(1), T(2), T(3), T(4));
  ASSERT_EQ(v5.x, T(4), "Vec4 addition operator: x");
  ASSERT_EQ(v5.y, T(6), "Vec4 addition operator: y");
  ASSERT_EQ(v5.z, T(8), "Vec4 addition operator: z");
  ASSERT_EQ(v5.w, T(10), "Vec4 addition operator: w");

  // Subtraction operator
  Vec4<T> v6 = v2 - Vec4<T>(T(1), T(2), T(3), T(4));
  ASSERT_EQ(v6.x, T(2), "Vec4 subtraction operator: x");
  ASSERT_EQ(v6.y, T(2), "Vec4 subtraction operator: y");
  ASSERT_EQ(v6.z, T(2), "Vec4 subtraction operator: z");
  ASSERT_EQ(v6.w, T(2), "Vec4 subtraction operator: w");

  // Scalar multiplication operator
  Vec4<T> v7 = v2 * T(2);
  ASSERT_EQ(v7.x, T(6), "Vec4 multiplication operator: x");
  ASSERT_EQ(v7.y, T(8), "Vec4 multiplication operator: y");
  ASSERT_EQ(v7.z, T(10), "Vec4 multiplication operator: z");
  ASSERT_EQ(v7.w, T(12), "Vec4 multiplication operator: w");

  // Scalar division operator
  if constexpr (std::is_floating_point_v<T>) {
    Vec4<T> v8 = v2 / T(2);
    ASSERT_EQ_TOLERANCE(v8.x, T(1.5), T(1e-5), "Vec4 division operator: x");
    ASSERT_EQ_TOLERANCE(v8.y, T(2), T(1e-5), "Vec4 division operator: y");
    ASSERT_EQ_TOLERANCE(v8.z, T(2.5), T(1e-5), "Vec4 division operator: z");
    ASSERT_EQ_TOLERANCE(v8.w, T(3), T(1e-5), "Vec4 division operator: w");
  } else {
    Vec4<T> v8 = v2 / T(2);
    ASSERT_EQ(v8.x, T(1), "Vec4 division operator (i32): x");
    ASSERT_EQ(v8.y, T(2), "Vec4 division operator (i32): y");
    ASSERT_EQ(v8.z, T(2), "Vec4 division operator (i32): z");
    ASSERT_EQ(v8.w, T(3), "Vec4 division operator (i32): w");
  }

  // Unary negation operator
  Vec4<T> v9 = -v2;
  ASSERT_EQ(v9.x, -T(3), "Vec4 unary negation: x");
  ASSERT_EQ(v9.y, -T(4), "Vec4 unary negation: y");
  ASSERT_EQ(v9.z, -T(5), "Vec4 unary negation: z");
  ASSERT_EQ(v9.w, -T(6), "Vec4 unary negation: w");

  // Equality / inequality operators
  Vec4<T> v10(T(3), T(4), T(5), T(6));
  ASSERT(v2 == v10, "Vec4 equality operator");
  ASSERT(!(v2 != v10), "Vec4 inequality operator (false case)");

  Vec4<T> v11(T(7), T(8), T(9), T(10));
  ASSERT(v2 != v11, "Vec4 inequality operator (true case)");

  // Abs function
  Vec4<T> v12(-T(3), T(4), -T(5), T(6));
  Vec4<T> absv = Abs(v12);
  ASSERT_EQ(absv.x, T(3), "Vec4 Abs: x");
  ASSERT_EQ(absv.y, T(4), "Vec4 Abs: y");
  ASSERT_EQ(absv.z, T(5), "Vec4 Abs: z");
  ASSERT_EQ(absv.w, T(6), "Vec4 Abs: w");

  // Dot product
  T dot = Dot(v2, v2); // 3^2+4^2+5^2+6^2 = 9+16+25+36 = 86
  ASSERT_EQ(dot, T(86), "Vec4 Dot product");

  // Length function
  T len = Length(v2, sqrtFunc);
  if constexpr (std::is_floating_point_v<T>) {
    ASSERT_EQ_TOLERANCE(len, std::sqrt(T(86)), T(1e-5), "Vec4 Length function");
  } else {
    ASSERT_EQ(len, T(static_cast<i32>(std::sqrt(86))), "Vec4 Length function (i32)");
  }

  // Normalize function
  Vec4<T> norm = Normalize(v2, sqrtFunc);
  if constexpr (std::is_floating_point_v<T>) {
    T normLen = Length(norm, sqrtFunc);
    ASSERT_EQ_TOLERANCE(normLen, T(1), T(1e-5), "Vec4 Normalize: length should be 1");
  } else {
    ASSERT_EQ(norm.x, T(0), "Vec4 Normalize (i32): x");
    ASSERT_EQ(norm.y, T(0), "Vec4 Normalize (i32): y");
    ASSERT_EQ(norm.z, T(0), "Vec4 Normalize (i32): z");
    ASSERT_EQ(norm.w, T(0), "Vec4 Normalize (i32): w");
  }
}

i32
main()
{
  testVec2<i8>(SqrtAdapter<i8>);
  testVec2<i16>(SqrtAdapter<i16>);
  testVec2<i32>(SqrtAdapter<i32>);
  testVec2<i64>(SqrtAdapter<i64>);
  testVec2<f32>(SqrtAdapter<f32>);
  testVec2<f64>(SqrtAdapter<f64>);
  testVec3<i8>(SqrtAdapter<i8>);
  testVec3<i16>(SqrtAdapter<i16>);
  testVec3<i32>(SqrtAdapter<i32>);
  testVec3<i64>(SqrtAdapter<i64>);
  testVec3<f32>(SqrtAdapter<f32>);
  testVec3<f64>(SqrtAdapter<f64>);
  testVec4<i8>(SqrtAdapter<i8>);
  testVec4<i16>(SqrtAdapter<i16>);
  testVec4<i32>(SqrtAdapter<i32>);
  testVec4<i64>(SqrtAdapter<i64>);
  testVec4<f32>(SqrtAdapter<f32>);
  testVec4<f64>(SqrtAdapter<f64>);
}
