#include "src/src.h"


//std::string getMsg(){
//    DcfFunctionProcessCommandProto dcfFunctionProcessCommandProto{"DZT_1", Cmd::Start};
//    MessageBox m2;
//    m2.payload = Serialization<DcfFunctionProcessCommandProto>::toJson(dcfFunctionProcessCommandProto);
//    m2.eventType = "ngair.proto.dcf.DcfFunctionProcessCommandProto";
//    return Serialization<MessageBox>::toJson(m2);
//}

void createClient(int number){
    std::thread([number](){
        DcfFunctionProcessCommandProto dcfFunctionProcessCommandProto{"DZT_"+std::to_string(number), Cmd::Start};
        MessageBox m2;
        m2.payload = Serialization<DcfFunctionProcessCommandProto>::toJson(dcfFunctionProcessCommandProto);
        m2.eventType = "ngair.proto.dcf.DcfFunctionProcessCommandProto";
        std::string payload = Serialization<MessageBox>::toJson(m2);

        TcpClient tcpClient("127.0.0.1", 4001);
        tcpClient.connectToServer();

        while (1){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            tcpClient.sendMessage(payload);
        }
    }).detach();
}


int main() {

    TcpServer tcpServer("127.0.0.1", 4001);

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

    createClient(1);
    createClient(2);
    createClient(3);
    createClient(4);
    createClient(5);
    createClient(6);
    createClient(7);
    createClient(8);
    createClient(9);
    createClient(10);
    createClient(11);
    createClient(12);
    createClient(13);
    createClient(14);
    createClient(15);
    createClient(16);
    createClient(17);
    createClient(18);
    createClient(19);
    createClient(20);


    while (1){
        sleep(1);
    }
    return 0;
}