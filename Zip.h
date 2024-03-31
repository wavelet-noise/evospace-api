//
//  Zip.hpp
//  Evospace
//
//  Created by wavelet noise on 20.11.2023.
//  Copyright © 2023 Epic Games, Inc. All rights reserved.
//
#pragma once
#ifndef Zip_hpp
#define Zip_hpp

#include "CoreMinimal.h"

#include <Serialization/BufferArchive.h>

#include <memory>
#include <string>
#include <vector>

namespace miniz_cpp {
class zip_file;
}

class Zip {
  public:
  Zip(const FString &file);
  ~Zip();

  void Open();
  void Empty();
  void Save();

  FString ReadF(const std::string &subpath);
  std::string Read(const std::string &subpath);
  TArray<uint8> Read8(const std::string &subpath);

  void Extract(std::string_view path);

  void Write(const std::string &subpath, const FBufferArchive &arch);
  void Write(const std::string &subpath, const std::string &content);
  void Write(const std::string &subpath, int32 content);
  void Write(const std::string &subpath, const std::vector<uint8> &content);
  void Write(const std::string &subpath, const std::vector<uint16> &content);

  std::vector<std::string> NameList();

  static void ExtractAllFiles(const std::string &zipFilePath, const std::string &extractionPath);

  std::unique_ptr<miniz_cpp::zip_file> zipfile;
  std::string filename;
};

#endif /* Zip_hpp */
