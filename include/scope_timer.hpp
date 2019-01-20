#ifndef SCOPE_TIMER
#define SCOPE_TIMER
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <fstream>

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
  using ScopesTiming = std::map<ScopeTimer::ScopeSignature, TimingVector>;

  static ScopesTiming&  getScopesTimingStaticInstance() {
    static ScopesTiming scopesTimingContainer;

    return (scopesTimingContainer);
  };

};

/*******************************************************Implementations*******************************************************/

inline ScopeTimer::ScopeTimer(const ScopeSignature& scopeName) : scopeName(scopeName), start(std::chrono::high_resolution_clock::now()) {};

inline ScopeTimer::~ScopeTimer() {
  const Duration  scopeTimerLifetimeDuration = this->getDurationFromStart();

  ScopeTimerStaticCore::addTimingToNamedScope(this->scopeName, scopeTimerLifetimeDuration);
  return ;
};

inline ScopeTimer::Duration  ScopeTimer::getDurationFromStart() const {
  using std::chrono::duration_cast;

  const std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

  return (duration_cast<DurationType>(now - this->start).count());
};


inline void  ScopeTimerStaticCore::addTimingToNamedScope(const ScopeTimer::ScopeSignature& scopeName, const ScopeTimer::Duration& duration) {
  ScopesTiming& scopesTimingContainer = ScopeTimerStaticCore::getScopesTimingStaticInstance();

  scopesTimingContainer[scopeName].push_back(duration);
  return ;
};

inline void  ScopeTimerStaticCore::dumpTimingToFile(const std::string& path) {
  const ScopesTiming& scopesTimingContainer = ScopeTimerStaticCore::getScopesTimingStaticInstance();
  std::ofstream       dumpfile;

  dumpfile.open(path, std::ios::out | std::ios::trunc);
  for (ScopesTiming::const_iterator it_scopes = scopesTimingContainer.begin(); it_scopes != scopesTimingContainer.end(); ++it_scopes) {
    const ScopeTimer::ScopeSignature& currentScope = it_scopes->first;
    const TimingVector&               timings = it_scopes->second;

    for (TimingVector::const_iterator it_timings = timings.begin(); it_timings != timings.end(); ++it_timings)
      dumpfile << currentScope << "," << *it_timings << std::endl;
  }
  dumpfile.close();
  return ;
};

inline void  ScopeTimerStaticCore::clearAllTiming() {
  ScopesTiming& scopesTimingContainer = ScopeTimerStaticCore::getScopesTimingStaticInstance();

  scopesTimingContainer.clear();
  return ;
};

inline void  ScopeTimerStaticCore::clearTimingForNamedScope(const ScopeTimer::ScopeSignature& scopeName) {
  ScopesTiming&           scopesTimingContainer = ScopeTimerStaticCore::getScopesTimingStaticInstance();
  ScopesTiming::iterator  it_scopes = scopesTimingContainer.find(scopeName);

  if (it_scopes != scopesTimingContainer.end())
    it_scopes->second.clear();
  return ;
};

#endif /* SCOPE_TIMER */
