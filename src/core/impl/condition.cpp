#include "core/impl/condition.hpp"

#include "core/tedilang_utils.hpp"

#include "variables.hpp"

#include <iostream>
#include <string>

std::string condition_chars = "><=";

bool condition( std::string instruction ) {
    size_t condition_startPos = instruction.find_first_of(condition_chars);
    size_t conditionLength;
    if (condition_startPos == std::string::npos) {
        return 0;
    }
    if ( condition_chars.find( instruction.substr(condition_startPos)[1] ) != std::string::npos ) {
        conditionLength = 2;
    } else {
        conditionLength = 1;
    }
    size_t condition_endPos = instruction.find_last_of(condition_chars);

    size_t second_endPos = instruction.length();

    std::string firstStr      = instruction.substr(0, condition_startPos);
    std::string secondStr     = instruction.substr(condition_endPos + 1, second_endPos);

    int first;
    int second;

    if ( Variables::instance().isDeclaredVariable(firstStr) ) {
        first                 = Variables::instance().getInt(firstStr);
    } else {
        first                 = stoi( firstStr );
    }

    if ( Variables::instance().isDeclaredVariable(secondStr) ) {
        second                = Variables::instance().getInt(secondStr);
    } else {
        second                = stoi( secondStr );
    }

    std::string op = instruction.substr( condition_startPos, conditionLength );
    
    int result = 0;

    if          (op == "<") return first < second;
    else if     (op == ">") return first > second;
    else if     (op == "==") return first == second;
    else if     (op == ">=") return first >= second;
    else if     (op == "<=") return first <= second;
    else        tedilang_exception("Invalid operator");

    if ( second_endPos != instruction.length() ) {
        std::string instructionAfter = std::to_string( result ) + instruction.substr(second_endPos);
    
        result = condition( instructionAfter );
    }

    return result;
}

bool get_condition(std::string instruction) {
    instruction.erase(remove(instruction.begin(), instruction.end(), ' '), instruction.end());
    
    bool final = false;

    final = condition( instruction );

    return final;
}