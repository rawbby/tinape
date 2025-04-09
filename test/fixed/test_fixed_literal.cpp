#include <assert.hpp>
#include <numeric.hpp>

void
test_simple_literal()
{
  constexpr auto pos = as_fixed_v<0.25>;
  ASSERT_EQ(pos.S, POS);
  ASSERT_EQ(pos.B, 1);
  ASSERT_EQ(pos.repr, 1);
  ASSERT_EQ(pos.P, -2);

  constexpr auto neg = as_fixed_v<-0.25>;
  ASSERT_EQ(neg.S, NEG);
  ASSERT_EQ(neg.B, 1);
  ASSERT_EQ(neg.repr, 1);
  ASSERT_EQ(neg.P, -2);
}

void
test_double_limit_literal()
{
  constexpr auto pos_max = as_fixed_v<std::numeric_limits<double>::max()>;
  ASSERT_EQ(pos_max.S, POS);
  ASSERT_EQ(pos_max.B, 53);
  ASSERT_EQ(pos_max.repr, (static_cast<std::uint64_t>(1) << pos_max.B) - 1);
  ASSERT_EQ(pos_max.P, 971);

  constexpr auto neg_max = as_fixed_v<-std::numeric_limits<double>::max()>;
  ASSERT_EQ(neg_max.S, NEG);
  ASSERT_EQ(neg_max.B, 53);
  ASSERT_EQ(neg_max.repr, (static_cast<std::uint64_t>(1) << neg_max.B) - 1);
  ASSERT_EQ(neg_max.P, 971);

  constexpr auto pos_min = as_fixed_v<std::numeric_limits<double>::min()>;
  ASSERT_EQ(pos_min.S, POS);
  ASSERT_EQ(pos_min.B, 1);
  ASSERT_EQ(pos_min.repr, 1);
  ASSERT_EQ(pos_min.P, -1022);

  constexpr auto neg_min = as_fixed_v<-std::numeric_limits<double>::min()>;
  ASSERT_EQ(neg_min.S, NEG);
  ASSERT_EQ(neg_min.B, 1);
  ASSERT_EQ(neg_min.repr, 1);
  ASSERT_EQ(neg_min.P, -1022);
}

int
main()
{
  test_simple_literal();
  test_double_limit_literal();
}
