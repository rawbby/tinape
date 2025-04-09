#include <assert.hpp>
#include <numeric.hpp>

int
main()
{
  const auto sqrt2ub_hardcoded = as_fixed_v<0x1.6a0ap0>;
  ASSERT_EQ(sqrt2ub_hardcoded.S, POS);
  ASSERT_EQ(sqrt2ub_hardcoded.B, 16);
  ASSERT_EQ(sqrt2ub_hardcoded.repr, 0b1011010100000101);
  ASSERT_EQ(sqrt2ub_hardcoded.P, -15);

  const auto sqrt2ub_generic = upper_bound<16>(as_fixed_v<std::numbers::sqrt2_v<double>>);
  ASSERT_EQ(sqrt2ub_generic.S, POS);
  ASSERT_EQ(sqrt2ub_generic.B, 16);
  ASSERT_EQ(sqrt2ub_generic.repr, 0b1011010100000101);
  ASSERT_EQ(sqrt2ub_generic.P, -15);

  const auto sqrt2ub_generic2 = upper_bound_v<16, std::numbers::sqrt2_v<double>>;
  ASSERT_EQ(sqrt2ub_generic2.S, POS);
  ASSERT_EQ(sqrt2ub_generic2.B, 16);
  ASSERT_EQ(sqrt2ub_generic2.repr, 0b1011010100000101);
  ASSERT_EQ(sqrt2ub_generic2.P, -15);

  const auto sqrt2ub_round = round_down<5>(as_fixed_v<0x1.6a0ap0>);
  ASSERT_EQ(sqrt2ub_round.S, POS);
  ASSERT_EQ(sqrt2ub_round.B, 5);
  ASSERT_EQ(sqrt2ub_round.repr, 0b10110);
  ASSERT_EQ(sqrt2ub_round.P, -4);
}
