#pragma once
#include "CoreMinimal.h"
#include "Evospace/CoordinateSystem.h"
#include "ThirdParty/luabridge/luabridge.h"

inline void registerMathClasses(lua_State *L) {
    // FColor
    luabridge::getGlobalNamespace(L)
        .beginClass<FColor>("FColor")
        .addStaticFunction(
            "new",
            [](uint8 r, uint8 g, uint8 b, uint8 a) {
                return FColor(r, g, b, a);
            }
        )
        .addProperty("r", &FColor::R, true)
        .addProperty("g", &FColor::G, true)
        .addProperty("b", &FColor::B, true)
        .addProperty("a", &FColor::A, true)
        .addStaticProperty("red", +[]() { return FColor::Red; })
        .addStaticProperty("green", +[]() { return FColor::Green; })
        .addStaticProperty("blue", +[]() { return FColor::Blue; })
        .addStaticProperty("yellow", +[]() { return FColor::Yellow; })
        .addStaticProperty("cyan", +[]() { return FColor::Cyan; })
        .addStaticProperty("magenta", +[]() { return FColor::Magenta; })
        .addStaticProperty("white", +[]() { return FColor::White; })
        .addStaticProperty("black", +[]() { return FColor::Black; })
        .addStaticProperty("gray", +[]() { return FColor(128,128,128,255); })
        .addStaticProperty("orange", +[]() { return FColor::Orange; })
        .addStaticProperty("purple", +[]() { return FColor::Purple; })
        .addStaticProperty("transparent", +[]() { return FColor::Transparent; })
        .endClass();

    // FQuat
    luabridge::getGlobalNamespace(L)
        .beginClass<FQuat>("FQuat")
        .addStaticFunction(
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
        .addStaticFunction("new", []() { return FTransform(); })
        .addFunction("set_location", &FTransform::SetLocation)
        .addFunction("set_rotation", &FTransform::SetRotation)
        .addFunction("set_scale", &FTransform::SetScale3D)
        .addFunction("get_location", &FTransform::GetLocation)
        .addFunction("get_rotation", &FTransform::GetRotation)
        .addFunction("get_scale", &FTransform::GetScale3D)
        .endClass();

        luabridge::getGlobalNamespace(L)
        .beginClass<Vec3i>("Vec3i")
        .addStaticFunction(
            "new", +[](int32 x, int32 y, int32 z) { return Vec3i(x, y, z); }
        )
        .addStaticFunction(
            "one", +[]() { return Vec3i(1); }
        )
        .addStaticProperty(
            "zero", +[]() { return Vec3i(0); }
        )
        .addStaticProperty(
            "up", +[]() { return Side::Up; }
        )
        .addStaticProperty(
            "down", +[]() { return Side::Down; }
        )
        .addStaticProperty(
            "left", +[]() { return Side::Left; }
        )
        .addStaticProperty(
            "right", +[]() { return Side::Right; }
        )
        .addStaticProperty(
            "back", +[]() { return Side::Back; }
        )
        .addStaticProperty(
            "front", +[]() { return Side::Front; }
        )
        .addProperty("x", &Vec3i::X, true)
        .addProperty("y", &Vec3i::Y, true)
        .addProperty("z", &Vec3i::Z, true)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<Vec2i>("Vec2i")
        .addStaticFunction(
            "new", +[](int32 x, int32 y) { return Vec2i(x, y); }
        )
        .addStaticProperty(
            "zero", +[]() { return Vec2i(0); }
        )
        .addStaticProperty(
            "one", +[]() { return Vec2i(1); }
        )
        .addProperty("x", &Vec2i::X, true)
        .addProperty("y", &Vec2i::Y, true)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<FVector>("Vec3")
        .addStaticFunction(
            "new", +[](float x, float y, float z) { return FVector(x, y, z); }
        )
        .addStaticFunction(
            "one", +[]() { return FVector(1); }
        )
        .addStaticProperty(
            "zero", +[]() { return FVector(0); }
        )
        .addStaticProperty(
            "up", +[]() { return FVector(Side::Up.X, Side::Up.Y, Side::Up.Z); }
        )
        .addStaticProperty(
            "down",
            +[]() { return FVector(Side::Down.X, Side::Down.Y, Side::Down.Z); }
        )
        .addStaticProperty(
            "left",
            +[]() { return FVector(Side::Left.X, Side::Left.Y, Side::Left.Z); }
        )
        .addStaticProperty(
            "right",
            +[]() {
                return FVector(Side::Right.X, Side::Right.Y, Side::Right.Z);
            }
        )
        .addStaticProperty(
            "back",
            +[]() { return FVector(Side::Back.X, Side::Back.Y, Side::Back.Z); }
        )
        .addStaticProperty(
            "front",
            +[]() {
                return FVector(Side::Front.X, Side::Front.Y, Side::Front.Z);
            }
        )
        .addProperty("x", &FVector::X, true)
        .addProperty("y", &FVector::Y, true)
        .addProperty("z", &FVector::Z, true)
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginNamespace("cs")
        .addFunction(
            "bp2sp",
            +[](const Vec3i &bpos) { auto spos = cs::WBtoS(bpos, gSectorSize); }
        )
        .addFunction(
            "w2bp", +[](const FVector &world) { auto spos = cs::WtoWB(world); }
        )
        .addFunction(
            "bp2w", +[](const Vec3i &bpos) { auto spos = cs::WBtoW(bpos); }
        )
        .addFunction(
            "w2sp",
            +[](const FVector &world) {
                auto spos = cs::WBtoS(world, gSectorSize);
            }
        )
        .endNamespace();
}
