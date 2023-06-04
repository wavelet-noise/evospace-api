// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#include "static_logger.h"

#include <memory>

StaticLogger::StaticLogger() {
#if WITH_EDITOR
    logger = std::make_unique<cpplog::MultiplexLogger>(new cpplog::UeLogger(), true, new cpplog::FileLogger("log.txt"), true);
#else
    logger = std::make_unique<cpplog::FileLogger>("log.txt");
#endif
}

StaticLogger &StaticLogger::Get() {
    static std::unique_ptr<StaticLogger> inst =
        std::make_unique<StaticLogger>();
    return *inst;
}

cpplog::BaseLogger &StaticLogger::get_logger() { return *Get().logger; }