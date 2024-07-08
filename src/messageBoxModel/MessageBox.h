//
// Created by stepan on 21.06.2024.
//

#ifndef TCP_MESSAGEBOX_H
#define TCP_MESSAGEBOX_H

#include "../utils/Serialization.h"

struct MessageBox{
    std::string payload;
    std::string eventType;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MessageBox, payload, eventType);
};

#endif //TCP_MESSAGEBOX_H
