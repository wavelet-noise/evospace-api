#pragma once
#include "abstract_error.h"

#include <string>

struct LuaStateBufferLoadError : AbstractError {
    std::string error;
    std::string in_line;

    LuaStateBufferLoadError(std::string err, std::string inl)
        : error(std::move(err)), in_line(std::move(inl)) {}
    virtual auto to_string() noexcept -> std::string override {
        return "Buffer load error: " + error + "\n" + "In line: " + in_line;
    }
};

struct LuaStateCodeDumpError : AbstractError {
    std::string error;

    LuaStateCodeDumpError(std::string err) : error(std::move(err)) {}
    virtual auto to_string() noexcept -> std::string override {
        return "Code dump error: " + error;
    }
};