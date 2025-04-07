#include <assert.hpp>
#include <numeric.hpp>

int
main()
{
  const auto sqrt2ub_hardcoded = as_fixed_v<0x1.6a0ap0>;
  ASSERT_EQ(sqrt2ub_hardcoded.sign_, POS);
  ASSERT_EQ(sqrt2ub_hardcoded.bits_, 16);
  ASSERT_EQ(sqrt2ub_hardcoded.repr_, 0b1011010100000101);
  ASSERT_EQ(sqrt2ub_hardcoded.power_, -15);

  const auto sqrt2ub_generic = upper_bound<16>(as_fixed_v<std::numbers::sqrt2_v<double>>);
  ASSERT_EQ(sqrt2ub_generic.sign_, POS);
  ASSERT_EQ(sqrt2ub_generic.bits_, 16);
  ASSERT_EQ(sqrt2ub_generic.repr_, 0b1011010100000101);
  ASSERT_EQ(sqrt2ub_generic.power_, -15);

  const auto sqrt2ub_generic2 = upper_bound_v<16, std::numbers::sqrt2_v<double>>;
  ASSERT_EQ(sqrt2ub_generic2.sign_, POS);
  ASSERT_EQ(sqrt2ub_generic2.bits_, 16);
  ASSERT_EQ(sqrt2ub_generic2.repr_, 0b1011010100000101);
  ASSERT_EQ(sqrt2ub_generic2.power_, -15);

  const auto sqrt2ub_round = round_down<5>(as_fixed_v<0x1.6a0ap0>);
  ASSERT_EQ(sqrt2ub_round.sign_, POS);
  ASSERT_EQ(sqrt2ub_round.bits_, 5);
  ASSERT_EQ(sqrt2ub_round.repr_, 0b10110);
  ASSERT_EQ(sqrt2ub_round.power_, -4);
}
