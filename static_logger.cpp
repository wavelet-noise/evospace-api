// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "static_logger.h"

#include <memory>

StaticLogger::StaticLogger(std::string_view filename)
{
    errors_log = new cpplog::StringLogger();
#ifdef WITH_EDITOR
    logger = std::make_unique<cpplog::MultiplexLogger>(
        new cpplog::UeLogger(), true,
        new cpplog::FilteringLogger(ERROR, errors_log, true), true);
#else
    logger = std::make_unique<cpplog::MultiplexLogger>(
        new cpplog::FileLogger(filename.data()), true,
        new cpplog::FilteringLogger(ERROR, errors_log, true), true);
#endif 
}

StaticLogger &StaticLogger::Get() {
    static std::unique_ptr<StaticLogger> inst;

    if (inst == nullptr) {
        inst = std::make_unique<StaticLogger>("log.txt");
    }

    return *inst;
}

cpplog::BaseLogger &StaticLogger::get_logger() { return *Get().logger; }