#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <limits.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define E_FLAG 1
#define I_FLAG (1 << 1)
#define V_FLAG (1 << 2)
#define C_FLAG (1 << 3)
#define L_FLAG (1 << 4)
#define N_FLAG (1 << 5)
#define H_FLAG (1 << 6)
#define S_FLAG (1 << 7)
#define F_FLAG (1 << 8)
#define O_FLAG (1 << 9)
#define EXTRA_DATA (1 << 10)  // for -o flag to know when we printed line num
#define MULTIPLE_FILES (1 << 11)  // to check if we need to put filenames
#define REGEX_FOUND (1 << 12)
#define HEAD_IS_FULL (1 << 13)
// short int = 16 bits;
#define MAX_LINE 4096

typedef struct regex_list {
    regex_t regular_expression;
    char debug_string[10];
    struct regex_list *link;
} regex_list;

void free_list(regex_list **head);
void get_flags(unsigned short *head, char *argv[], int argc);
void count_files(unsigned short *flags, int argc, char *argv[],
                 short regex_position);
void create_linked_list();
void list_add_at_tail(regex_t regex, regex_list *head /*, char *regex_str*/);
void list_add_at_head(regex_t regex, regex_list *head, char *regex_str);
void destroy_linked_list(regex_list **head);
short get_regular_expressions(regex_list **head, int argc, char *argv[],
                              unsigned short *flags);
void get_regex_from_file(regex_list *head, int argc, char *argv[],
                         unsigned short flags);
void compile_regular_expression(regex_t *regex, char *argv,
                                unsigned short flags);
bool is_file(char *argv_name);
bool is_flag(const char *argument, unsigned short *flags);
bool check_for_flag(char *ef_flags, unsigned short flags, char *argv[], int j);
int process_file(regex_list *head, unsigned short *flags, char *filename,
                 int *v_flag_counter, int *line_number);
bool print_matched_line(regex_list *head, char *buffer, unsigned short flags,
                        char *filename, int *line_number, int *v_flag_counter);
bool print_only_matched_parts(regex_list *head, char *buffer,
                              unsigned short flags, char *filename,
                              int *line_number /*, int *v_flag_counter*/);
void print_count_of_lines(int match, int vflag_counter,
                          unsigned short int flags, char *filename);
char *getsubstr(char *s, regmatch_t *pmatch);
void replace_cr(char *line, char delim);
void print_error_msg(char *argv[], int i, unsigned short *flags,
                     short regex_position);
/* DEBUG FUNCTIONS */
void convert_to_binary(size_t const size, void const *const ptr);
void print_list(regex_list *head);
#endif  //  SRC_GREP_S21_GREP_H_
