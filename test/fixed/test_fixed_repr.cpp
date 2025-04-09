#include <numeric.hpp>
#include <assert.hpp>

int
main()
{
  ASSERT_EQ((Fixed<POS, 4, -2>{ 0.25 }.repr), 0b00'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 3.25 }.repr), 0b11'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 1.25 }.repr), 0b01'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 2.50 }.repr), 0b10'10);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 0.25 }.repr), 0b00);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 3.25 }.repr), 0b11);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 1.25 }.repr), 0b01);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 2.50 }.repr), 0b10);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 0.25f }.repr), 0b00'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 3.25f }.repr), 0b11'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 1.25f }.repr), 0b01'01);
  ASSERT_EQ((Fixed<POS, 4, -2>{ 2.50f }.repr), 0b10'10);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 0.25f }.repr), 0b00);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 3.25f }.repr), 0b11);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 1.25f }.repr), 0b01);
  ASSERT_EQ((Fixed<POS, 2, 0>{ 2.50f }.repr), 0b10);
}
