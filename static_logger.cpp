#include "static_logger.h"

#include <memory>

StaticLogger &StaticLogger::Get() {
    static std::unique_ptr<StaticLogger> inst;

    if (inst == nullptr) {
        inst = std::make_unique<StaticLogger>();
    }

    return *inst;
}

void StaticLogger::Log(std::string_view sw) { lines.push_back(sw.data()); }

void StaticLogger::Log(const FString &sw) {
    lines.push_back(TCHAR_TO_UTF8(*sw));
}

void StaticLogger::Clear() { lines.clear(); }