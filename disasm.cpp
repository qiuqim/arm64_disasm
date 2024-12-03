//
// Created  on 2024/7/22.
//

#include "disasm.h"



std::string disasm::disasm_code(uint64_t addr, std::vector<uint8_t>& code) {
    std::stringstream ss;
    cs_insn *insn;
    size_t count = cs_disasm(handle, code.data(), code.size(), addr, 0, &insn);
    if (count > 0) {
        for (size_t j = 0; j < count; j++) {
            //字节码
            std::cout << "字节码: " << std::endl;
            for (size_t i = 0; i < insn[j].size; i++) {
                std::cout << "0x" << std::hex << (int)insn[j].bytes[i] << " ";
            }
            std::cout << "\n地址 0x" << std::hex << insn[j].address << " 指令:\t" << insn[j].mnemonic << "\t" << insn[j].op_str
                      << std::endl;
            ss << "0x" << std::hex << insn[j].address << ":\t" << insn[j].mnemonic << "\t" << insn[j].op_str
                      << std::endl;
            if (insn[j].detail) {
                cs_detail *detail = insn[j].detail;
                if (detail->regs_read_count) {
                    std::cout << "\tRead:";
                    for (size_t k = 0; k < detail->regs_read_count; k++) {
                        std::cout << " " << cs_reg_name(handle, detail->regs_read[k]);
                    }
                    std::cout << std::endl;
                }
                if (detail->regs_write_count) {
                    std::cout << "\tWrite:";
                    for (size_t k = 0; k < detail->regs_write_count; k++) {
                        std::cout << " " << cs_reg_name(handle, detail->regs_write[k]);
                    }
                    std::cout << std::endl;
                }
            }
            cs_regs regs_read, regs_write;
            unsigned char regs_read_count , regs_write_count;
            if(!cs_regs_access(handle, insn, regs_read, &regs_read_count,
                           regs_write, &regs_write_count))
            {
                if (regs_read_count) {
                    printf("\tRegisters read:");
                    for(int i = 0; i < regs_read_count; i++) {
                        printf(" %s", cs_reg_name(handle, regs_read[i]));
                    }
                    printf("\n");
                }

                if (regs_write_count) {
                    printf("\tRegisters modified:");
                    for(int i = 0; i < regs_write_count; i++) {
                        printf(" %s", cs_reg_name(handle, regs_write[i]));
                    }
                    printf("\n");
                }
            }
        }
        cs_free(insn, count);
    } else {
        std::cout << "ERROR: Failed to disassemble given code!" << std::endl;
    }

    return ss.str();
}

std::string disasm::disasm_code(uint64_t addr, std::vector<uint32_t> &code) {
            std::vector<uint8_t> code_8(code.size() * 4);
            for (size_t i = 0; i < code.size(); i++) {
                code_8[i * 4] = code[i] & 0xff;
                code_8[i * 4 + 1] = (code[i] >> 8) & 0xff;
                code_8[i * 4 + 2] = (code[i] >> 16) & 0xff;
                code_8[i * 4 + 3] = (code[i] >> 24) & 0xff;
            }
            return disasm_code(addr, code_8);
}