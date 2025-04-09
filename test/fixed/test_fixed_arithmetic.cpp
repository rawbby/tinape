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

    ASSERT_EQ((as_fixed<32, 16>(c + d)), (as_fixed<8, 4>(c) + as_fixed<8, 4>(d)), "%f + %f", c, d);
    ASSERT_EQ((as_fixed<32, 16>(c - d)), (as_fixed<8, 4>(c) - as_fixed<8, 4>(d)), "%f - %f", c, d);
    ASSERT_EQ((as_fixed<32, 16>(c * d)), (as_fixed<8, 4>(c) * as_fixed<8, 4>(d)), "%f * %f", c, d);

    ASSERT_EQ((as_fixed<32, 16>(d + c)), (as_fixed<8, 4>(d) + as_fixed<8, 4>(c)), "%f + %f", c, d);
    ASSERT_EQ((as_fixed<32, 16>(d - c)), (as_fixed<8, 4>(d) - as_fixed<8, 4>(c)), "%f - %f", c, d);
    ASSERT_EQ((as_fixed<32, 16>(d * c)), (as_fixed<8, 4>(d) * as_fixed<8, 4>(c)), "%f * %f", c, d);
  }
}

int
main()
{
  fuzz();

  ASSERT_EQ((Fixed<POS, 1, 3>{ 8.0 } * Fixed<POS, 1, 4>{ 16.0 }).repr, 0b1);
  ASSERT_EQ((Fixed<POS, 1, 0>{ 1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr, 0b1);
  ASSERT_EQ((Fixed<NEG, 1, 0>{ 1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr, 0b1);
  ASSERT_EQ((Fixed<VAR, 1, 0>{ -1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr, -0b1);

  static_assert((as_fixed_v<16.0> - as_fixed_v<16.0>).repr == 0);
  static_assert((as_fixed_v<-16.0> - as_fixed_v<-16.0>).repr == 0);
  static_assert((as_fixed_v<-16.0> + as_fixed_v<16.0>).repr == 0);
  static_assert((as_fixed_v<16.0> + as_fixed_v<-16.0>).repr == 0);

  constexpr auto hi = Fixed<VAR, 2, 0>{ 1.0 };
  constexpr auto lo = Fixed<VAR, 2, 0>{ -1.0 };

  ASSERT_EQ(hi - lo, as_fixed_v<2.0>);
  ASSERT_EQ(hi + lo, as_fixed_v<0.0>);
  ASSERT_EQ(lo - hi, as_fixed_v<-2.0>);
  ASSERT_EQ(lo + hi, as_fixed_v<0.0>);

  ASSERT_EQ(hi - hi, as_fixed_v<0.0>);
  ASSERT_EQ(hi + hi, as_fixed_v<2.0>);
  ASSERT_EQ(lo - lo, as_fixed_v<0.0>);
  ASSERT_EQ(lo + lo, as_fixed_v<-2.0>);
}
