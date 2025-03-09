#include <assert.hpp>
#include <bitset>
#include <macro.hpp>
#include <numeric.hpp>

using namespace numeric;
using enum Sign;

void
test_hard_coded_repr()
{
  ASSERT_EQ((Fixed<POS, 4, -2>{ 0.25 }.repr_), 0b00'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 3.25 }.repr_), 0b11'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 1.25 }.repr_), 0b01'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 2.50 }.repr_), 0b10'10);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 0.25 }.repr_), 0b00);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 3.25 }.repr_), 0b11);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 1.25 }.repr_), 0b01);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 2.50 }.repr_), 0b10);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 0.25f }.repr_), 0b00'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 3.25f }.repr_), 0b11'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 1.25f }.repr_), 0b01'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 2.50f }.repr_), 0b10'10);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 0.25f }.repr_), 0b00);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 3.25f }.repr_), 0b11);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 1.25f }.repr_), 0b01);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 2.50f }.repr_), 0b10);
}

void
test_sizeof()
{
  ASSERT_EQ(sizeof(Fixed<POS, 64, 0>), 8);
  ASSERT_EQ(sizeof(Fixed<POS, 33, 0>), 8);
  ASSERT_EQ(sizeof(Fixed<POS, 32, 0>), 4);
  ASSERT_EQ(sizeof(Fixed<POS, 17, 0>), 4);
  ASSERT_EQ(sizeof(Fixed<POS, 16, 0>), 2);
  ASSERT_EQ(sizeof(Fixed<POS, 9, 0>), 2);
  ASSERT_EQ(sizeof(Fixed<POS, 8, 0>), 1);

  ASSERT_EQ(sizeof(Fixed<NEG, 64, 0>), 8);
  ASSERT_EQ(sizeof(Fixed<NEG, 33, 0>), 8);
  ASSERT_EQ(sizeof(Fixed<NEG, 32, 0>), 4);
  ASSERT_EQ(sizeof(Fixed<NEG, 17, 0>), 4);
  ASSERT_EQ(sizeof(Fixed<NEG, 16, 0>), 2);
  ASSERT_EQ(sizeof(Fixed<NEG, 9, 0>), 2);
  ASSERT_EQ(sizeof(Fixed<NEG, 8, 0>), 1);

  ASSERT_EQ(sizeof(Fixed<VAR, 63, 0>), 8);
  ASSERT_EQ(sizeof(Fixed<VAR, 32, 0>), 8);
  ASSERT_EQ(sizeof(Fixed<VAR, 31, 0>), 4);
  ASSERT_EQ(sizeof(Fixed<VAR, 16, 0>), 4);
  ASSERT_EQ(sizeof(Fixed<VAR, 15, 0>), 2);
  ASSERT_EQ(sizeof(Fixed<VAR, 8, 0>), 2);
  ASSERT_EQ(sizeof(Fixed<VAR, 7, 0>), 1);
}

void
test_literal()
{
  constexpr auto l1 = as_fixed_v<0.25>;
  ASSERT_EQ(l1.sign_, POS);
  ASSERT_EQ(l1.bits_, 1);
  ASSERT_EQ(l1.repr_, 0b1);
  ASSERT_EQ(l1.power_, -2);
  constexpr auto l2 = as_fixed_v<-0.25>;
  ASSERT_EQ(l2.sign_, NEG);
  ASSERT_EQ(l2.bits_, 1);
  ASSERT_EQ(l2.repr_, 0b1);
  ASSERT_EQ(l2.power_, -2);
  constexpr auto l3 = as_fixed_v<std::numeric_limits<double>::max()>;
  ASSERT_EQ(l3.sign_, POS);
  ASSERT_EQ(l3.bits_, 53);
  ASSERT_EQ(l3.repr_, (static_cast<std::uint64_t>(1) << l3.bits_) - 1);
  ASSERT_EQ(l3.power_, 971);
  constexpr auto l4 = as_fixed_v<-std::numeric_limits<double>::max()>;
  ASSERT_EQ(l4.sign_, NEG);
  ASSERT_EQ(l4.bits_, 53);
  ASSERT_EQ(l4.repr_, (static_cast<std::uint64_t>(1) << l4.bits_) - 1);
  ASSERT_EQ(l4.power_, 971);
  constexpr auto l5 = as_fixed_v<std::numeric_limits<double>::min()>;
  ASSERT_EQ(l5.sign_, POS);
  ASSERT_EQ(l5.bits_, 1);
  ASSERT_EQ(l5.repr_, 1);
  ASSERT_EQ(l5.power_, -1022);
  constexpr auto l6 = as_fixed_v<-std::numeric_limits<double>::min()>;
  ASSERT_EQ(l6.sign_, NEG);
  ASSERT_EQ(l6.bits_, 1);
  ASSERT_EQ(l6.repr_, 1);
  ASSERT_EQ(l6.power_, -1022);
}

void
test_mask()
{
  constexpr auto m6_0 = std::bitset<8>(numeric::mask<6, 0>());
  constexpr auto m6_4 = std::bitset<8>(numeric::mask<6, 4>());
  constexpr auto m64 = std::bitset<64>(numeric::mask<64>());

  ASSERT_EQ(m6_0[0], 1);
  ASSERT_EQ(m6_0[1], 1);
  ASSERT_EQ(m6_0[2], 1);
  ASSERT_EQ(m6_0[3], 1);
  ASSERT_EQ(m6_0[4], 1);
  ASSERT_EQ(m6_0[5], 1);
  ASSERT_EQ(m6_0[6], 0);
  ASSERT_EQ(m6_0[7], 0);

  ASSERT_EQ(m6_4[0], 0);
  ASSERT_EQ(m6_4[1], 0);
  ASSERT_EQ(m6_4[2], 0);
  ASSERT_EQ(m6_4[3], 0);
  ASSERT_EQ(m6_4[4], 1);
  ASSERT_EQ(m6_4[5], 1);
  ASSERT_EQ(m6_4[6], 0);
  ASSERT_EQ(m6_4[7], 0);

  for (u8 i = 0; i < 63; ++i)
    ASSERT_EQ(m64[i], 0);

  ASSERT_EQ(m64[63], 1);
}

int
main()
{
  const auto x = lshift(-0b100, -2);
  ASSERT_EQ((Fixed<POS, 1, 0>{ 1.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 1>{ 2.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 2>{ 4.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 3>{ 8.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 4>{ 16.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 5>{ 32.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 6>{ 64.0 }.repr_), 0b1);
  ASSERT_EQ((Fixed<POS, 1, 7>{ 128.0 }.repr_), 0b1);

  constexpr auto test = Fixed<VAR, 1, 0>{ -1.0 };
  ASSERT_EQ(test.repr_, -1);
  ASSERT_EQ(test.bits_, 1);
  ASSERT_EQ(test.power_, 0);
  ASSERT_EQ(test.sign_, VAR);

  constexpr auto test2 = Fixed<VAR, 1, 0>{ -1.0f };
  ASSERT_EQ(test2.repr_, -1);
  ASSERT_EQ(test2.bits_, 1);
  ASSERT_EQ(test2.power_, 0);
  ASSERT_EQ(test2.sign_, VAR);

  ASSERT_EQ((Fixed<POS, 1, 3>{ 8.0 } * Fixed<POS, 1, 4>{ 16.0 }).repr_, 0b1);
  ASSERT_EQ((Fixed<POS, 1, 0>{ 1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr_, 0b1);
  ASSERT_EQ((Fixed<NEG, 1, 0>{ 1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr_, 0b1);
  ASSERT_EQ((Fixed<VAR, 1, 0>{ -1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr_, -0b1);

  test_literal();
  test_hard_coded_repr();
  test_sizeof();
  test_mask();

  ASSERT_EQ((Fixed<POS, 4, -2>{ Fixed<POS, 2, 0>{ 2.50f } }.repr_), 0b1000);
  ASSERT_EQ((Fixed<POS, 2, 0>{ Fixed<POS, 4, -2>{ 2.50f } }.repr_), 0b10);

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
