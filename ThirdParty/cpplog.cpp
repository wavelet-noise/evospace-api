#include "CppLog.h"
#include <filesystem>

namespace cpplog {

void SessionRotatingLogger::RotateLogs() {
  std::vector<std::filesystem::path> logFiles;

  if (!std::filesystem::exists(m_path) || !std::filesystem::is_directory(m_path)) {
    std::filesystem::create_directories(m_path);
  }

  // Assuming m_path is a directory where logs are stored
  for (const auto &entry : std::filesystem::directory_iterator(m_path)) {
    if (entry.is_regular_file()) {
      logFiles.push_back(entry.path());
    }
  }

  // Keep only the latest 10 logs
  if (logFiles.size() > 10) {
    std::sort(logFiles.begin(), logFiles.end(), [](const std::filesystem::path &a, const std::filesystem::path &b) {
      return std::filesystem::last_write_time(a) > std::filesystem::last_write_time(b);
    });

    logFiles.resize(10); // Keep first 10 after sorting by modification time
    for (size_t i = 10; i < logFiles.size(); ++i) {
      std::filesystem::remove(logFiles[i]);
    }
  }
}

bool UeStringArrayLogger::sendLogMessage(LogData *logData) {
  OstreamLogger::sendLogMessage(logData);
  std::string out_string = m_stream.str().c_str();
  log.Add(UTF8_TO_TCHAR(out_string.data()));
  return true;
}

bool UeLogger::sendLogMessage(LogData *logData) {
#if WITH_EDITOR
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
      UTF8_TO_TCHAR(out_string.data()));
    break;
  case ERROR_LL:
    FMsg::Logf_Internal(
      UE_LOG_SOURCE_FILE(__FILE__),
      __LINE__,
      LogTemp.GetCategoryName(),
      ELogVerbosity::Error,
      TEXT("%s"),
      UTF8_TO_TCHAR(out_string.data()));
    break;
  case FATAL_LL:
    FMsg::Logf_Internal(
      UE_LOG_SOURCE_FILE(__FILE__),
      __LINE__,
      LogTemp.GetCategoryName(),
      ELogVerbosity::Fatal,
      TEXT("%s"),
      UTF8_TO_TCHAR(out_string.data()));
    break;
  default:
    FMsg::Logf_Internal(
      UE_LOG_SOURCE_FILE(__FILE__),
      __LINE__,
      LogTemp.GetCategoryName(),
      ELogVerbosity::Display,
      TEXT("%s"),
      UTF8_TO_TCHAR(out_string.data()));
    break;
  }
  m_stream.str("");
  m_stream.clear();
#endif

  return true;
}
} // namespace cpplog