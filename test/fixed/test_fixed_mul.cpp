#include <assert.hpp>
#include <numeric.hpp>

int
main()
{
  ASSERT_EQ((Fixed<POS, 1, 3>{ 8.0 } * Fixed<POS, 1, 4>{ 16.0 }).repr_, 0b1);
  ASSERT_EQ((Fixed<POS, 1, 0>{ 1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr_, 0b1);
  ASSERT_EQ((Fixed<NEG, 1, 0>{ 1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr_, 0b1);
  ASSERT_EQ((Fixed<VAR, 1, 0>{ -1.0 } * Fixed<POS, 1, 7>{ 128.0 }).repr_, -0b1);
}
