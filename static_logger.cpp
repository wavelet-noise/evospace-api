// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#include "static_logger.h"

#include <memory>

StaticLogger::StaticLogger(std::string_view filename)
#ifdef WITH_EDITOR
    : logger(std::make_unique<cpplog::UeLogger>())
#else
    : logger(std::make_unique<cpplog::FileLogger>(filename.data()))
#endif
{
}

StaticLogger &StaticLogger::Get() {
    static std::unique_ptr<StaticLogger> inst;

    if (inst == nullptr) {
        inst = std::make_unique<StaticLogger>("log.txt");
    }

    return *inst;
}

cpplog::BaseLogger &StaticLogger::get_logger() { return *Get().logger; }