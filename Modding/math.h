#pragma once
#include "CoreMinimal.h"
#include "ThirdParty/luabridge/luabridge.h"

inline void registerUnrealClasses(lua_State *L) {
    // FColor
    luabridge::getGlobalNamespace(L)
        .beginClass<FColor>("FColor")
        .addFunction(
            "new",
            [](uint8 r, uint8 g, uint8 b, uint8 a) {
                return FColor(r, g, b, a);
            }
        )
        .addProperty("r", &FColor::R, true)
        .addProperty("g", &FColor::G, true)
        .addProperty("b", &FColor::B, true)
        .addProperty("a", &FColor::A, true)
        .addStaticProperty("red", []() { return FColor::Red; })
        .addStaticProperty("green", []() { return FColor::Green; })
        .addStaticProperty("blue", []() { return FColor::Blue; })
        .addStaticProperty("yellow", []() { return FColor::Yellow; })
        .addStaticProperty("cyan", []() { return FColor::Cyan; })
        .addStaticProperty("magenta", []() { return FColor::Magenta; })
        .addStaticProperty("white", []() { return FColor::White; })
        .addStaticProperty("black", []() { return FColor::Black; })
        .addStaticProperty("gray", []() { return FColor(128,128,128,255); })
        .addStaticProperty("orange", []() { return FColor::Orange; })
        .addStaticProperty("purple", []() { return FColor::Purple; })
        .addStaticProperty("transparent", []() { return FColor::Transparent; })
        .endClass();

    // FQuat
    luabridge::getGlobalNamespace(L)
        .beginClass<FQuat>("FQuat")
        .addFunction(
            "new",
            [](float x, float y, float z, float w) { return FQuat(x, y, z, w); }
        )
        .addProperty("x", &FQuat::X, true)
        .addProperty("y", &FQuat::Y, true)
        .addProperty("z", &FQuat::Z, true)
        .addProperty("w", &FQuat::W, true)
        .addFunction("get_forward_vector", &FQuat::GetForwardVector)
        .addFunction("get_right_vector", &FQuat::GetRightVector)
        .addFunction("get_up_vector", &FQuat::GetUpVector)
        .endClass();

    // FTransform
    luabridge::getGlobalNamespace(L)
        .beginClass<FTransform>("FTransform")
        .addFunction("new", []() { return FTransform(); })
        .addFunction("set_location", &FTransform::SetLocation)
        .addFunction("set_rotation", &FTransform::SetRotation)
        .addFunction("set_scale", &FTransform::SetScale3D)
        .addFunction("get_location", &FTransform::GetLocation)
        .addFunction("get_rotation", &FTransform::GetRotation)
        .addFunction("get_scale", &FTransform::GetScale3D)
        .endClass();
}
