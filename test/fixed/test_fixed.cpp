#include <assert.hpp>
#include <macro.hpp>
#include <numeric.hpp>

#include <cmath>

template<int power>
void
test_one_bit_repr()
{
  const auto v = std::pow(2.0, static_cast<double>(power));
  const auto f = Fixed<POS, 1, power>{ v };
  ASSERT_EQ(f.repr, 1);
}

int
main()
{
  test_one_bit_repr<-512>();
  test_one_bit_repr<-32>();
  test_one_bit_repr<-16>();
  test_one_bit_repr<-8>();
  test_one_bit_repr<-4>();
  test_one_bit_repr<-3>();
  test_one_bit_repr<-2>();
  test_one_bit_repr<-1>();
  test_one_bit_repr<0>();
  test_one_bit_repr<1>();
  test_one_bit_repr<2>();
  test_one_bit_repr<3>();
  test_one_bit_repr<4>();
  test_one_bit_repr<8>();
  test_one_bit_repr<16>();
  test_one_bit_repr<32>();
  test_one_bit_repr<512>();

  constexpr auto test = Fixed<VAR, 1, 0>{ -1.0 };
  ASSERT_EQ(test.repr, -1);
  ASSERT_EQ(test.B, 1);
  ASSERT_EQ(test.P, 0);
  ASSERT_EQ(test.S, VAR);

  constexpr auto test2 = Fixed<VAR, 1, 0>{ -1.0f };
  ASSERT_EQ(test2.repr, -1);
  ASSERT_EQ(test2.B, 1);
  ASSERT_EQ(test2.P, 0);
  ASSERT_EQ(test2.S, VAR);
}
