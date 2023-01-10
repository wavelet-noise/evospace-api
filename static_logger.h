// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
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
    StaticLogger(std::string_view filename);

    std::unique_ptr<cpplog::BaseLogger> logger;
    
    cpplog::StringLogger * errors_log;

    static StaticLogger &Get();
    static cpplog::BaseLogger &get_logger();

    StaticLogger(const StaticLogger &) = delete;
    StaticLogger &operator=(const StaticLogger &) = delete;
};