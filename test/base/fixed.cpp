#include <base/fixed.h>

int
main()
{
  using namespace base;

  static_assert(std::is_same_v<decltype(internal::ConditionalType<1, int, unsigned>()), int>);
  static_assert(std::is_same_v<decltype(internal::ConditionalType<0, int, unsigned>()), unsigned>);

  static_assert(std::is_same_v<internal::ConditionalTypeV<1, int, unsigned>, int>);
  static_assert(std::is_same_v<internal::ConditionalTypeV<0, int, unsigned>, unsigned>);

  static_assert(sizeof(Fixed<0, 16, 16>{}) == 4);
  static_assert(sizeof(Fixed<1, 4, 12>{}) == 4);
  static_assert(sizeof(Fixed<0, 4, 12>{}) == 2);
}
