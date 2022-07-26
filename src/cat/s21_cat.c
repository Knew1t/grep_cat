#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 4096
#define B_FLAG 0b1
#define E_FLAG 0b10
#define N_FLAG 0b100
#define T_FLAG 0b1000
#define S_FLAG 0b10000
#define V_FLAG 0b100000
#define NEW_LINE_FLAG 0b1000000
#define STOP_FLAG 0b10000000
// char  = 1 bytes, 8 bits
unsigned char parse_argument(char *argv);
unsigned char get_flags(const char *argv);
unsigned char get_gnu_flags(const char *argv);
void file_processing(FILE *opened_file_stream, char flags);
void vt_flags_processing(char flags, unsigned int c);

int main(int argc, char *argv[]) {
    unsigned char flags = 0;
    for (int i = 1; i < argc; i++) {
        if (flags != 255) {
            FILE *opened_file_stream;
            if ((opened_file_stream = fopen(argv[i], "r"))) {  // is_file?
                file_processing(opened_file_stream, flags);
                fclose(opened_file_stream);
                flags |= STOP_FLAG;
            } else if (!(flags & STOP_FLAG)) {
                flags = flags | parse_argument(argv[i]);
            }
        } else {
            printf("error\n");
            break;
        }
    }
    return 0;
}

void file_processing(FILE *opened_file_stream, char flags) {
    int c;
    long long line_num = 1;
    static short empty_line_counter = 0;
    flags |= NEW_LINE_FLAG;
    while ((c = getc(opened_file_stream)) != EOF) {
        if ((flags & B_FLAG) && (flags & NEW_LINE_FLAG) && (c != '\n'))
            printf("%6lld\t", line_num++);
        if ((flags & N_FLAG) && !(flags & B_FLAG) && (flags & NEW_LINE_FLAG)) {
            if ((flags & S_FLAG) && (empty_line_counter > 1)) {
            } else {
                printf("%6lld\t", line_num++);
            }
        }
        if (c == '\n') {
            if (flags & E_FLAG && !(flags & S_FLAG))
                printf("$");
            else if (flags & E_FLAG && flags & S_FLAG && empty_line_counter < 1)
                printf("$");
            if (flags & NEW_LINE_FLAG)
                empty_line_counter++;
            flags |= NEW_LINE_FLAG;
        } else {
            flags &= ~NEW_LINE_FLAG;
            empty_line_counter = 0;
        }
        if ((flags & S_FLAG) && (empty_line_counter > 1) && (c == '\n')) {
        } else if ((flags & V_FLAG) || (flags & T_FLAG)) {
            vt_flags_processing(flags, c);
        } else {
            putchar(c);
        }
    }
}

void vt_flags_processing(char flags, unsigned int c) {
    char *nonprint_array[65] = {
        "^@",   "^A",   "^B",   "^C",   "^D",   "^E",   "^F",   "^G",    "^H",
        "^I",   "\n",   "^K",   "^L",   "^M",   "^N",   "^O",   "^P",    "^Q",
        "^R",   "^S",   "^T",   "^U",   "^V",   "^W",   "^X",   "^Y",    "^Z",
        "^[",   "^\\",  "^]",   "^^",   "^_",   "^?",   "M-^@", "M-^A",  "M-^B",
        "M-^C", "M-^D", "M-^E", "M-^F", "M-^G", "M-^H", "M-^I", "M-^J",  "M-^K",
        "M-^L", "M-^M", "M-^N", "M-^O", "M-^P", "M-^Q", "M-^R", "M-^S",  "M-^T",
        "M-^U", "M-^V", "M-^W", "M-^X", "M-^Y", "M-^Z", "M-^[", "M-^\\", "M-^]",
        "M-^^", "M-^_"};
    if (flags & T_FLAG && flags & V_FLAG) {
        if ((c != 10 && c <= 31) || (c >= 127 && c <= 159)) {
            if (c < 127) {
                printf("%s", nonprint_array[(int)c]);
            } else {
                printf("%s", nonprint_array[(int)(c - 95)]);
            }
        } else {
            putchar(c);
        }
    } else if (flags & T_FLAG) {
        if (c == 9)  // 9 = '\t'
            printf("%s", nonprint_array[(int)c]);
        else
            putchar(c);
    } else if (flags & V_FLAG) {
        if (((c < 9) || (c > 9 && c <= 31) || (c >= 127 && c <= 159)) &&
            c != 10) {
            if (c < 127) {
                printf("%s", nonprint_array[(int)c]);
            } else {
                printf("%s", nonprint_array[(int)(c - 95)]);
            }
        } else {
            putchar(c);
        }
    }
}

unsigned char parse_argument(char *argv) {
    unsigned char result = 0;
    if (strspn((argv), "-") == 1 && *(argv + 1) != '\0') {
        char all_flags[] = "bentsTEv";
        if (strspn(argv + 1, all_flags) == strlen(argv + 1)) {
            result = get_flags(argv + 1);
        } else {
            result = 255;
        }
    } else if (strspn((argv), "-") == 2) {
        result = get_gnu_flags(argv);
    } else {
        result = 255;
    }
    return result;
}

unsigned char get_flags(const char *argv) {
    unsigned char result = 0;
    for (int i = 0; argv[i] != '\0'; i++) {
        if (argv[i] == 'b') {
            result |= B_FLAG;
        } else if (argv[i] == 'e') {
            result |= E_FLAG | V_FLAG;
        } else if (argv[i] == 'n') {
            result |= N_FLAG;
        } else if (argv[i] == 't') {
            result |= T_FLAG | V_FLAG;
        } else if (argv[i] == 's') {
            result |= S_FLAG;
        } else if (argv[i] == 'T') {
            result |= T_FLAG;
        } else if (argv[i] == 'E') {
            result |= E_FLAG;
        } else if (argv[i] == 'v') {
            result |= V_FLAG;
        }
    }
    return result;
}

unsigned char get_gnu_flags(const char *argv) {
    unsigned char result = 0;
    if (!strcmp(argv, "--number-nonblank")) {
        result |= B_FLAG;
    } else if (!strcmp(argv, "--number")) {
        result |= N_FLAG;
    } else if (!strcmp(argv, "--squeeze-blank")) {
        result = result | S_FLAG;
    } else {
        result = 255;
    }
    return result;
}
