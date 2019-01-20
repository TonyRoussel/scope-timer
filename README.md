##  What is this ?

A header only helper to measure execution time of a C++ scope

##  How to use it ?

1. You instantiate a `ScopeTimer` object at the beginning of the scope you want to measure
2. You call the scope as much as you want
3. You call `ScopeTimerStaticCore::dumpTimingToFile("/path/to/a/dump.csv")` to write time measures to a file

##  Example ?

Let's say you have a function called `aFunctionThatTakeTime`. You want to measure it's execution time:

```c++
int aFunctionThatTakeTime() {
  int x;

  /*
   * Do stuff with 'x'
   */
  return (x);
};
```

Change it to:

```c++
#include "/path/to/scope_timer.hpp"

int aFunctionThatTakeTime() {
  ScopeTimer  scopeTimer("aNameForThatTimer")
  int x;

  /*
   * Do stuff with 'x'
   */
  return (x);
};
```

and call the dump method of `ScopeTimerStaticCore` after you made calls to `aFunctionThatTakeTime`

```c++
#include "/path/to/scope_timer.hpp"

int aFunctionThatTakeTime();

int main() {
  for (int i = 0; i < 5; ++i)
    aFunctionThatTakeTime()
  ScopeTimerStaticCore::dumpTimingToFile("dump_file.csv");
  return (0);
}
```

After executing this program, you'll have a file named `dump_file.csv` with the following content

```
aNameForThatTimer,100215
aNameForThatTimer,100218
aNameForThatTimer,100213
aNameForThatTimer,100220
aNameForThatTimer,100202
```

where the first column is the name you gave to the scope measured, a second column with its timing in microseconds


Have a good day !
