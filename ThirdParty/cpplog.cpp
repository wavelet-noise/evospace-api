#include "cpplog.h"

namespace cpplog {
bool UeLogger::sendLogMessage(LogData* logData)
{
    OstreamLogger::sendLogMessage(logData);
    std::string out_string = m_stream.str().c_str();
    switch (logData->level) {
    case WARN:
        UE_LOG(LogTemp, Warning, TEXT("%s"), UTF8_TO_TCHAR(out_string.data()));
        break;
    case ERROR:
        UE_LOG(LogTemp, Error, TEXT("%s"), UTF8_TO_TCHAR(out_string.data()));
        break;
    case FATAL:
        UE_LOG(LogTemp, Fatal, TEXT("%s"), UTF8_TO_TCHAR(out_string.data()));
        break;
    default:
        UE_LOG(LogTemp, Display, TEXT("%s"), UTF8_TO_TCHAR(out_string.data()));
        break;
    }
    m_stream.str("");
    m_stream.clear();

    return true;
}
}