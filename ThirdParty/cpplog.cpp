#include "cpplog.h"

namespace cpplog {
bool UeLogger::sendLogMessage(LogData *logData) {
    OstreamLogger::sendLogMessage(logData);
    std::string out_string = m_stream.str().c_str();
    switch (logData->level) {
    case WARN:
        FMsg::Logf_Internal(
            UE_LOG_SOURCE_FILE(__FILE__),
            __LINE__,
            LogTemp.GetCategoryName(),
            ELogVerbosity::Warning,
            TEXT("%s"),
            UTF8_TO_TCHAR(out_string.data())
        );
        break;
    case ERROR:
        FMsg::Logf_Internal(
            UE_LOG_SOURCE_FILE(__FILE__),
            __LINE__,
            LogTemp.GetCategoryName(),
            ELogVerbosity::Error,
            TEXT("%s"),
            UTF8_TO_TCHAR(out_string.data())
        );
        break;
    case FATAL:
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

    return true;
}
} // namespace cpplog