// Copyright (c) 2017 - 2022, Samsonov Andrey. All Rights Reserved.
#pragma once
#include "abstract_error.h"

#include <string>

struct FileNotFoundError : AbstractError {
    std::string name;
    FileNotFoundError(std::string n) : name(std::move(n)) {}
    FileNotFoundError() {}

    virtual auto to_string() noexcept -> std::string override {
        return "File " + name + " not found";
    }
};

struct ObjectHasNoName : AbstractError {
    int32 ind;
    ObjectHasNoName(int32 n) : ind(n) {}

    virtual auto to_string() noexcept -> std::string override {
        return "Object with index" + std::to_string(ind) + " has no name";
    }
};

struct ObjectHasNoClassError : AbstractError {

    std::string name;
    ObjectHasNoClassError(std::string n) : name(std::move(n)) {}

    virtual auto to_string() noexcept -> std::string override {
        return "Object " + name + " has no class";
    }
};

struct ObjectIsNotDeserializedError : AbstractError {

    std::string name;
    ObjectIsNotDeserializedError(std::string n) : name(std::move(n)) {}

    virtual auto to_string() noexcept -> std::string override {
        return "Object " + name + " is not deserialized";
    }
};

struct BrokenJsonError : AbstractError {

    BrokenJsonError() {}

    virtual auto to_string() noexcept -> std::string override {
        return "json is broken";
    }
};

struct JsonTryToFindNotExistingObjectError : AbstractError {

    std::string name;
    std::string value;
    JsonTryToFindNotExistingObjectError(
        std::string field, std::string field_value
    )
        : name(std::move(field)), value(std::move(field_value)) {}

    virtual auto to_string() noexcept -> std::string override {
        return "Json with field " + name + " trying to find \"" + value +
               "\" " + " that not exists";
    }
};

struct ClassNotFoundError : AbstractError {

    std::string name;
    std::string class_name;
    ClassNotFoundError(std::string n, std::string cn)
        : name(std::move(n)), class_name(std::move(cn)) {}

    virtual auto to_string() noexcept -> std::string override {
        return "Object " + name + " is trying to load class " + class_name +
               " that not existing";
    }
};