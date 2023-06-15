#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

void put_matrix(uint16_t matrix[5]) {
    char buffer[] = "python gen_matrix.py "
                       "xxxxxxxxx "
                       "xxxxxxxxx "
                       "xxxxxxxxx "
                       "xxxxxxxxx "
                       "xxxxxxxxx "
                       "out.svg; pkill -HUP mupdf";
    int ind = 21;

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 9; x++) {
            bool bit = (matrix[y] >> (8-x)) & 1;
            if (bit)
                buffer[ind++] = '1';
            else
                buffer[ind++] = '0';
        }
        buffer[ind++] = ' ';
    }

    printf("%s\n", buffer);
    system("pkill -HUP mupdf");
    system(buffer);
}

void hardware_init() {
}

void delay_ms(double ms) {
    usleep((uint64_t)(ms * 1000));
}


