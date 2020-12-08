// shared.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "shared.h"
#include <sstream>
#include <iostream>

using namespace std;

CPU::CPU() :
    m_acc(0),
    m_ip(0)
{

}

CPU::~CPU()
{

}

void CPU::AddInstruction(const std::string& instruction)
{
    Instruction in;
    in.op = instruction.substr(0, 3);
    in.arg = stoi(instruction.substr(4));
    m_instructions.push_back(in);
}

bool CPU::Run()
{
    while (!Step())
        ;

    return true;
}

bool CPU::Step()
{
    //cerr << DumpState() << endl;
    if (m_ip < 0 || m_ip >= m_instructions.size()) {
        return true;
    }

    Instruction current = m_instructions[m_ip];
    ++m_ip;
    
    if (current.op == "nop"s) DoNOP(current.arg);
    else if (current.op == "acc"s) DoACC(current.arg);
    else if (current.op == "jmp"s) DoJMP(current.arg);

    return false;
}

bool CPU::RunTo(__int64 where)
{
    do {
        if (m_ip == where) return false;
    } while (Step());

    return true;
}

std::string CPU::DumpState()
{
    stringstream ss;
    ss << "@" << m_ip << ": " << m_instructions[m_ip].op << " " << m_instructions[m_ip].arg << " ; ACC = " << m_acc;
    return ss.str();
}

std::string CPU::DumpInstruction()
{
    return DumpInstruction(m_ip);
}

std::string CPU::DumpInstruction(__int64 ip)
{
    stringstream ss;
    ss << m_instructions[ip].op << " " << m_instructions[ip].arg;
    return ss.str();
}

string CPU::GetOp(__int64 ip)
{
    return m_instructions[ip].op;
}

void CPU::SetOp(__int64 ip, string op)
{
    m_instructions[ip].op = op;
}

void CPU::DoNOP(__int64 arg)
{
}

void CPU::DoACC(__int64 arg)
{
    m_acc += arg;
}

void CPU::DoJMP(__int64 arg)
{
    // Have to decrement because we've already moved on
    m_ip = (m_ip - 1) + arg;
}
