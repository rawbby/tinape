#include <type/float.h>
#include <type/traits.h>

int
main()
{
  static_assert(GetFloatBits<Float>() == 23);
}
