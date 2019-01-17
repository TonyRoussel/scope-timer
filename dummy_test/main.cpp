#include "../include/scope_timer.hpp"

void  functionA();
void  functionB();

int main() {
  for (size_t i = 0; i < 3; ++i) {
    functionA();
    functionB();
  }
  ScopeTimerStaticCore::dumpTimingToFile("/tmp/scope-timer_dump-dummy-test.csv");
  return (0);
};
