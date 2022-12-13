// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Evospace/Shared/ThirdParty/result.h"

/**
 * @brief Abstract error type for Result<T, Error>
 */
struct AbstractError {
    virtual ~AbstractError() = default;
    virtual auto to_string() noexcept -> std::string = 0;
    // void log_default() noexcept { StaticLogger::Get().Log(to_string()); }
};