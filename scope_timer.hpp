#ifndef SCOPE_TIMER
#define SCOPE_TIMER
#include <chrono>
#include <string>
#include <vector>

class ScopeTimer {
public:
  using ScopeSignature = std::string;
  using Duration = decltype(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now()).count());

  ScopeTimer(const ScopeSignature& scopeName);
  ~ScopeTimer();

  Duration  getDurationFromStart() const;
private:
  ScopeTimer();

  const ScopeSignature                                  scopeName;
  const std::chrono::high_resolution_clock::time_point  start;
};

class ScopeTimerStaticCore {
public:

  static void addTimingToNamedScope(const ScopeTimer::ScopeSignature& scopeName, const ScopeTimer::Duration& duration);
  static void dumpTimingToFile(const std::string& path);
  static void clearAllTiming();
  static void clearTimingForNamedScope(const ScopeTimer::ScopeSignature& scopeName);

private:
  using TimingVector = std::vector<ScopeTimer::Duration>;
  using ScopesTiming = std::map<ScopeTimer::ScopeSignature, TimingVector>;

  static ScopesTiming&  getScopesTimingStaticInstance();
};

#endif /* SCOPE_TIMER */
