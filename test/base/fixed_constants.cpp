#include <base/fixed.h>
#include <bit>
#include <cstdint>

#include <numbers>

constexpr static void
CheckSizeOfSum(auto value)
{
  static_assert(sizeof(value + value + value + value + value + value + value) == 1);
  static_assert(sizeof(value + value + value + value + value + value + value + value) == 2);
}

int
main()
{
  using namespace base;

  static_assert(c0 == 0.);
  static_assert(c0 < c_000244141);
  static_assert(c0 < c_000488281);
  static_assert(c0 < c_000976563);
  static_assert(c0 < c_00195313);
  static_assert(c0 < c_00390625);
  static_assert(c0 < c_0078125);
  static_assert(c0 < c_015625);
  static_assert(c0 < c_03125);
  static_assert(c0 < c_0625);
  static_assert(c0 < c_125);
  static_assert(c0 < c_25);
  static_assert(c0 < c_5);
  static_assert(c0 < c1);
  static_assert(c0 < c2);
  static_assert(c0 < c4);
  static_assert(c0 < c8);
  static_assert(c0 < c16);
  static_assert(c0 < c32);
  static_assert(c0 < c64);
  static_assert(c0 < c128);
  static_assert(c0 < c256);
  static_assert(c0 < c512);
  static_assert(c0 < c1024);
  static_assert(c0 < c2048);
  static_assert(c0 < c4096);

  static_assert(c_000244141 == 1. / 4096.);
  static_assert(c_000488281 == 1. / 2048.);
  static_assert(c_000976563 == 1. / 1024.);
  static_assert(c_00195313 == 1. / 512.);
  static_assert(c_00390625 == 1. / 256.);
  static_assert(c_0078125 == 1. / 128.);
  static_assert(c_015625 == 1. / 64.);
  static_assert(c_03125 == 1. / 32.);
  static_assert(c_0625 == 1. / 16.);
  static_assert(c_125 == 1. / 8.);
  static_assert(c_25 == 1. / 4.);
  static_assert(c_5 == 1. / 2.);

  static_assert(c1 == 1.);

  static_assert(c2 == 2.);
  static_assert(c4 == 4.);
  static_assert(c8 == 8.);
  static_assert(c16 == 16.);
  static_assert(c32 == 32.);
  static_assert(c64 == 64.);
  static_assert(c128 == 128.);
  static_assert(c256 == 256.);
  static_assert(c512 == 512.);
  static_assert(c1024 == 1024.);
  static_assert(c2048 == 2048.);
  static_assert(c4096 == 4096.);

  CheckSizeOfSum(c_000244141);
  CheckSizeOfSum(c_000488281);
  CheckSizeOfSum(c_000976563);
  CheckSizeOfSum(c_00195313);
  CheckSizeOfSum(c_00390625);
  CheckSizeOfSum(c_0078125);
  CheckSizeOfSum(c_015625);
  CheckSizeOfSum(c_03125);
  CheckSizeOfSum(c_0625);
  CheckSizeOfSum(c_125);
  CheckSizeOfSum(c_25);
  CheckSizeOfSum(c_5);

  CheckSizeOfSum(c1);

  CheckSizeOfSum(c2);
  CheckSizeOfSum(c4);
  CheckSizeOfSum(c8);
  CheckSizeOfSum(c16);
  CheckSizeOfSum(c32);
  CheckSizeOfSum(c64);
  CheckSizeOfSum(c128);
  CheckSizeOfSum(c256);
  CheckSizeOfSum(c512);
  CheckSizeOfSum(c1024);
  CheckSizeOfSum(c2048);
  CheckSizeOfSum(c4096);

  static_assert(c_000244141 < c_000488281);
  static_assert(c_000488281 < c_000976563);
  static_assert(c_000976563 < c_00195313);
  static_assert(c_00195313 < c_00390625);
  static_assert(c_00390625 < c_0078125);
  static_assert(c_0078125 < c_015625);
  static_assert(c_015625 < c_03125);
  static_assert(c_03125 < c_0625);
  static_assert(c_0625 < c_125);
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
  static_assert(c256 < c512);
  static_assert(c512 < c1024);
  static_assert(c1024 < c2048);
  static_assert(c2048 < c4096);

  static_assert(std::bit_cast<std::uint8_t>(c_000244141) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_000488281) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_000976563) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_00195313) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_00390625) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_0078125) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_015625) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_03125) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_0625) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_125) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_25) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c_5) == std::uint8_t{ 1 });

  static_assert(std::bit_cast<std::uint8_t>(c1) == std::uint8_t{ 1 });

  static_assert(std::bit_cast<std::uint8_t>(c2) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c4) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c8) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c16) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c32) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c64) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c128) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c256) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c512) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c1024) == std::uint8_t{ 1 });
  static_assert(std::bit_cast<std::uint8_t>(c2048) == std::uint8_t{ 1 });

  static_assert(sqrt2ub < c2);
  static_assert(c1 < sqrt2ub);
  static_assert(sqrt2ub == std::numbers::sqrt2);
  static_assert(sizeof(sqrt2ub) == 2);
}
