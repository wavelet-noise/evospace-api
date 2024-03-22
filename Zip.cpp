//
//  Zip.cpp
//  Evospace
//
//  Created by wavelet noise on 20.11.2023.
//  Copyright © 2023 Epic Games, Inc. All rights reserved.
//

#include "Zip.h"

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
