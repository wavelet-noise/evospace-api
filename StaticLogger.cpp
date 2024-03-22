// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.
#include "StaticLogger.h"

#include <memory>

StaticLogger::StaticLogger() {
#if WITH_EDITOR
  logger_internal = std::make_unique<cpplog::TeeLogger>(new cpplog::UeLogger(), true, new cpplog::SessionRotatingLogger(TCHAR_TO_UTF8(*FPaths::ProjectLogDir())), true);
#else
  logger_internal = std::make_unique<cpplog::SessionRotatingLogger>(TCHAR_TO_UTF8(*FPaths::ProjectLogDir()));
#endif

#ifdef EVOSPACE_LOG_INFO_PLUS
  logger = std::make_unique<cpplog::templated::TFilteringLogger<INFO_LL>>(logger_internal.get());
#else
  logger = std::make_unique<cpplog::templated::TFilteringLogger<TRACE_LL>>(logger_internal.get());
#endif
}

StaticLogger &StaticLogger::Get() {
  static std::unique_ptr<StaticLogger> inst =
    std::make_unique<StaticLogger>();
  return *inst;
}

cpplog::BaseLogger &StaticLogger::get_logger() {
  return *Get().logger;
}