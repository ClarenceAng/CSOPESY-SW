#include <memory>
#include <iostream>
#include "symbol_table.h"

/*
 * WHAT MAIN DOES

 * main() shows the symbol table being used in the two required ways. It hardcodes
 * the C declaration "int myCSOPESYGrade = 100" and feeds it to store(). First it
 * creates the table as a temporary stack variable and stores the statement
 * (store() internally calls parse() to tokenize/convert, then update() to set the
 * value). Second, it creates the table on the heap behind a std::unique_ptr, which
 * owns and automatically frees the table when it goes out of scope, and stores the
 * exact same statement through the pointer using `->`. The main program therefore
 * demonstrates storing into both an automatic (stack) and a smart-pointer (heap)
 * instance of the symbol table.
 */
int main() {
    const std::string declaration = "int myCSOPESYGrade = 100"; // hardcoded statement to parse

    std::cout << "A) Symbol table as a TEMPORARY (stack) variable\n";
    SymbolTable table;             // temporary stack instance
    table.store(declaration);      

    std::cout << "B) Symbol table as a std::unique_ptr\n";
    auto tablePtr = std::make_unique<SymbolTable>(); // heap instance owned by unique_ptr
    tablePtr->store(declaration);

    return 0;
}
