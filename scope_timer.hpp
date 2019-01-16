#ifndef SCOPE_TIMER
#define SCOPE_TIMER
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>

class ScopeTimer {
public:
  using ScopeSignature = std::string;
  using DurationType = std::chrono::microseconds;
  using Duration = decltype(std::chrono::duration_cast<DurationType>(std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now()).count());

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
  using ScopesTiming = std::unordered_map<ScopeTimer::ScopeSignature, TimingVector>;

  static ScopesTiming&  getScopesTimingStaticInstance();
};

/*******************************************************Implementations*******************************************************/

ScopeTimer::ScopeTimer(const ScopeSignature& scopeName) : scopeName(scopeName), start(std::chrono::high_resolution_clock::now()) {};

ScopeTimer::~ScopeTimer() {
  const Duration  scopeTimerLifetimeDuration = this->getDurationFromStart();

  ScopeTimerStaticCore::addTimingToNamedScope(this->scopeName, scopeTimerLifetimeDuration);
  return ;
};

ScopeTimer::Duration  ScopeTimer::getDurationFromStart() const {
  using std::chrono::duration_cast;

  const std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

  return (duration_cast<DurationType>(now - this->start).count());
};

#endif /* SCOPE_TIMER */
