#include <stdint.h>

typedef struct {
    int width;
    const uint8_t bitmap[5];
} font_character_t;

int put_character(font_character_t character, int x_coord, uint16_t matrix[5]);
int put_string(char* string, int x_coord, font_character_t font[127], uint16_t matrix[5]);

extern const font_character_t character_infinity[2];
extern const font_character_t wide_font[127];
extern const font_character_t narrow_font[127];

