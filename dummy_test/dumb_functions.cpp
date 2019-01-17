#include <thread>
#include <chrono>
#include "../include/scope_timer.hpp"

void  functionA() {
  ScopeTimer  scopeTimer("functionA");
  std::this_thread::sleep_for (std::chrono::milliseconds(500));
  return ;
};

void  functionB() {
  ScopeTimer  scopeTimer("functionB");
  std::this_thread::sleep_for (std::chrono::seconds(1));
  return ;
};
