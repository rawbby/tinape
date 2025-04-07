#include <numeric.hpp>
#include <assert.hpp>
#include <macro.hpp>
#include <bitset>

int
main()
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
