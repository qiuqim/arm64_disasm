#include <iostream>
#include <vector>
#include <unistd.h>
#include <sstream>

#include "disasm.h"


disasm disasm_;
int main() {
    std::vector<uint32_t> code;
    unsigned int shellcode[]={0xF81E0FF3,0xA9017BFD,
                              0x910043FD,0x90000013,0x91010273,0xF8400673,0x14000002,
                              0xB9000E7F,0x320003E0,0xD503201F,0xB9400E68,0x34FFFFA8,
                              0xF9401660,0xB4FFFF40,0xA9418668,0x2D400660,0xBD400A62,
                              0x2A1F03E2,0xD63F0100,0x12000008,0xB9001268,0x17FFFFF2};

    for(int i=0;i<sizeof(shellcode)/sizeof(shellcode[0]);i++){
        code.push_back(shellcode[i]);
    }

    disasm_.disasm_code(0x7b00000000,code);


    return 0;
}
