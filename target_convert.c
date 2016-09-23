/* Public Domain */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void usage(char *prog) {
    fprintf(stderr,
            "%s -e|-d < infile > outfile\n"
            "\n"
            "-d    decode (t3000 -> t3001)\n"
            "-e    encode (t3001 -> t3000)\n",
            prog);
    exit(1);
}

int main (int argc, char **argv)
{
    if (argc != 2 || argv[1][0] != '-' || argv[1][2] != '\0' || (argv[1][1] != 'd' && argv[1][1] != 'e'))
        usage(argv[0]);

    bool encode = argv[1][1] == 'e';

    uint8_t p = 18;
    int i;
    while ((i = getchar()) != EOF) {
        uint8_t c = i;
        if (encode)
            c = ((c << 5 | c >> 3) - p) ^ 0xCC;
        else {
            c = p + (c ^ 0xCC);
            c = c << 3 | c >> 5;
        }
        putchar(c);
        p++;
    }
    return 0;
}
