#include <assert.hpp>
#include <numeric.hpp>

void
test_simple_literal()
{
  constexpr auto pos = as_fixed_v<0.25>;
  ASSERT_EQ(pos.sign_, POS);
  ASSERT_EQ(pos.bits_, 1);
  ASSERT_EQ(pos.repr_, 1);
  ASSERT_EQ(pos.power_, -2);

  constexpr auto neg = as_fixed_v<-0.25>;
  ASSERT_EQ(neg.sign_, NEG);
  ASSERT_EQ(neg.bits_, 1);
  ASSERT_EQ(neg.repr_, 1);
  ASSERT_EQ(neg.power_, -2);
}

void
test_double_limit_literal()
{
  constexpr auto pos_max = as_fixed_v<std::numeric_limits<double>::max()>;
  ASSERT_EQ(pos_max.sign_, POS);
  ASSERT_EQ(pos_max.bits_, 53);
  ASSERT_EQ(pos_max.repr_, (static_cast<std::uint64_t>(1) << pos_max.bits_) - 1);
  ASSERT_EQ(pos_max.power_, 971);

  constexpr auto neg_max = as_fixed_v<-std::numeric_limits<double>::max()>;
  ASSERT_EQ(neg_max.sign_, NEG);
  ASSERT_EQ(neg_max.bits_, 53);
  ASSERT_EQ(neg_max.repr_, (static_cast<std::uint64_t>(1) << neg_max.bits_) - 1);
  ASSERT_EQ(neg_max.power_, 971);

  constexpr auto pos_min = as_fixed_v<std::numeric_limits<double>::min()>;
  ASSERT_EQ(pos_min.sign_, POS);
  ASSERT_EQ(pos_min.bits_, 1);
  ASSERT_EQ(pos_min.repr_, 1);
  ASSERT_EQ(pos_min.power_, -1022);

  constexpr auto neg_min = as_fixed_v<-std::numeric_limits<double>::min()>;
  ASSERT_EQ(neg_min.sign_, NEG);
  ASSERT_EQ(neg_min.bits_, 1);
  ASSERT_EQ(neg_min.repr_, 1);
  ASSERT_EQ(neg_min.power_, -1022);
}

int
main()
{
  test_simple_literal();
  test_double_limit_literal();
}
