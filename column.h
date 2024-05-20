#ifndef COLUMN_H
#define COLUMN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REALOC_SIZE 256

enum enum_type {
    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING
};
typedef enum enum_type ENUM_TYPE;

union column_type {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
};
typedef union column_type COL_TYPE;

struct COLUMN {
    char *titre;
    unsigned int size;
    unsigned int max_size;
    ENUM_TYPE column_type;
    COL_TYPE **data;
};
typedef struct COLUMN COLUMN;
COLUMN *create_column(ENUM_TYPE type, char *col_titre);

void print_col(COLUMN* col);
void delete_column(COLUMN **col);
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
int insert_value(COLUMN *col, void *value);
void print_limite_col_lig(COLUMN *col, int limite);

#endif // COLUMN_H
