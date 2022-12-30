// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "../static_logger.h"
#include "Evospace/Common.h" //TODO: remove
#include "Evospace/MainGameInstance.h"
#include "Evospace/Shared/ThirdParty/luabridge.h"

#include <unordered_map>
#include <vector>

#include "prototype.generated.h"

class Base;

/*namespace Events {
        struct OnAnimationFinished
        {
                ECS_DECLARE_TYPE;

                Entity* entity;
                ComponentHandle<Render> render;
        };

        struct OnEntitySpawned
        {
                ECS_DECLARE_TYPE;

                Entity* entity;
        };
}*/

#define EVO_LUA_CODEGEN_DB(type, name)                                         \
  public:                                                                      \
    static type *lua_codegen_cast(UPrototype *parent_inst) {                   \
        return Cast<type>(parent_inst);                                        \
    }                                                                          \
    static void RegisterCommonLua(lua_State *L) {                              \
        luabridge::getGlobalNamespace(L)                                       \
            .beginClass<type>(#name)                                           \
            .addStaticFunction("find", &evo::DB::find_mut<type>)               \
            .addStaticFunction("get", &evo::DB::get<type>)                     \
            .addStaticFunction("get_derived", &evo::DB::get_derived<type>)     \
            .addStaticFunction("cast", &type::lua_codegen_cast)                \
            .endClass();                                                       \
    }

UCLASS(Abstract)
/**
 * @brief Super class for all objects stored in database
 */
class UPrototype
    : public UObject { // : public std::enable_shared_from_this<Static> {
    GENERATED_BODY()

  public:
    // Static(const Static &) = delete;
    // Static &operator=(const Static &) = delete;

    /**
     * @brief Object name in database
     */
    std::string name;
};

namespace evo {

//! helper class for all objects stored in DB
// template <typename Ty_> class StaticHelper : public Static {
//   public:
//     static auto GetLuaLambda() {
//         return [](lua_State *state, void *data) {
//             std::error_code er;
//             luabridge::push(state, reinterpret_cast<Ty_ *>(data), er);
//         };
//     }
// };

//! database of static game objects
class DB {
  public:
    template <typename TReturned> static auto &get_storage() {
        static std::unordered_map<
            std::string,
            std::unique_ptr<TReturned, std::function<void(TReturned *)>>>
            storage;
        return storage;
    }

    template <typename TReturned, typename TCreated>
    static TReturned *get(std::string_view name) {
        using TReturnedNormalized = typename std::remove_cv<TReturned>::type;
        static_assert(std::is_base_of<TReturned, TCreated>());
        auto &gs = get_storage<TReturnedNormalized>();
        if (gs.find(name.data()) == gs.end()) { // TODO: make find
            auto u = std::unique_ptr<
                TReturnedNormalized,
                std::function<void(TReturnedNormalized *)>>(
                NewObject<TCreated>(),
                [](TReturnedNormalized *f) { /*f->ConditionalBeginDestroy();*/ }
            );
            u->name = name;
            TReturnedNormalized *u_ptr = u.get();
            UMainGameInstance::GetMainGameInstance()->mDBStorage.Add(u_ptr);
            gs.insert(std::make_pair(name, std::move(u)));
            return u_ptr;
        } else {
            return gs.find(name.data())->second.get();
        }
    }

    template <typename TReturned> static void Clear() {
        get_storage<TReturned>().clear();
    }

    template <typename TReturned> static TReturned *get(std::string_view name) {
        auto &gs = get_storage<TReturned>();
        if (gs.find(name.data()) == gs.end()) {
            auto u =
                std::unique_ptr<TReturned, std::function<void(TReturned *)>>(
                    NewObject<TReturned>(),
                    [](TReturned *f) { /*f->ConditionalBeginDestroy();*/ }
                );
            u->name = name;
            TReturned *u_ptr = u.get();
            UMainGameInstance::GetMainGameInstance()->mDBStorage.Add(u_ptr);
            gs.insert(std::make_pair(name, std::move(u)));
            LOG(TRACE) << "Registering "
                       << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName())
                       << " with name " << name;
            return u_ptr;
        } else {
            LOG(TRACE) << "Appending "
                       << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName())
                       << " with name " << name;
            return gs.find(name.data())->second.get();
        }
    }

    template <typename TReturned>
    static TReturned *get_derived(std::string_view name, UClass *class_ptr) {
        auto &gs = get_storage<TReturned>();
        if (gs.find(name.data()) == gs.end()) {
            if (!class_ptr) {
                LOG(ERROR) << "trying to register nullptr";
                return nullptr;
            }
            if (!class_ptr->IsChildOf(TReturned::StaticClass())) {
                LOG(ERROR) << TCHAR_TO_UTF8(*class_ptr->GetName())
                           << " is not a child of "
                           << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName()
                              );
                return nullptr;
            }
            auto u =
                std::unique_ptr<TReturned, std::function<void(TReturned *)>>(
                    NewObject<TReturned>(
                        (UObject *)GetTransientPackage(), class_ptr
                    ),
                    [](TReturned *f) { /*f->ConditionalBeginDestroy();*/ }
                );
            u->name = name;
            TReturned *u_ptr = u.get();
            UMainGameInstance::GetMainGameInstance()->mDBStorage.Add(u_ptr);
            gs.insert(std::make_pair(name, std::move(u)));
            LOG(TRACE) << "Registering "
                       << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName())
                       << " with name " << name;
            return u_ptr;
        } else {
            LOG(TRACE) << "Appending "
                       << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName())
                       << " with name " << name;
            return gs.find(name.data())->second.get();
        }
    }

    // template <typename TReturned>
    // static TReturned *
    // RegisterTable(luabridge::LuaRef table, std::string_view name) {
    //     auto &gs = GetStorage<TReturned>();
    //     if (!gs.contains(name.data())) {
    //         auto u = std::make_unique<TReturned>();
    //         u->name = name;
    //         TReturned *uptr = u.get();
    //         gs.insert(std::make_pair(name, std::move(u)));
    //         return uptr;
    //     }
    //
    //     // std::cout << typeid(TReturned).name() << " with name " << name <<
    //     "
    //     // is already exists" << std::endl;
    //     return nullptr;
    // }

    // template <typename TReturned, typename... Types>
    // static TReturned *RegisterArg(std::string_view name, Types... args) {
    //     auto &gs = GetStorage<TReturned>();
    //     if (!gs.contains(name.data())) {
    //         auto u = std::make_unique<TReturned>(args...);
    //         u->name = name;
    //         TReturned *uptr = u.get();
    //         gs.insert(std::make_pair(name, std::move(u)));
    //         return uptr;
    //     }
    //
    //     // std::cout << typeid(TReturned).name() << " with name " << name <<
    //     "
    //     // is already exists" << std::endl;
    //     return nullptr;
    // }

    template <typename _TReturned>
    static const _TReturned *find(std::string_view name) {
        using ReturntdNorm = typename std::remove_cv<_TReturned>::type;
        auto &storage = get_storage<ReturntdNorm>();

        auto res = storage.find(name.data());
        if (res != storage.end()) {
            return reinterpret_cast<ReturntdNorm *>(res->second.get());
        }

        return nullptr;
    }

    template <typename _TReturned>
    static _TReturned *find_mut(std::string_view name) {
        using ReturntdNorm = typename std::remove_cv<_TReturned>::type;
        auto &storage = get_storage<ReturntdNorm>();

        auto res = storage.find(std::string(name));
        if (res != storage.end()) {
            return reinterpret_cast<ReturntdNorm *>(res->second.get());
        }

        return nullptr;
    }

    template <typename _TReturned> static const auto &ObjectIterator() {
        return get_storage<_TReturned>();
    }

    static std::vector<std::pair<void *, std::function<void(void *)>>> mProtos;
    static void
    store_proto(void *proto, std::function<void(void *)> deallocator) {
        mProtos.push_back(std::make_pair(proto, deallocator));
    }

    static void free_protos() {
        for (auto p : mProtos) {
            p.second(p.first);
        }

        ensure(mProtos.empty());
    }

    static std::string_view
    GetLocalizedString(std::string_view table, const FKeyTableObject &object) {
        // if (const auto & loctable = mLocTables.find(table.data()); loctable
        // != mLocTables.end())
        // {
        // 	auto& [k, v] = *loctable;
        //
        // 	if (const auto loctext = v.mLocTexts.find(object.Key); loctext
        // != v.mLocTexts.end())
        // 	{
        // 		return loctext->second;
        // 	}
        // }
        //
        // if (const auto& loctable = mLocTablesSource.find(table.data());
        // loctable != mLocTablesSource.end())
        // {
        // 	auto& [k, v] = *loctable;
        //
        // 	if (const auto loctext = v.mLocTexts.find(object.Key); loctext
        // != v.mLocTexts.end())
        // 	{
        // 		return loctext->second;
        // 	}
        // }

        static std::string dummy = "missed";
        return dummy;
    }

    static std::string GetLocalizedParts(
        const std::vector<FKeyTableObject> &label_parts,
        std::string_view separator = " "
    ) {
        std::string s{};

        // {
        // 	for (auto& k : label_parts)
        // 	{
        // 		s += DB::GetLocalizedString(k.Table, k);
        // 		s += separator;
        // 	}
        // }

        return s;
    }
};

template <typename _TReturned> class LazyBase {
  public:
    LazyBase() = default;

    LazyBase(std::string_view name) : stored(name) {}

    const _TReturned *operator()() const {
        if (stored.size()) {
            base = DB::find<_TReturned>(stored);
            stored.clear();
            stored.shrink_to_fit();
        }

        return base;
    }

    operator bool() const {
        if (stored.size()) {
            base = DB::find<_TReturned>(stored);
            stored.clear();
            stored.shrink_to_fit();
        }

        return !!base;
    }

    mutable const _TReturned *base = nullptr;
    mutable std::string stored;
};
} // namespace evo