#include "Server.hpp"

#include <unistd.h>

int main()
{
  auto tmp = Server("5445");
  tmp.start();
  sleep(444);
  return 0;
}
