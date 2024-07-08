//
// Created by stepan on 04.07.2024.
//

#ifndef TCP_DCFFUNCTIONPROCESSCOMMANDPROTO_H
#define TCP_DCFFUNCTIONPROCESSCOMMANDPROTO_H

#include "../utils/Serialization.h"
#include <string>
#include <utility>

enum Cmd {Start, Stop};

struct DcfFunctionProcessCommandProto{

    DcfFunctionProcessCommandProto() = default;

    DcfFunctionProcessCommandProto(std::string functionName, Cmd cmd) : functionName(std::move(functionName)), cmd(cmd) {}

    std::string functionName;
    Cmd cmd = Start;

    [[nodiscard]] std::string toString() const {
        return "functionName : " + functionName + ", " + "cmd :" + std::to_string(cmd);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DcfFunctionProcessCommandProto, functionName, cmd);
};


NLOHMANN_JSON_SERIALIZE_ENUM(Cmd, {
    {Start, "Start"},
    {Stop, "Stop"},
})

#endif //TCP_DCFFUNCTIONPROCESSCOMMANDPROTO_H
