// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once

#include "ThirdParty/lua/lua.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <utility>

namespace evo {
template <class IdType, class Base, class Comparator> class TemplateFactory {
  public:
    using IdTypeUsing = IdType;

    // Register lua class in lua state
    using RegisterFunc = std::function<void(lua_State *)>;

    using BaseFuncTuple = std::tuple<RegisterFunc, RegisterFunc>;

    using FactoryBaseMap = std::map<IdType, BaseFuncTuple, Comparator>;

    BaseFuncTuple GetBaseTuple(const IdType &id) {
        auto it = base_map_.find(id);
        if (it != base_map_.end())
            return it->second;

        return {};
    }

    void register_lua(lua_State *state) const {
        for (const auto &[key, value] : base_map_) {
            LOG(TRACE) << "Register class " << key;
            std::get<1>(value)(state);
        }
        for (const auto &[key, value] : base_map_) {
            std::get<0>(value)(state);
        }
    }

    void add_base(
        const IdType &id, RegisterFunc reg, RegisterFunc pre_reg, std::string_view comment = ""
    ) {
        auto i = base_map_.find(id);
        if (i == base_map_.end()) {
            base_map_.insert(std::make_pair(id, std::make_tuple(reg, pre_reg)));
        } else {
            std::cout << id << "base redefinition!" << std::endl;
            i->second = std::make_tuple(reg, pre_reg);
        }
    }

    FactoryBaseMap base_map_;
};

template <class T> class RegisterBase {
  public:
    template <class Factory>
    RegisterBase(Factory &factory, const typename Factory::IdTypeUsing &id) {
        factory.add_base(id, T::GetRegisterLambda(), T::GetPreRegisterLambda());
    }
};

#define EVO_REGISTER_BASE_IMPL(type, factory, id)                              \
    namespace {                                                                \
    evo::RegisterBase<type> RegisterBase##type(factory, id);                   \
    }
} // namespace evo