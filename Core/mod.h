// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Evospace/SerializableJson.h"

#include <Dom/JsonObject.h>

#include <string>
#include <vector>

#include "Mod.generated.h"

UCLASS(BlueprintType)
/**
 * @brief Mod object
 */
class UMod : public UObject, public ISerializableJson {
    GENERATED_BODY()

  public:
    /**
     * @brief name
     */
    std::string name;

    /**
     * @brief version
     */
    std::string version;

    /**
     * @brief title
     */
    std::string title;

    /**
     * @brief evospace_version
     */
    std::string evospace_version;

    /**
     * @brief created_by
     */
    std::string created_by;

    /**
     * @brief description
     */
    std::string description;

    /**
     * @brief author
     */
    std::string author;

    /**
     * @brief dependencies
     */
    std::vector<std::string> dependencies;

    std::string bytecode;

    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;
    bool DeserializeFromDirectory(const FString &s);

    FString Name() const { return UTF8_TO_TCHAR(name.data()); }
    FString Version() const { return UTF8_TO_TCHAR(version.data()); }
    FString Title() const { return UTF8_TO_TCHAR(title.data()); }
    FString EvospaceVersion() const {
        return UTF8_TO_TCHAR(evospace_version.data());
    }
    FString CreatedBy() const { return UTF8_TO_TCHAR(created_by.data()); }
    FString Description() const { return UTF8_TO_TCHAR(description.data()); }
    FString Author() const { return UTF8_TO_TCHAR(author.data()); }

    TArray<FString> Dependencies() const {
        TArray<FString> arr;
        for (auto &a : dependencies) {
            arr.Add(UTF8_TO_TCHAR(name.data()));
        }
        return arr;
    }
};