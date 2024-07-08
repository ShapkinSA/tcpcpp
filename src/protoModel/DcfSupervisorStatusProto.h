//
// Created by stepan on 04.07.2024.
//

#ifndef TCP_DCFSUPERVISORSTATUSPROTO_H
#define TCP_DCFSUPERVISORSTATUSPROTO_H

#include <string>
#include <set>
#include "../utils/Serialization.h"

struct DcfSupervisorStatusProto{

    DcfSupervisorStatusProto() = default;

    DcfSupervisorStatusProto(const std::set<std::string> &functions, const std::set<std::string> &svs,
                             const std::set<std::string> &gooses) : functions(functions), svs(svs), gooses(gooses) {}

    std::set<std::string> functions;
    std::set<std::string> svs;
    std::set<std::string> gooses;

    [[nodiscard]] std::string toString() const {
        std::string payload = "";
        for (const auto &fun: functions)
            payload += "functions: \"" + fun + "\"\n";

        for (const auto &sv: svs)
            payload += "svs: \"" + sv + "\"\n";

        for (const auto &goose: gooses)
            payload += "gooses: \"" + goose + "\"\n";
        return payload;
    }
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DcfSupervisorStatusProto, functions, svs, gooses);
};

#endif //TCP_DCFSUPERVISORSTATUSPROTO_H
