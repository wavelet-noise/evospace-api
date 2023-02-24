// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "ThirdParty/cpplog.h"

#include <list>
#include <string>

#ifndef LOG_LEVEL
#define LOG(level)                                                             \
    cpplog::LogMessage((level), *StaticLogger::Get().logger).getStream()
#endif

#ifndef LOG_NOTHING
#define LOG_NOTHING(level)                                                     \
    true ? (void)0 : cpplog::helpers::VoidStreamClass() & LOG(level)
#endif

class StaticLogger {
  public:
    StaticLogger();

    std::unique_ptr<cpplog::BaseLogger> logger;

    static StaticLogger &Get();
    static cpplog::BaseLogger &get_logger();

    StaticLogger(const StaticLogger &) = delete;
    StaticLogger &operator=(const StaticLogger &) = delete;
};