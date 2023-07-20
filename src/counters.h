#pragma once

enum value_type{VALUE_INT, VALUE_TIME_WHOLE_SECONDS, VALUE_TIME_FRACTIONAL_SECONDS};

void display_integer (int number);

int alter_integer(int min, int max, int direction, int value);

void alter_value(int *seconds_or_int, int *ms, int min, int max, enum value_type type, int direction);

#define UP 1
#define DOWN -1
#define INFINITY -1


