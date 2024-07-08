#include "src/src.h"


int main() {

//    TcpServer tcpServer("192.168.0.108", 4001);
    TcpServer tcpServer("0.0.0.0", 4001);
//    TcpServer tcpServer("127.0.0.1", 4001);

    tcpServer.setHandler<DcfSupervisorStatusProto>("ngair.proto.dcf.DcfSupervisorStatusProto", [](const DcfSupervisorStatusProto &dcfSupervisorStatusProto) {
        printf("%s\n", dcfSupervisorStatusProto.toString().c_str());
    });

    tcpServer.setHandler<DcfFunctionProcessCommandProto>("ngair.proto.dcf.DcfFunctionProcessCommandProto", [](const DcfFunctionProcessCommandProto &dcfFunctionProcessCommandProto) {
        printf("%s\n", dcfFunctionProcessCommandProto.toString().c_str());
    });

    tcpServer.setHandler<DcfSupervisorErrorDescriptionProto>("ngair.proto.dcf.DcfSupervisorErrorDescriptionProto", [](const DcfSupervisorErrorDescriptionProto &dcfSupervisorErrorDescriptionProto) {
        printf("%s\n", dcfSupervisorErrorDescriptionProto.toString().c_str());
    });

    tcpServer.start();

    while (1){
        sleep(1);
    }
    return 0;
}