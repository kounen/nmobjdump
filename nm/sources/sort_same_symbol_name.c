/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** sort_same_symbol_name
*/

#include "../../include/my_nm.h"

static size_t get_symbol_name_length(const char *symbol_info)
{
    int symbol_name_length = 0;

    while (symbol_info[symbol_name_length] != ' ')
    {
        symbol_name_length += 1;
    }
    return symbol_name_length;
}

static void swap_same_symbols(char *symbol1, char *symbol2, elf_t *elf, int i)
{
    char *tmp;

    if (!strcmp(symbol1, symbol2))
    {
        tmp = elf->symbols_info[i + 1];
        elf->symbols_info[i + 1] = elf->symbols_info[i];
        elf->symbols_info[i] = tmp;
    }
}

void sort_same_name_symbols(elf_t *elf, size_t symnb)
{
    char *symbol1_name, *symbol2_name;

    for (size_t i = 0; i < symnb; i++)
    {
        if (i + 1 < symnb && elf->symbols_info[i][0])
        {
            symbol1_name = strndup(elf->symbols_info[i],
            get_symbol_name_length(elf->symbols_info[i]));
            symbol2_name = strndup(elf->symbols_info[i + 1],
            get_symbol_name_length(elf->symbols_info[i + 1]));
            swap_same_symbols(symbol1_name, symbol2_name, elf, i);
            free(symbol1_name);
            free(symbol2_name);
        }
    }
}

void sort_specific_symbols(elf_t *elf, size_t symnb, const char *symbol_name)
{
    char *tmp;

    for (size_t i = 0; i < symnb; i++)
    {
        if (i + 1 < symnb
        && !strncmp(elf->symbols_info[i], symbol_name, strlen(symbol_name)))
        {
            tmp = elf->symbols_info[i + 1];
            elf->symbols_info[i + 1] = elf->symbols_info[i];
            elf->symbols_info[i] = tmp;
            break;
        }
    }
}