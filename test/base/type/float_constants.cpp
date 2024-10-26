#include <type/float.h>

int
main()
{
  static_assert(c_125 == 0.125f);
  static_assert(c_25 == 0.25f);
  static_assert(c_5 == 0.5f);
  static_assert(c0 == 0.0f);
  static_assert(c1 == 1.0f);
  static_assert(c2 == 2.0f);
  static_assert(c4 == 4.0f);
  static_assert(c8 == 8.0f);
  static_assert(c16 == 16.0f);
  static_assert(c32 == 32.0f);
  static_assert(c64 == 64.0f);
  static_assert(c128 == 128.0f);
  static_assert(c256 == 256.0f);

  static_assert(c0 < c_125);
  static_assert(c_125 < c_25);
  static_assert(c_25 < c_5);
  static_assert(c_5 < c1);
  static_assert(c1 < c2);
  static_assert(c2 < c4);
  static_assert(c4 < c8);
  static_assert(c8 < c16);
  static_assert(c16 < c32);
  static_assert(c32 < c64);
  static_assert(c64 < c128);
  static_assert(c128 < c256);
}
