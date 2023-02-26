#include "ore_data.h"

#include "Evospace/JsonHelper.h"

bool FOreData::SerializeJson(TSharedPtr<FJsonObject> json) {
    json_helper::TrySet(json, TEXT("item"), item);
    json_helper::TrySet(json, TEXT("capacity"), capacity);
    json_helper::TrySet(json, TEXT("gathered"), gathered);
    return true;
}

bool FOreData::DeserializeJson(TSharedPtr<FJsonObject> json) {
    json_helper::TryGetDB(json, TEXT("item"), item);
    json_helper::TryGet(json, TEXT("capacity"), capacity);
    json_helper::TryGet(json, TEXT("gathered"), gathered);
    return true;
}