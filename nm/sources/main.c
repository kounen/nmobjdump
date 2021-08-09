/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** main my_nm
*/

#include "../../include/my_nm.h"

int main(int argc, char *argv[])
{
    bool error = false;

    if (argc == 1) {
        if (my_nm("a.out", argc)) return 84;
    } else {
        for (int i = 1; i < argc; i++)
            error = my_nm(argv[i], argc);
        return error ? 84 : 0;
    }
    return 0;
}