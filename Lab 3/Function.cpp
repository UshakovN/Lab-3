#include <cstdio>
#pragma warning (disable:6064)

const int NMAX = 2;
typedef short int record[NMAX];

void check_record(FILE* f_txt, record& buffer, bool& flag, bool& eol) {
    int i = 0; char ch;
    flag = true; eol = false;

    while (i < NMAX && flag) {
        if (fscanf_s(f_txt, "%hd", &buffer[i]) == 1)
        {
            fscanf_s(f_txt, "%c", &ch);
            if (ch == '\n') eol = true;
            if (ch != ' ' && ch != '\n') flag = false;
            i++;
        }
        else flag = false;
    }
    return;
}

void input(FILE* f_bin, FILE* f_txt, int n, bool& err) {
    record buffer = { 0,0 };
    bool flag, eol; int i = 0;
    err = false;

    while (i < n && !feof(f_txt)) {
        check_record(f_txt, buffer, flag, eol);
        if (flag) {
            fwrite(&buffer, sizeof(record), 1, f_bin);
            i++;
        }
        if (!eol) fscanf_s(f_txt, "%*[^\n]");
    }
    if (i != n) err = true;
    return;
}

void output(FILE* f_bin, FILE* f_txt, int n) {
    record buffer;

    fprintf(f_txt, "Записи: \n");
    for (int i = 0; i < n; i++) {
        fseek(f_bin, i * sizeof(record), SEEK_SET);
        fread(&buffer, sizeof(record), 1, f_bin);
        fprintf(f_txt, "(%d): %hd %hd \n", i + 1, (buffer[0]), (buffer[1]));
    }
    return;
}

void swap_record(FILE* f_bin, int pos_1, int pos_2) {
    record buffer_1, buffer_2;

    fseek(f_bin, (pos_1 - 1) * sizeof(record), SEEK_SET);
    fread(&buffer_1, sizeof(record), 1, f_bin);

    fseek(f_bin, (pos_2 - 1) * sizeof(record), SEEK_SET);
    fread(&buffer_2, sizeof(record), 1, f_bin);

    fseek(f_bin, (pos_1 - 1) * sizeof(record), SEEK_SET);
    fwrite(&buffer_2, sizeof(record), 1, f_bin);

    fseek(f_bin, (pos_2 - 1) * sizeof(record), SEEK_SET);
    fwrite(&buffer_1, sizeof(record), 1, f_bin);

    return;
}

void size_check(int& n) {
    while (n < 2 || n > 20) {
        printf("Ошибка. Введите значение от 2 до 20. \n");
            scanf_s("%d", &n);
    }
    return;
}