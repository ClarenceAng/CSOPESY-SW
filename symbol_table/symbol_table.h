#pragma once
#include <string>
#include <variant>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "symbol.h"

/*
 * KEY ELEMENT 3 - PUBLIC FUNCTIONS THAT STORE AND UPDATE VALUES

 * SymbolTable is the container that maps a variable name to its Symbol
 * record using an Dstd::unordered_map, giving an average O(1) of lookup, insertion,
 * and update by name. It exposes the two required public functions: "store()"
 * declares a brand-new variable, while "update()" changes the value of a variable
 * that already exists. "store()" is the entry point: it calls "parse()" to tokenize
 * and convert a declaration, then either inserts a brand-new entry or, if the name
 * already exists, delegates to "update()". Together these functions let callers
 * safely build up a table of typed variables, mirroring how an OS process tracks
 * the variables it owns.
 */
class SymbolTable {
    using String = std::string;
    using ValueType = Symbol::ValueType;

    private:
        // The map key is the variable's name
        std::unordered_map<String, Symbol> table;

    public:
        // Store a variable in the symbol table, parse the declaration, then either
        // update() an existing value or insert a new entry
        void store(const String& statement) {
            String name;
            PrimitiveDataTypes type;
            ValueType value;
            if (!parse(statement, name, type, value)) {
                return;
            }
            if (table.find(name) != table.end()) {
                update(name, value);   // already exists -> update its value
                return;
            }
            Symbol symbol;             // new declaration -> insert directly
            symbol.type = type;
            symbol.value = value;
            table[name] = symbol;
        }

        // Update the value of a variable in the symbol table
        void update(const String& name, ValueType value) {
            auto it = table.find(name);
            it->second.value = value;
        }

        // Tokenizes and converts a declaration into its name, type, and typed
        // value. Returns false on a statement that cannot be parsed.
        bool parse(const String& statement, String& name,
            PrimitiveDataTypes& type, ValueType& value) {
            std::istringstream iss(statement);
            String typeStr, eq, valueStr;
            iss >> typeStr >> name >> eq >> valueStr;

            if (eq != "=" || name.empty() || valueStr.empty()) {
                std::cout << "[parse] cannot parse statement: '" << statement << "'\n";
                return false;
            }

            if (typeStr == "char") {
                type = PrimitiveDataTypes::TYPE_CHAR;   value = static_cast<char>(valueStr[0]);
            } else if (typeStr == "short") {
                type = PrimitiveDataTypes::TYPE_SHORT;  value = static_cast<short>(std::stoi(valueStr));
            } else if (typeStr == "int") {
                type = PrimitiveDataTypes::TYPE_INT;    value = std::stoi(valueStr);
            } else if (typeStr == "long") {
                type = PrimitiveDataTypes::TYPE_LONG;   value = std::stol(valueStr);
            } else if (typeStr == "float") {
                type = PrimitiveDataTypes::TYPE_FLOAT;  value = std::stof(valueStr);
            } else if (typeStr == "double") {
                type = PrimitiveDataTypes::TYPE_DOUBLE; value = std::stod(valueStr);
            } else {
                std::cout << "[parse] unknown type: '" << typeStr << "'\n";
                return false;
            }
            return true;
        }
};
