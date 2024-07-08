//
// Created by user on 11.01.2024.
//




#ifndef TRANSPORTPROTOCOLSCPP_SERIALIZATION_H
#define TRANSPORTPROTOCOLSCPP_SERIALIZATION_H

#include "libs/json/single_include/nlohmann/json.hpp"

using nlohmann::json;
template<class T>
class Serialization{
public:

    static std::string toJson(T& value) {
        json j = value;
        return j.dump();
    }

    static bool fromJson(const std::string& s, T& value) {
        if (s.empty()) {
        }
        using nlohmann::from_json;

        try
        {
            json j = json::parse(s);
            from_json(j, value);
            return true;
        }
        catch (const std::exception& ex)
        {
            return false;
        }
    }
};

#endif //TRANSPORTPROTOCOLSCPP_SERIALIZATION_H
