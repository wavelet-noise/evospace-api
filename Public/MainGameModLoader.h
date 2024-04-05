#pragma once
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "ThirdParty/cpplog.h"
#include "ThirdParty/luabridge/LuaBridge.h"

#include <string>
#include <array>

#include "MainGameModLoader.generated.h"

class UPrototype;
namespace evo {
class LegacyLuaState;
}
class UMainGameModLoader;
namespace evo {
class ModLoadingLuaState;
}

class UJsonObjectLibrary;
class UMod;
class ModLoadingContext;

class StringStreamPortion {
  public:
  std::ostringstream input;
  int severity = TRACE_LL;

  StringStreamPortion(ModLoadingContext &par, int sev)
    : severity(sev), parent(par) {}

  ~StringStreamPortion();

  template <typename Ty>
  StringStreamPortion &operator<<(Ty Str) {
    input << Str;
    return *this;
  }

  template <typename Ty>
  StringStreamPortion &operator<<(Ty *Str) {
    if (Str) {
      input << Str;
    } else {
      input << "nil";
    }
    return *this;
  }

  ModLoadingContext &parent;

  StringStreamPortion(const StringStreamPortion &v) = delete;
  StringStreamPortion &operator=(const StringStreamPortion &v) = delete;
};

class ModLoadingContext {
  public:
  ModLoadingContext(evo::LegacyLuaState *lua, UMainGameModLoader *);
  ~ModLoadingContext() = default;

  ModLoadingContext(const ModLoadingContext &c) = delete;
  ModLoadingContext &operator=(const ModLoadingContext &c) = delete;

  std::string message;

  std::vector<std::string> errors;

  evo::LegacyLuaState *lua_state;

  UMainGameModLoader *loader;

  StringStreamPortion log(int sev) {
    ++log_level_counts[sev];
    return StringStreamPortion(*this, sev);
  }

  std::string Get();
  void Set(std::string_view m);
  FCriticalSection critical;

  std::array<int32, MAX_LL> log_level_counts = { 0 };

  bool has_errors() {
    return log_level_counts[ERROR_LL] || log_level_counts[FATAL_LL];
  }
};

enum class ModTickLoadStatus { NotChecked,
                               Ok,
                               Error,
                               Download };

UCLASS()
/**
 * 
 */
class UMainGameModLoader : public UObject {
  GENERATED_BODY()
  public:
  UPROPERTY(VisibleAnywhere)
  UJsonObjectLibrary *mJsonObjectLibrary;

  UPROPERTY(VisibleAnywhere)
  TArray<int64> mSubscribedIds;

  void LoadDirectory(ModLoadingContext &context, const FString &path, const FString &dir);
  bool LoadSync();

  std::vector<UObject *> GetPrototypes();

  bool SelectLocalization(const FString &locale);

  std::optional<luabridge::LuaRef> lastRegisteredMod;
  void RegisterPrototypeFromTable(const UMod*owner,const luabridge::LuaRef &table);
  void ModInitTable(const luabridge::LuaRef &table);

  static UMainGameModLoader *GetMainGameModLoader();

  void RegisterPrototype(const UMod * owner, UPrototype *proto) const;

  bool AllSequence(ModLoadingContext &cotext);

  int VanillaJsonCount = 0;

  UPROPERTY()
  UMod *mCurrentMod;

  UPROPERTY()
  TArray<UMod *> mods;

  ModTickLoadStatus current_mod_status = ModTickLoadStatus::NotChecked;

  UPROPERTY()
  TArray<FString> error_log;

  UFUNCTION(BlueprintCallable)
  int32 GetPhase() const { return phase; }

  private:
  static bool LoadLoc(ModLoadingContext &context, const FString &path, const FString &locale = "source", bool isSource = true);

  bool PrepareMods(ModLoadingContext &context);
  bool LuaTickCaller(ModLoadingContext &context, std::string_view function_name, int32 seq);
  bool SubscriptionLoading(ModLoadingContext &context);
  bool Init(ModLoadingContext &context, int32 seq);
  bool PostInit(ModLoadingContext &context, int32 seq);
  bool PreInit(ModLoadingContext &context, int32 seq);
  bool ResearchPostprocess(ModLoadingContext &context);
  bool LuaPostprocess(ModLoadingContext &context);
  bool CollectingItems(ModLoadingContext &context);
  bool ModContentLoad(ModLoadingContext &cotext, int phase);

  UPROPERTY()
  TArray<UMod *> lostMods;

  UPROPERTY(VisibleAnywhere)
  int current_mod = 0;

  UPROPERTY(VisibleAnywhere)
  int phase = 0;
};
