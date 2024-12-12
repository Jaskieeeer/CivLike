#ifndef CELL_H
#define CELL_H

struct Cell {
    enum class Type {
        EMPTY,
        TOWN,
        SETTLER,
        WARRIOR
    };

    Type type;
    int id;
    int playerId;

    Cell() : type(Type::EMPTY), id(0),playerId(0) {}
};

#endif // CELL_H