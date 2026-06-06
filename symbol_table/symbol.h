#pragma once
#include <string>
#include <variant>
/*
 * KEY ELEMENT 2 - ENUM OF SUPPORTED PRIMITIVE DATA TYPES
 
 * This enum class enumerates the primitive data types that the symbol table 
 * is allowed to hold. Each enumerator maps one-to-one to a primitive type, 
 * so every variable's type is tracked with a compact, type-safe, and 
 * self-documenting tag. Furthermore, using an enum class instead of a 
 * plain enum keeps the names scoped under PrimitiveDataTypes and
 * prevents accidental implicit conversion to int.
 */
enum class PrimitiveDataTypes {
    TYPE_CHAR,                  // char
    TYPE_SHORT,                 // short int
    TYPE_INT,                   // int
    TYPE_LONG,                  // long int
    TYPE_FLOAT,                 // float
    TYPE_DOUBLE,                // double
};

/*
 * KEY ELEMENT 1 - STORING N PRIMITIVE DATA TYPES (the Symbol record)
 
 * A Symbol is a struct representing one entry in the symbol table. It contains
 * the declared PrimitiveDataTypes tag and the actual value; the variable's name
 * is not stored here but serves as the identifier, i.e. the table's map key. The
 * value is a std::variant over the supported C primitives, which acts like a type-safe
 * union: at any moment it holds exactly one of the listed types and remembers
 * which one. This is how a single symbol table can store N different primitive
 * data types at once without losing type information. A struct is used because a
 * Symbol is a plain aggregate of public data with no invariants to enforce.
 */
struct Symbol {
    using ValueType = std::variant<
        char,
        short,
        int,
        long,
        float,
        double
    >;

    PrimitiveDataTypes type;     // declared primitive type
    ValueType value;             // current value (one of the N primitives)
};
