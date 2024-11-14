// Copyright (c) 2017 - 2024, Samsonov Andrey. All Rights Reserved.

#include "Mod.h"

#include "EvospaceLuaState.h"
#include "LegacyLuaState.h"
#include "Evospace/JsonHelper.h"
#include "Evospace/Misc/JsonLuaConverter.h"
#include "Public/MainGameModLoader.h"

#include <regex>

void UMod::lua_state_close() {
  mod_table.reset();
  config.reset();
}

void UMod::SaveConfig(const FString &directory, ModLoadingContext &context) const {
  if (config.has_value() && config->isTable()) {
    auto json = JLConverter::LuaTableToJson(config.value());

    FString json_data = "";
    const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&json_data, 0);
    FJsonSerializer::Serialize(json.ToSharedRef(), Writer);

    FString file_name = directory / Name() + ".json";

    FFileHelper::SaveStringToFile(json_data, *file_name);
  }
}

void UMod::LoadConfig(const FString &directory, ModLoadingContext &context) {
  IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
  FString file_name = directory / Name() + ".json";
  FString json_data;
  if (PlatformFile.FileExists(*file_name)) {
    FFileHelper::LoadFileToString(json_data, *file_name);
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(json_data);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
      config = JLConverter::JsonToLuaTable(context.lua_state->L, JsonObject);
    }
  } else {
    LOG(WARN_LL) << "No config for mod " << mName;
  }
}

bool UMod::DeserializeJson(TSharedPtr<FJsonObject> json) {
  json_helper::TryGet(json, "name", mName);
  json_helper::TryGet(json, "version", mVersion);
  json_helper::TryGet(json, "title", mTitle);
  json_helper::TryGet(json, "author", mAuthor);
  json_helper::TryGet(json, "evospace_version", mEvospaceVersion);
  json_helper::TryGet(json, "dependencies", dependencies);
  json_helper::TryGet(json, "description", mDescription);

  for (auto &s : dependencies) {
    s = std::regex_replace(s, std::regex(" "), "");
  }

  return true;
}

bool UMod::DeserializeFromDirectory(const FString &directory, ModLoadingContext &context) {
  IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
  {
    FString json_data;
    if (PlatformFile.FileExists(*(directory / "info.json"))) {
      FFileHelper::LoadFileToString(json_data, *(directory / "info.json"));
    } else {
      LOG(WARN_LL) << *directory << " has no info.json";
      return false;
    }

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(json_data);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
      DeserializeJson(JsonObject);
    }
  }

  auto lua_state = context.lua_state;

  auto file = directory / "init.lua";
  if (PlatformFile.FileExists(*file)) {
    FString json_data;
    FFileHelper::LoadFileToString(json_data, *(directory / "init.lua"));
    luabridge::setGlobal(lua_state->L, nullptr, "init");
    context.loader->lastRegisteredMod = {};
    if (auto result = lua_state->RunCode(TCHAR_TO_UTF8(*json_data), "@init")) {
      if (context.loader->lastRegisteredMod.has_value()) {
        mod_table = context.loader->lastRegisteredMod.value();
        if (this->mod_table->isTable()) {
          LOG(INFO_LL) << "Init function table registered";
          if ((*mod_table)["config"].isTable()) {
            LOG(INFO_LL) << "Config table registered";
            config = (*mod_table)["config"];
          }
        } else {
          LOG(ERROR_LL) << "db:mod expects to get a table";
        }
      } else {
        LOG(ERROR_LL) << "Registration unknown error";
      }
    } else {
      LOG(ERROR_LL) << "init.lua file execution error";
    }
  }

  return true;
}
