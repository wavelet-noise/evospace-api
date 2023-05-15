// Copyright (c) 2017 - 2023, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"
#include "ThirdParty/luabridge/luabridge.h"

#include <Dom/JsonObject.h>

#include <optional>
#include <string>
#include <vector>

#include "Mod.generated.h"

class ModLoadingContext;

UCLASS(BlueprintType)
/**
 * @brief Mod object
 */
class UMod : public UObject, public ISerializableJson {
    GENERATED_BODY()

  public:
    /**
     * @brief name. Must be not empty.
     */
    std::string name;

    /**
     * @brief version. Default value: ""
     */
    std::string version;

    /**
     * @brief title. Default value: ""
     */
    std::string title;

    /**
     * @brief evospace_version. Default value: ""
     */
    std::string evospace_version;

    /**
     * @brief created_by. Default value: ""
     */
    std::string created_by;

    /**
     * @brief description. Default value: ""
     */
    std::string description;

    /**
     * @brief author. Default value: ""
     */
    std::string author;

    /**
     * @brief enabled. Default value: true
     */
    bool enabled = true;

    /**
     * @brief is mod loaded without errors. Default value: false
     */
    bool loaded_without_errors = false;

    /**
     * @brief dependencies
     */
    std::vector<std::string> dependencies;

    std::optional<luabridge::LuaRef> init;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    bool DeserializeFromDirectory(const FString &s, ModLoadingContext &context);

    UFUNCTION(BlueprintCallable)
    FString Name() const { return UTF8_TO_TCHAR(name.data()); }

    UFUNCTION(BlueprintCallable)
    FString Version() const { return UTF8_TO_TCHAR(version.data()); }

    UFUNCTION(BlueprintCallable)
    FString Title() const { return UTF8_TO_TCHAR(title.data()); }

    UFUNCTION(BlueprintCallable)
    FString EvospaceVersion() const {
        return UTF8_TO_TCHAR(evospace_version.data());
    }

    UFUNCTION(BlueprintCallable)
    FString CreatedBy() const { return UTF8_TO_TCHAR(created_by.data()); }

    UFUNCTION(BlueprintCallable)
    FString Description() const { return UTF8_TO_TCHAR(description.data()); }

    UFUNCTION(BlueprintCallable)
    FString Author() const { return UTF8_TO_TCHAR(author.data()); }

    UFUNCTION(BlueprintCallable)
    bool Enabled() const { return enabled; }

    UFUNCTION(BlueprintCallable)
    bool LoadedWithoutErrors() const { return loaded_without_errors; }

    UFUNCTION(BlueprintCallable)
    TArray<FString> Dependencies() const {
        TArray<FString> arr;
        for (auto &a : dependencies) {
            arr.Add(UTF8_TO_TCHAR(name.data()));
        }
        return arr;
    }
};