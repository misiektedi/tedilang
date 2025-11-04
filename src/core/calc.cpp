#include "core/calc.h"

#include <iostream>
#include <string>

std::string chars = "+-*/";
std::string numbers = "0123456789";

int interpret(int final, std::string instruction, int offset) {
    size_t instruction_length = instruction.length();

    //std::string instruction_striped = instruction.substr(offset);

    size_t operation_pos = instruction.find_first_of(chars, offset);
    if (operation_pos == std::string::npos) {
        return final;
    }

    size_t next_number_pos = instruction.find_first_of(numbers, operation_pos + 1);
    if (next_number_pos == std::string::npos) {
        return final;
    }

    final = stoi( instruction.substr(offset, operation_pos - offset) );

    int next_number = stoi( instruction.substr(next_number_pos, instruction.find_first_of(' ', offset)) );

    char op = instruction[offset + operation_pos];
    
    if ( op == '+' ) final = final + next_number;

    if ( offset < instruction_length ) {
        final = interpret(final, instruction, next_number_pos);
    }

    std::cout << "---" << std::endl << final << std::endl << instruction << std::endl << next_number_pos << std::endl << instruction_length << std::endl << offset << std::endl << next_number << std::endl << "---" << std::endl;

    return final;
}

int calc(std::string instruction) {
    instruction.erase(remove(instruction.begin(), instruction.end(), ' '), instruction.end());
    
    int instruction_length = instruction.length();
    int final = 0;

    final = interpret(final, instruction, 0);

    return final;
}