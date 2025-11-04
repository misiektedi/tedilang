#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <array>
#include <algorithm>
#include <cstring>
#include <variant>
#include <ranges>
#include <cctype>

#include "core/calc.h"

using namespace std;

class Value {
public:
    enum class Type { INT, DOUBLE, STRING, BOOL };

private:
    Type type;
    variant<int, double, string, bool> data;

public:
    Value(int v) : type(Type::INT), data(v) {}
    Value(double v) : type(Type::DOUBLE), data(v) {}
    Value(const string& v) : type(Type::STRING), data(v) {}
    Value(bool v) : type(Type::BOOL), data(v) {}
    Value() : type(Type::INT), data(0) {}

    Type getType() const { return type; }

    int asInt() const { return get<int>(data); }
    double asDouble() const { return get<double>(data); }
    const string& asString() const { return get<string>(data); }
    bool asBool() const { return get<bool>(data); }
};

unordered_map<string, Value> variables;

bool check_function(string line, string function_name) {
    if ( line.starts_with(function_name + "(") && line.ends_with(")") ) return true;

    return false;
}

string function_content(string line, int name_length) {
    return line.substr(name_length + 1, line.length() - name_length - 2 );
}

string remove_qm(string text) {
    return text.substr(1, text.length() - 2 );
}

void interpreter(string line) {

    if ( check_function(line, "output") ) {

        string content = function_content(line, 6);

        if ( content.starts_with('"') && content.ends_with('"') ) {
            cout << content.substr(1, content.length() - 2 ) << endl;
        } 
        else
        {

            string type = content.substr( 0, content.find('@') );
            string varName = content.substr( content.find('@') + 1 );
            
            if ( type == "int" )            cout << variables[varName].asInt() << endl;
            else if ( type == "string" )    cout << variables[varName].asString() << endl;
            else cerr << "[ERROR] Nothing to output." << endl;

        }

    }

    if ( check_function(line, "shell") ) {

        string content = function_content(line, 5);

        if ( content.starts_with('"') && content.ends_with('"') ) {
            string content01 = content.substr(1, content.length() - 2 );
            const char* contentChar = content01.data();

            int result = system(contentChar);

            cout << result << endl;
        }
    }

    if ( line.starts_with("let") ) {
        array<string, 2> types = {"int", "string"};

        string lineStriped = line.substr(4);

        string type = lineStriped.substr(0, 0 + lineStriped.find(' ') );

        string content = lineStriped.substr(1 + type.length());

        size_t pos = content.find('=');

        string key = content.substr(0, -1 + pos);
        string value = content.substr(pos + 2);
        
        if ( type == "int" ) {
            variables[key] = Value( calc(value) );
        } else if ( type == "string" ) {
            variables[key] = Value( remove_qm(value) );
        }
    }

    if ( check_function(line, "wait") ) {

        string content = function_content(line, 4);

        int contentInt = stoi(content);

        this_thread::sleep_for(chrono::seconds(contentInt));

    }

    if ( line.starts_with("exit") ) {
        exit(0);
    }

}

int main( int argc, char* argv[] ) {
    ifstream file( argv[1] );

    if (!file.is_open()) {
        cerr << "File not exist." << endl;
        return 1;
    }

    string line;
    bool main = false;

    while ( getline(file, line, ';') ) {

        if ( line.starts_with("#") ) continue;

        if ( line.starts_with("main {") ) {
            main = true;
            line = line.substr(6);
        }

        if ( main == false ) continue;


        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        
        auto view = line
            | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
            | std::views::reverse
            | std::views::drop_while([](unsigned char ch){ return std::isspace(ch); })
            | std::views::reverse;

        string line(view.begin(), view.end());



        interpreter( line );

    }

    file.close();
    return 0;
}