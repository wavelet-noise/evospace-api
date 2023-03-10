#pragma once

#include <string>

struct KeyTable {
    std::string key = "";
    std::string table = "";
    float param = 0;
    bool has_param = false;

    static KeyTable create(std::string_view k, std::string_view t) {
        auto kt = KeyTable();
        kt.key = k;
        kt.table = t;

        return kt;
    }

    static KeyTable new_param(std::string_view k, std::string_view t, float p) {
        auto kt = KeyTable();
        kt.key = k;
        kt.table = t;
        kt.param = p;
        kt.has_param = true;

        return kt;
    }
};