#include "src/src.h"

int main(){

    std::set<std::string> functions;
    functions.insert("DZT_1");
    functions.insert("MTZ_2");
    functions.insert("VV_1");
    functions.insert("KL_2");


    std::set<std::string> svs;
    svs.insert("01:0C:CD:04:02:12");
    svs.insert("01:0C:CD:04:00:12");
    svs.insert("01:0C:CD:04:02:1");
    svs.insert("01:0C:CD:04:00:11");


    std::set<std::string> gooses;
    gooses.insert("01:0C:CD:05:00:22");
    gooses.insert("01:0C:CD:05:02:22");
    gooses.insert("01:0C:CD:05:00:32");
    gooses.insert("01:0C:CD:05:02:32");

    DcfSupervisorStatusProto dcfSupervisorStatusProto{functions, svs, gooses};
    DcfFunctionProcessCommandProto dcfFunctionProcessCommandProto{"DZT_1", Cmd::Start};
    DcfSupervisorErrorDescriptionProto dcfSupervisorErrorDescriptionProto{"DZT_1",ErrorType::SvError};


    MessageBox m1;
    m1.payload = Serialization<DcfSupervisorStatusProto>::toJson(dcfSupervisorStatusProto);
    m1.eventType = "ngair.proto.dcf.DcfSupervisorStatusProto";
    auto msg1 = Serialization<MessageBox>::toJson(m1);

    MessageBox m2;
    m2.payload = Serialization<DcfFunctionProcessCommandProto>::toJson(dcfFunctionProcessCommandProto);
    m2.eventType = "ngair.proto.dcf.DcfFunctionProcessCommandProto";
    auto msg2 = Serialization<MessageBox>::toJson(m2);

    MessageBox m3;
    m3.payload = Serialization<DcfSupervisorErrorDescriptionProto>::toJson(dcfSupervisorErrorDescriptionProto);
    m3.eventType = "ngair.proto.dcf.DcfSupervisorErrorDescriptionProto";
    auto msg3 = Serialization<MessageBox>::toJson(m3);


    TcpClient tcpClient("127.0.0.1", 4001);
//    TcpClient tcpClient("192.168.0.106", 4001);
    tcpClient.connectToServer();


    std::thread([&](){
        while (1){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            tcpClient.sendMessage(msg1);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            tcpClient.sendMessage(msg2);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            tcpClient.sendMessage(msg3);
        }
    }).join();

    return 0;
}