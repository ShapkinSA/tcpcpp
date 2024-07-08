//
// Created by stepan on 04.07.2024.
//

#ifndef TCP_DCFSUPERVISORERRORDESCRIPTIONPROTO_H
#define TCP_DCFSUPERVISORERRORDESCRIPTIONPROTO_H

#include <string>
#include <utility>
#include "../utils/Serialization.h"

enum ErrorType {InternalError, InternalErrorFixed, SvError, GooseError, ViedError, SvErrorFixed, GooseErrorFixed};

struct DcfSupervisorErrorDescriptionProto{

    DcfSupervisorErrorDescriptionProto() = default;

    DcfSupervisorErrorDescriptionProto(std::string data, ErrorType errorType) : data(std::move(data)),
                                                                                errorType(errorType) {}
    std::string data;
    ErrorType errorType = InternalError;
    [[nodiscard]] std::string toString() const {
        return "data : " + data + ", " + "errorType :" + std::to_string(errorType);
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DcfSupervisorErrorDescriptionProto, data, errorType);
};

NLOHMANN_JSON_SERIALIZE_ENUM(ErrorType, {
    {InternalError, "InternalError"},
    {InternalErrorFixed, "InternalErrorFixed"},
    {SvError, "SvError"},
    {GooseError, "GooseError"},
    {ViedError, "ViedError"},
    {SvErrorFixed, "SvErrorFixed"},
    {GooseErrorFixed, "GooseErrorFixed"}
})

#endif //TCP_DCFSUPERVISORERRORDESCRIPTIONPROTO_H
