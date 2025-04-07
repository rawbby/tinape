#include <numeric.hpp>
#include <assert.hpp>
#include <bitset>

int
main()
{
  constexpr auto m6_0 = std::bitset<8>(mask<6, 0>());
  constexpr auto m6_4 = std::bitset<8>(mask<6, 4>());
  constexpr auto m64 = std::bitset<64>(mask<64>());

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
