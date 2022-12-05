#pragma once
#include "static_logger.h"

struct AbstractError {
    virtual ~AbstractError() = default;
    virtual auto to_string() noexcept -> std::string = 0;
    void log_default() noexcept { StaticLogger::Get().Log(to_string()); }
};