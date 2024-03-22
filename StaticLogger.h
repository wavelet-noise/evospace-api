// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/Vector.h"
#include "ThirdParty/cpplog.h"

#include <list>
#include <string>

#ifndef LOG_LEVEL
#define LOG(level) \
  cpplog::LogMessage((level), *StaticLogger::Get().logger).getStream()
#endif

#ifndef LOG_NOTHING
#define LOG_NOTHING(level) \
  true ? (void)0 : cpplog::helpers::VoidStreamClass() & LOG(level)
#endif

class StaticLogger {
  public:
  StaticLogger();

  std::unique_ptr<cpplog::BaseLogger> logger;
  std::unique_ptr<cpplog::BaseLogger> logger_internal;

  static StaticLogger &Get();
  static cpplog::BaseLogger &get_logger();

  StaticLogger(const StaticLogger &) = delete;
  StaticLogger &operator=(const StaticLogger &) = delete;
};

inline std::ostream &operator<<(std::ostream &os, const FString &str) {
  const std::string stdString(TCHAR_TO_UTF8(*str));
  os << stdString;
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const FVector3i &vec) {
  os << "{" << std::to_string(vec.X) << ", " << std::to_string(vec.Y) << ", " << std::to_string(vec.Z) << "}";
  return os;
}