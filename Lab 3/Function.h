#pragma once
#include <cstdio>

const int NMAX = 2;
typedef short int record[NMAX];

void check_record(FILE* f_txt, record& buffer, bool& flag, bool& eol);
void input(FILE* f_bin, FILE* f_txt, int n, bool& err);
void output(FILE* f_bin, FILE* f_txt, int n);
void swap_record(FILE* f_bin, int pos_1, int pos_2);
void size_check(int& n);