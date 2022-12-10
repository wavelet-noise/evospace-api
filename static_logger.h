#pragma once
#include "ThirdParty/cpplog.h"


#include <list>
#include <string>

#ifndef LOG_LEVEL
#define LOG(level) cpplog::LogMessage((level), *StaticLogger::Get().logger).getStream()
#endif

#ifndef LOG_NOTHING
#define LOG_NOTHING(level) true ? (void)0 : cpplog::helpers::VoidStreamClass() & LOG(level)
#endif

class StaticLogger {
  public:
    StaticLogger(std::string_view filename);

    std::unique_ptr<cpplog::BaseLogger> logger;

    static StaticLogger &Get();
    static cpplog::BaseLogger &get_logger();
    std::list<std::string> lines{};
    void Log(std::string_view sw);
    void Clear();

    StaticLogger(const StaticLogger &) = delete;
    StaticLogger &operator=(const StaticLogger &) = delete;
};