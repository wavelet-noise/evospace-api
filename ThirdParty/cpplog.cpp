#include "cpplog.h"

namespace cpplog {

bool UeStringArrayLogger::sendLogMessage(LogData *logData) {
    OstreamLogger::sendLogMessage(logData);
    std::string out_string = m_stream.str().c_str();
    log.Add(UTF8_TO_TCHAR(out_string.data()));
    return true;
}

bool UeLogger::sendLogMessage(LogData *logData) {
#ifndef UE_BUILD_SHIPPING
    OstreamLogger::sendLogMessage(logData);
    std::string out_string = m_stream.str().c_str();
    switch (logData->level) {
    case WARN_LL:
        FMsg::Logf_Internal(
            UE_LOG_SOURCE_FILE(__FILE__),
            __LINE__,
            LogTemp.GetCategoryName(),
            ELogVerbosity::Warning,
            TEXT("%s"),
            UTF8_TO_TCHAR(out_string.data())
        );
        break;
    case ERROR_LL:
        FMsg::Logf_Internal(
            UE_LOG_SOURCE_FILE(__FILE__),
            __LINE__,
            LogTemp.GetCategoryName(),
            ELogVerbosity::Error,
            TEXT("%s"),
            UTF8_TO_TCHAR(out_string.data())
        );
        break;
    case FATAL_LL:
        FMsg::Logf_Internal(
            UE_LOG_SOURCE_FILE(__FILE__),
            __LINE__,
            LogTemp.GetCategoryName(),
            ELogVerbosity::Fatal,
            TEXT("%s"),
            UTF8_TO_TCHAR(out_string.data())
        );
        break;
    default:
        FMsg::Logf_Internal(
            UE_LOG_SOURCE_FILE(__FILE__),
            __LINE__,
            LogTemp.GetCategoryName(),
            ELogVerbosity::Display,
            TEXT("%s"),
            UTF8_TO_TCHAR(out_string.data())
        );
        break;
    }
    m_stream.str("");
    m_stream.clear();
#endif

    return true;
}
} // namespace cpplog