#include <numeric.hpp>
#include <assert.hpp>

int
main()
{
  ASSERT_EQ((Fixed<POS, 4, -2>{ Fixed<POS, 2, 0>{ 2.50f } }.repr_), 0b1000);
  ASSERT_EQ((Fixed<POS, 2, 0>{ Fixed<POS, 4, -2>{ 2.50f } }.repr_), 0b10);
}
