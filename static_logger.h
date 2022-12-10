#pragma once
#include <list>
#include <string>

class StaticLogger {
  public:
    StaticLogger() {}

    static StaticLogger &Get();
    std::list<std::string> lines{};
    void Log(std::string_view sw);
    void Clear();

    StaticLogger(const StaticLogger &) = delete;
    StaticLogger &operator=(const StaticLogger &) = delete;
};