#include <assert.hpp>
#include <numeric.hpp>

#include <iostream>
#include <limits>
#include <random>

void
fuzz()
{
  std::random_device rd;
  std::mt19937 gen(rd());

  std::bernoulli_distribution eq_chance{ 0.1 };
  std::uniform_int_distribution dist{
    std::numeric_limits<i8>::lowest(),
    std::numeric_limits<i8>::max()
  };

  constexpr int numPairs = 10'000'000;
  for (int i = 0; i < numPairs; ++i) {
    i8 a, b;
    if (eq_chance(gen)) {
      b = a = dist(gen);
    } else {
      a = dist(gen);
      b = dist(gen);
    }

    const double c = static_cast<double>(a) / static_cast<double>(1 << 4);
    const double d = static_cast<double>(b) / static_cast<double>(1 << 4);

    ASSERT_EQ((c == d), (as_fixed<8, 4>(c) == as_fixed<8, 4>(d)), "%f == %f", c, d);
    ASSERT_EQ((c != d), (as_fixed<8, 4>(c) != as_fixed<8, 4>(d)), "%f != %f", c, d);
    ASSERT_EQ((c <= d), (as_fixed<8, 4>(c) <= as_fixed<8, 4>(d)), "%f <= %f", c, d);
    ASSERT_EQ((c >= d), (as_fixed<8, 4>(c) >= as_fixed<8, 4>(d)), "%f >= %f", c, d);
    ASSERT_EQ((c < d), (as_fixed<8, 4>(c) < as_fixed<8, 4>(d)), "%f < %f", c, d);
    ASSERT_EQ((c > d), (as_fixed<8, 4>(c) > as_fixed<8, 4>(d)), "%f > %f", c, d);

    ASSERT_EQ((d == c), (as_fixed<8, 4>(d) == as_fixed<8, 4>(c)), "%f == %f", c, d);
    ASSERT_EQ((d != c), (as_fixed<8, 4>(d) != as_fixed<8, 4>(c)), "%f != %f", c, d);
    ASSERT_EQ((d <= c), (as_fixed<8, 4>(d) <= as_fixed<8, 4>(c)), "%f <= %f", c, d);
    ASSERT_EQ((d >= c), (as_fixed<8, 4>(d) >= as_fixed<8, 4>(c)), "%f >= %f", c, d);
    ASSERT_EQ((d < c), (as_fixed<8, 4>(d) < as_fixed<8, 4>(c)), "%f < %f", c, d);
    ASSERT_EQ((d > c), (as_fixed<8, 4>(d) > as_fixed<8, 4>(c)), "%f > %f", c, d);
  }
}

int
main()
{
  fuzz();

  static_assert(as_fixed_v<0.0>.repr == 0);
  static_assert(as_fixed_v<-1.0>.repr == 1);
  static_assert(as_fixed_v<1.0>.repr == 1);

  static_assert((as_fixed_v<1.0> - as_fixed_v<1.0>).repr == 0);
  static_assert((as_fixed_v<0.0> - as_fixed_v<0.0>).repr == 0);
  static_assert((as_fixed_v<-1.0> - as_fixed_v<-1.0>).repr == 0);

  static_assert(as_fixed_v<1.0> != as_fixed_v<0.0>);
  static_assert(as_fixed_v<1.0> != as_fixed_v<-1.0>);
  static_assert(as_fixed_v<0.0> != as_fixed_v<1.0>);
  static_assert(as_fixed_v<0.0> != as_fixed_v<-1.0>);
  static_assert(as_fixed_v<-1.0> != as_fixed_v<1.0>);
  static_assert(as_fixed_v<-1.0> != as_fixed_v<0.0>);

  static_assert(as_fixed_v<1.0> > as_fixed_v<0.0>);
  static_assert(as_fixed_v<1.0> > as_fixed_v<-1.0>);
  static_assert(as_fixed_v<0.0> < as_fixed_v<1.0>);
  static_assert(as_fixed_v<0.0> > as_fixed_v<-1.0>);
  static_assert(as_fixed_v<-1.0> < as_fixed_v<1.0>);
  static_assert(as_fixed_v<-1.0> < as_fixed_v<0.0>);

  const auto hi = Fixed<VAR, 4, -2>{ 1.0 };
  const auto nil = Fixed<VAR, 4, -2>{ 0.0 };
  const auto lo = Fixed<VAR, 4, -2>{ -1.0 };

  ASSERT(!(nil.repr > 0));
  ASSERT(!(nil.repr < 0));

  ASSERT_EQ(nil.repr, 0);
  ASSERT_EQ(lo.repr, -0b01'00);
  ASSERT_EQ(hi.repr, 0b01'00);

  ASSERT(nil == nil);
  ASSERT(lo == lo);
  ASSERT(hi == hi);

  ASSERT(nil != lo);
  ASSERT(nil != hi);
  ASSERT(lo != nil);
  ASSERT(lo != hi);
  ASSERT(hi != nil);
  ASSERT(hi != lo);

  ASSERT(hi > nil);
  ASSERT(hi > lo);
  ASSERT(nil < hi);
  ASSERT(nil > lo);
  ASSERT(lo < hi);
  ASSERT(lo < nil);
}
