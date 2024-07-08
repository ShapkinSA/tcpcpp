#include "src/src.h"
#include <set>

int main(){

    DcfSupervisorStatusProto dcfSupervisorStatusProto;

    std::set<std::string> funcs;
    funcs.insert("DZT_1");
    funcs.insert("MTZ_2");
    funcs.insert("VV_1");
    funcs.insert("KL_2");


    std::set<std::string> svs;
    funcs.insert("01:0C:CD:04:02:12");
    funcs.insert("01:0C:CD:04:00:12");
    funcs.insert("01:0C:CD:04:02:1");
    funcs.insert("01:0C:CD:04:00:11");


    std::set<std::string> gooses;
    funcs.insert("01:0C:CD:05:00:22");
    funcs.insert("01:0C:CD:05:02:22");
    funcs.insert("01:0C:CD:05:00:32");
    funcs.insert("01:0C:CD:05:02:32");


    dcfSupervisorStatusProto.functions = funcs;
    dcfSupervisorStatusProto.svs = svs;
    dcfSupervisorStatusProto.gooses = gooses;

    printf("%s", dcfSupervisorStatusProto.toString().c_str());

    return 0;
}