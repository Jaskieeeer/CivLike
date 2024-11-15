#ifndef CELL_H
#define CELL_H

struct Cell {
    enum class Type {
        EMPTY,
        TOWN,
        UNIT
    };

    Type type;
    int id;

    Cell() : type(Type::EMPTY), id(0) {}
};

#endif // CELL_H