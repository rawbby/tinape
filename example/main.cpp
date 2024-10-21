#include "context.h"

int
main(int, char**)
{
  auto context = Context();
  Init(&context);
  Loop(&context);
  Quit(&context);
}
