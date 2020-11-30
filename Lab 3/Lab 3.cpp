//Вариант 2. В двоичном файле поменять местами две записи с заданными номерами.
//Каждая запись представляет собой 2 числа типа short int.

#include <cstdio>
#include <locale.h>
#include "Function.h"
#pragma warning (disable:6387)
#pragma warning (disable:4473)

int main() {
    setlocale(LC_ALL, "Rus");
    int select, n, pos_1, pos_2;
    bool err, flag = true;
    FILE* f_bin;
    FILE* f_txt;
    FILE* log;

    while (flag) {
        printf("1: Очистить log-файл. \n");
        printf("2: Решить задачу. \n");
        printf("3: Завершение работы программы. \n");
        printf("Выбор: ");
        scanf_s("%d", &select);
        switch (select) {

        case (1):
            fopen_s(&log, "log.txt", "wt");
            fclose(log);
            fopen_s(&log, "log.txt", "at");
            fprintf(log, "log-файл очищен. \n");
            fclose(log);
            break;

        case(2):
            fopen_s(&log, "log.txt", "at");
            fopen_s(&f_txt, "input.txt", "rt");
            fopen_s(&f_bin, "output.bin", "wb+");
            printf("Введите количество записей, которые необходимо считать: \n");
            scanf_s("%d", &n); size_check(n);
            input(f_bin, f_txt, n, err);
            if (err) {
                printf("В входном файле недостаточно записей. \n");
                fprintf(log, "В входном файле недостаточно записей. \n");
            }
            else {
                fprintf(log, "Записи считаны. \n");
                output(f_bin, log, n);
                printf("Введите позиции записей, которые необходимо поменять местами: \n");
                scanf_s("%d %d", &pos_1, &pos_2);
                if (pos_1 <= n && pos_2 <= n)
                {
                    fprintf(log, "Позиции для замены: (%d) и (%d). \n", pos_1, pos_2);
                    swap_record(f_bin, pos_1, pos_2);
                    fprintf(log, "Записи (%d) и (%d) поменяны местами. \n", pos_1, pos_2);
                    output(f_bin, log, n);
                }
                else printf("Ошибка. Позиция не должна превосходить количество считанных записей. \n");
            }
            fclose(f_txt); fclose(f_bin); fclose(log);
            break;

        case(3):
            flag = false;
            fopen_s(&log, "log.txt", "a");
            fprintf(log, "Завершение работы программы. \n");
            fclose(log);
            break;

        default:
            printf("Введите корректное значение. \n");
            break;

        }
    }
    return(0);
}