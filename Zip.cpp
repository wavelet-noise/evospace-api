//
//  Zip.cpp
//  Evospace
//
//  Created by wavelet noise on 20.11.2023.
//  Copyright © 2023 Epic Games, Inc. All rights reserved.
//

#include "Zip.h"

#include "StaticLogger.h"
#include "Evospace/Shared/ThirdParty/zip_file.h"

#include <bitset>

namespace {

union Converter {
  float f;
  int32 i;
  char arr[4];
};

union Converter16 {
  uint16 u;
  char arr[2];
};

std::string intToBytes(int paramInt) {
  Converter c;
  c.i = paramInt;

  std::string s(c.arr, 4);
  return s;
}

std::string floatToBytes(float paramInt) {
  Converter c;
  c.f = paramInt;

  std::string s(c.arr, 4);
  return s;
}
} // namespace

Zip::Zip(const FString &file) {
  filename = std::string(TCHAR_TO_UTF8(*file));
}
Zip::~Zip() {
  if (zipfile) {
    zipfile->reset();
  }
}

void Zip::Open() {
  zipfile = std::make_unique<miniz_cpp::zip_file>(filename);
}

void Zip::Empty() {
  zipfile = std::make_unique<miniz_cpp::zip_file>();
}

std::vector<std::string> Zip::NameList() {
  return zipfile->namelist();
}

void Zip::Extract(std::string_view path) {
  zipfile->extractall(path.data());
}

void Zip::ExtractAllFiles(const std::string& zipFilePath, const std::string& extractionPath) {
  mz_zip_archive zip_archive;
  memset(&zip_archive, 0, sizeof(zip_archive));

  if (!mz_zip_reader_init_file(&zip_archive, zipFilePath.c_str(), 0)) {
    LOG(ERROR_LL) << "Could not initialize zip archive";
    return;
  }

  int file_count = (int)mz_zip_reader_get_num_files(&zip_archive);
  for (int i = 0; i < file_count; i++) {
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) {
      LOG(ERROR_LL) << "Could not get file stat for file index " << i;
      continue;
    }

    // Create a full path for the file to be extracted
    std::string fullPath = extractionPath + "/" + file_stat.m_filename;

    // Check if the path includes a directory, and if so, create the directory
    auto dirPath = std::filesystem::path(fullPath).parent_path();
    if (!dirPath.empty()) {
      std::filesystem::create_directories(dirPath);
    }

    // Extract the file
    if (!mz_zip_reader_extract_to_file(&zip_archive, i, fullPath.c_str(), 0)) {
      LOG(ERROR_LL) << "Could not extract file " << file_stat.m_filename;
    } else {
      //std::cout << "Extracted " << file_stat.m_filename << " successfully." << std::endl;
    }
  }

  mz_zip_reader_end(&zip_archive);
}

TArray<uint8> Zip::Read8(const std::string &subpath) {
  auto content = zipfile->read(subpath);

  TArray<uint8> content8;
  content8.SetNum(content.size() * 2);

  for (int i = 0; i < content.size(); ++i) {
    Converter16 conv;
    conv.u = content[i];

    content8[i * 2 + 0] = conv.arr[0];
    content8[i * 2 + 1] = conv.arr[1];
  }

  return content8;
}

FString Zip::ReadF(const std::string &subpath) {
  auto content = zipfile->read(subpath);

  FString contentF;

  for (int i = 0; i < content.size(); ++i) {
    contentF.AppendChar(static_cast<TCHAR>(content[i]));
  }

  return contentF;
}

std::string Zip::Read(const std::string &subpath) {
  return zipfile->read(subpath);
}

void Zip::Write(const std::string &subpath, const std::string &content) {
  return zipfile->writestr(subpath, content);
}

void Zip::Write(const std::string &subpath, int32 content) {
  Write(subpath, intToBytes(content));
}

void Zip::Write(const std::string &subpath, const std::vector<uint8> &content) {
  std::string str(content.begin(), content.end());
  Write(subpath, str);
}

void Zip::Write(
  const std::string &subpath, const std::vector<uint16> &content) {
  std::vector<uint8> content8;
  content8.resize(content.size() * 2);

  for (int i = 0; i < content.size(); ++i) {
    Converter16 conv;
    conv.u = content[i];

    content8[i * 2 + 0] = conv.arr[0];
    content8[i * 2 + 1] = conv.arr[1];
  }

  std::string str(content8.begin(), content8.end());
  Write(subpath, str);
}

void Zip::Write(const std::string &subpath, const FBufferArchive &arch) {

  std::string str;
  str.resize(arch.Num());
  for (int i = 0; i < arch.Num(); ++i) {
    str[i] = arch[i];
  }
  Write(subpath, str);
}

void Zip::Save() {
  zipfile->save(filename);
}
