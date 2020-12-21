#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <string>
#include <vector>
#include <regex>

class CPU
{
public:
    struct Instruction {
        std::string op;
        int arg;
    };

    CPU();
    ~CPU();

    void AddInstruction(const std::string& instruction);
    bool Run();
    bool Step();
    bool RunTo(__int64 where);

    __int64 GetAcc() { return m_acc; }
    __int64 GetIP() { return m_ip; }

    std::string DumpState();
    std::string DumpInstruction();
    std::string DumpInstruction(__int64 ip);

    std::string GetOp(__int64 ip);
    void SetOp(__int64 ip, std::string op);
    __int64 GetIntSize() { return m_instructions.size(); }

private:
    void DoNOP(__int64 arg);
    void DoACC(__int64 arg);
    void DoJMP(__int64 arg);

    __int64 m_acc;
    __int64 m_ip;

    std::vector<Instruction> m_instructions;
};


std::vector<std::string> split(const std::string& input, const std::string& regex) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
        first{ input.begin(), input.end(), re, -1 },
        last;
    return { first, last };
}