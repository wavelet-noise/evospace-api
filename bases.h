#pragma once

#include "Evospace/Common.h"
#include "ThirdParty/luabridge.h"
#include "localization_table.h"
#include "template_factory.h"
#include "Evospace/MainGameInstance.h"

#include "static_logger.h"
#include <unordered_map>
#include <vector>

class Base;

namespace evo {
struct BaseFactory {
    struct cmpNameFast {
        bool operator()(std::string_view a, std::string_view b) const {
            return a < b;
        }
    };

    using FactoryType = TemplateFactory<std::string, Base, cmpNameFast>;

    static FactoryType &Get() {
        static FactoryType object;
        return object;
    }
};

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

#define SOG_REGISTER_BASE(type)                                                \
    SOG_REGISTER_BASE_IMPL(type, ecs::BaseFactory::Get(), #type)

class Base : public std::enable_shared_from_this<Base> {
  public:
    Base() = default;
    virtual ~Base() = default;

    Base(const Base &) = delete;
    Base &operator=(const Base &) = delete;

    std::string name;
};

/*template<typename Ty_>
struct BaseHelper : public Base {
        static auto GetPrototypeLambda() {
                return [](ecs::Entity* e, void* proto) {
e->assign_prototype<Ty_>(*reinterpret_cast<Ty_*>(proto)); };
        }
        static auto GetComponentLambda() {
                return [](ecs::Entity* e) -> void* { return e->get_ptr<Ty_>();
};
        }
        static auto GetAnyLambda() {
                return [](void** data) { *data = new Ty_(); };
        }
        static auto GetLuaLambda() {
                return [](lua_State* state, void* data) { std::error_code er;
luabridge::push(state, reinterpret_cast<Ty_*>(data), er);
                };
        }
};*/

//! helper class for all objects stored in DB
template <typename Ty_> struct BaseHelper : public Base {
    static auto GetLuaLambda() {
        return [](lua_State *state, void *data) {
            std::error_code er;
            luabridge::push(state, reinterpret_cast<Ty_ *>(data), er);
        };
    }
};

//! database of static game objects
class DB {
  public:
    template <typename TReturned> static auto &GetStorage() {
        static std::unordered_map<
            std::string,
            std::unique_ptr<TReturned, std::function<void(TReturned *)>>>
            storage;
        return storage;
    }

    template <typename TReturned, typename TCreated>
    static TReturned *Register(std::string_view name) {
        using ReturntdNorm = typename std::remove_cv<TReturned>::type;
        static_assert(std::is_base_of<TReturned, TCreated>());
        auto &gs = GetStorage<ReturntdNorm>();
        if (!gs.contains(name.data())) { // TODO: make find
            auto u =
                std::unique_ptr<ReturntdNorm, std::function<void(ReturntdNorm *)>>(
                    NewObject<TCreated>(),
                    [](ReturntdNorm *f) { /*f->ConditionalBeginDestroy();*/ }
                );
            u->name = name;
            ReturntdNorm *uptr = u.get();
            UMainGameInstance::GetMainGameInstance()->mDBStorage.Add(uptr);
            gs.insert(std::make_pair(name, std::move(u)));
            return uptr;
        } else {
            return gs.find(name.data())->second.get();
        }

        // std::cout << typeid(TCreated).name() << " with name " << name << " is
        // already exists" << std::endl;
        return nullptr;
    }

    template <typename TReturned> static void Clear() {
        GetStorage<TReturned>().clear();
    }

    template <typename TReturned>
    static TReturned *Register(std::string_view name) {
        auto &gs = GetStorage<TReturned>();
        if (!gs.contains(name.data())) {
            auto u =
                std::unique_ptr<TReturned, std::function<void(TReturned *)>>(
                    NewObject<TReturned>(),
                    [](TReturned *f) { /*f->ConditionalBeginDestroy();*/ }
                );
            u->name = name;
            TReturned *uptr = u.get();
            UMainGameInstance::GetMainGameInstance()->mDBStorage.Add(uptr);
            gs.insert(std::make_pair(name, std::move(u)));
            LOG(TRACE) << "Registering " << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName()) << " with name " << name;
            return uptr;
        } else {
            LOG(TRACE) << "Appending " << TCHAR_TO_UTF8(*TReturned::StaticClass()->GetName()) << " with name " << name;
            return gs.find(name.data())->second.get();
        }

        // std::cout << typeid(TReturned).name() << " with name " << name << "
        // is already exists" << std::endl;
        return nullptr;
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
    static const _TReturned *Find(std::string_view name) {
        using ReturntdNorm = typename std::remove_cv<_TReturned>::type;
        auto &storage = GetStorage<ReturntdNorm>();

        auto res = storage.find(std::string(name));
        if (res != storage.end()) {
            return reinterpret_cast<ReturntdNorm *>(res->second.get());
        }

        // std::cout << typeid(_TReturned).name() << " " << name << " not found"
        // << std::endl;
        return nullptr;
    }

    template <typename _TReturned> static const auto &ObjectIterator() {
        return GetStorage<_TReturned>();
    }

    static std::vector<std::pair<void *, std::function<void(void *)>>> mProtos;
    static void
    StoreProtoPtr(void *proto, std::function<void(void *)> deallocator) {
        mProtos.push_back(std::make_pair(proto, deallocator));
    }

    static void FreeProtos() {
        for (auto p : mProtos) {
            p.second(p.first);
        }

        ensure(mProtos.empty());
    }

    static std::unordered_map<std::string, LocalizationTable> mLocTablesSource;
    static std::unordered_map<std::string, LocalizationTable> mLocTables;

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
            base = DB::Find<_TReturned>(stored);
            stored.clear();
            stored.shrink_to_fit();
        }

        return base;
    }

    operator bool() const {
        if (stored.size()) {
            base = DB::Find<_TReturned>(stored);
            stored.clear();
            stored.shrink_to_fit();
        }

        return !!base;
    }

    mutable const _TReturned *base = nullptr;
    mutable std::string stored;
};
} // namespace evo