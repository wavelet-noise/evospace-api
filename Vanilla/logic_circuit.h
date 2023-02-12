// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "Modding/legacy_lua_state.h"
#include "Vanilla/tiered_block.h"

#include "logic_circuit.generated.h"

class ADimension;
class UDataOutputAccessor;
class UInventory;
class UDataInputAccessor;
class UItem;
class AMainPlayerController;
class UInternalInventory;
class USingleSlotInventory;

/**
 * @brief LogicNetworkState
 */
class LogicNetworkState : public evo::LegacyLuaState {

  public:
    LogicNetworkState();

    static LogicNetworkState &Get();

    // UFUNCTION()
    // FLuaValue GetClass(FLuaValue name);
    //
    // UFUNCTION()
    // FLuaValue FindObject(FLuaValue name);
    //
    // UFUNCTION()
    // FLuaValue SetBlockInDim(FLuaValue x, FLuaValue y, FLuaValue z,
    //                         FLuaValue sb);

    void RequireDimesion(ADimension *dim);
    virtual void Log(const FString &Message);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Output;

    // virtual void
    // ReceiveLuaCountHook_Implementation(const FLuaDebug &LuaDebug);

  private:
    ADimension *dimension;
};

UCLASS()
/**
 * @brief Vanilla lua controller BlockLogic
 */
class ULuaController : public UTieredBlock {
    GENERATED_BODY()

  public:
    ULuaController();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual bool is_block_tick() const override;

    UFUNCTION(BlueprintCallable)
    void Execute();

    virtual void Tick() override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Code;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString LastError;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Output;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> ConsoleOutput;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    USingleSlotInventory *mElectricInventory;
};

UENUM(BlueprintType)
enum class ELogicInterfaceMode : uint8 {
    Nothing,
    Inventory,
    Network,
    Crafter,
    Switch,
    ModeMax
};

UENUM(BlueprintType)
enum class ELogicControllerMode : uint8 { Nothing, Crafter, Switch, ModeMax };

UENUM(BlueprintType)
enum class ELogicDisplayMode : uint8 {
    Nothing,
    OnOff,
    Color,
    Numeric,
    ModeMax
};

UCLASS()
class ULogicInterface : public UTieredBlock {
    GENERATED_BODY()

  public:
    ULogicInterface();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UFUNCTION(BlueprintCallable)
    void SetMode(ELogicInterfaceMode mode);

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ELogicInterfaceMode mSelectedMode = ELogicInterfaceMode::Nothing;

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual void Tick() override;

    void BlockBeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    UInternalInventory *mInventoryRight;

    bool is_block_tick() const override;

  private:
    UPROPERTY()
    UDataOutputAccessor *mAccessorRight;

    UPROPERTY()
    UBaseAccessor *mAccessorLeft;

    UPROPERTY()
    ADimension *mDim;

    UPROPERTY()
    UItem *mCapacityItem;

    UPROPERTY()
    UItem *mBusyItem;

    UPROPERTY()
    UItem *mInputErrorItem;

    UPROPERTY()
    UItem *mOutputErrorItem;

    UPROPERTY()
    UItem *mProgressItem;

    UPROPERTY()
    UItem *mSwitchedItem;

  public:
    EVO_LUA_CODEGEN_DB_EX(LogicInterface);
    static void RegisterLua(lua_State *L);
};

UCLASS()
class ULogicController : public UFilteringBlock {
    GENERATED_BODY()

  public:
    ULogicController();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UFUNCTION(BlueprintCallable)
    void SetMode(ELogicControllerMode mode);

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ELogicControllerMode mSelectedMode = ELogicControllerMode::Nothing;

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual void Tick() override;

    void BlockBeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    UInternalInventory *mInventoryLeft;

    UPROPERTY(BlueprintReadOnly)
    UInternalInventory *mSetup;

    bool is_block_tick() const override;

    void ChangeFilter(int32 inventory, int32 slot, UItem *item) override;

  private:
    UPROPERTY()
    UDataInputAccessor *mAccessorLeft;

    UPROPERTY()
    UBaseAccessor *mAccessorRight;

  public:
    EVO_LUA_CODEGEN_DB_EX(LogicController);
    static void RegisterLua(lua_State *L);
};

UCLASS()
class ULogicDisplay : public UFilteringBlock {
    GENERATED_BODY()

  public:
    ULogicDisplay();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual void Tick() override;

    void BlockBeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    UInternalInventory *mInventoryLeft;

    UPROPERTY(BlueprintReadOnly)
    UInternalInventory *mSetup;

    UPROPERTY(BlueprintReadWrite)
    FLinearColor mColor;

    UFUNCTION(BlueprintCallable)
    void SetMode(ELogicDisplayMode mode);

    UPROPERTY(BlueprintReadWrite)
    int64 mNumeric = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ELogicDisplayMode mSelectedMode = ELogicDisplayMode::Nothing;

    bool is_block_tick() const override;

    void ChangeFilter(int32 inventory, int32 slot, UItem *item) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UMaterialInstanceDynamic *mMaterialDyn;

  private:
    UPROPERTY()
    UDataInputAccessor *mAccessorLeft;

  public:
    EVO_LUA_CODEGEN_DB_EX(LogicDisplay);
    static void RegisterLua(lua_State *L);
};

UENUM(BlueprintType)
enum class ELogicCircuitMode : uint8 {
    And,
    Or,
    Xor,

    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    Equal,
    NotEqual,
    Const,

    Add,
    Sub,
    Mul,
    Div,
    Mod,

    Wire,

    Abs,

    ModeMax
};

UCLASS()
class UCircuitSetup : public UObject, public ISerializableJson {
    GENERATED_BODY()

  public:
    UCircuitSetup();

    virtual bool SerializeJson(TSharedPtr<FJsonObject> json) override;
    virtual bool DeserializeJson(TSharedPtr<FJsonObject> json) override;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    UInventory *mInputs;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    UInventory *mOutputs;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    int64 mValue = 1;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool mInputValue = false;
};

class LogicFunctor {
  public:
    LogicFunctor() = default;
    virtual ~LogicFunctor() = default;
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) = 0;
    virtual int32 GetInputsCount() = 0;
};

template <int argcount> class TLogicFunctor : public LogicFunctor {
  public:
    TLogicFunctor() = default;
    virtual ~TLogicFunctor() = default;
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) = 0;
    virtual int32 GetInputsCount() override { return argcount; };
};

class AndFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class OrFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class XorFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class GreaterFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class AddFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class SubFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class ConstFunctor : public TLogicFunctor<0> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class MulFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class DivFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class ModFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class GreaterEqualFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class LessFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class LessEqualFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class EqualFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class NotEqualFunctor : public TLogicFunctor<2> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class WireFunctor : public TLogicFunctor<0> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};
class AbsFunctor : public TLogicFunctor<1> {
    virtual void operator()(
        const UInventory *input, UCircuitSetup *setup, UInventory *output
    ) override;
};

UCLASS()
class ULogicCircuit : public UFilteringBlock {
    GENERATED_BODY()

  public:
    ULogicCircuit();

    virtual TSubclassOf<UBlockWidget> GetWidgetClass() const override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ELogicCircuitMode mSelectedMode = ELogicCircuitMode::Const;

    virtual bool LoadSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;
    virtual bool SaveSettings(
        TSharedPtr<FJsonObject> json, AMainPlayerController *mpc = nullptr
    ) override;

    virtual void Tick() override;

    UFUNCTION(BlueprintCallable)
    void SetMode(ELogicCircuitMode mode);

    UFUNCTION(BlueprintCallable)
    void SetValue(int64 mode);

    UFUNCTION(BlueprintCallable)
    void SetInputValue(bool mode);

    UPROPERTY(VisibleAnywhere)
    UDataInputAccessor *mAccessorLeft;

    UPROPERTY(VisibleAnywhere)
    UDataOutputAccessor *mAccessorRight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UInternalInventory *mInventoryLeft;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UInternalInventory *mInventoryRight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCircuitSetup *mSetup;

    // UPROPERTY(VisibleAnywhere)
    //	UInventory * mInventoryRightLast;

    UPROPERTY(VisibleAnywhere)
    UItem *moutput;

    virtual bool is_block_tick() const override;

    void ChangeFilter(int32 inventory, int32 slot, UItem *item) override;

  public:
    EVO_LUA_CODEGEN_DB_EX(LogicCircuit);
    static void RegisterLua(lua_State *L);
};
