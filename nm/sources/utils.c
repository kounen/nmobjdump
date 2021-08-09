/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** utils
*/

#include "../../include/my_nm.h"

void dump_symbol_name(char *symbol_name, int dash_nbr)
{
    if (!strncmp(symbol_name, "wm4.", 4) && dash_nbr)
        printf("wm4.");
    for (int i = 0; i < dash_nbr; i++)
        printf("_");
    if (!strncmp(symbol_name, "wm4.", 4) && dash_nbr)
    {
        symbol_name = strtok(symbol_name + 4, " ");
        symbol_name[strlen(symbol_name) - 2] = '\0';
    }
    printf("%s\n", symbol_name);
}

int get_dash_nbr(const char *symbol_name)
{
    int dash_nbr = 0;

    if (strstr(symbol_name, "wm4."))
        dash_nbr = 4;
    while (symbol_name[dash_nbr] == '_')
    {
        dash_nbr += 1;
    }
    if (strstr(symbol_name, "wm4."))
        dash_nbr -= 4;
    return dash_nbr;
}

bool is_symbol_array(const char *symbol_name)
{
    char *symbol_array_name[4] = {
        "__do_global_dtors_aux_fini_array_entry",
        "__frame_dummy_init_array_entry",
        "__init_array_end",
        "__init_array_start"
    };

    for (int i = 0; i < 4; i++)
    {
        if (!strcmp(symbol_name, symbol_array_name[i]))
        {
            return true;
        }
    }
    return false;
}

int compar(const void *a, const void *b)
{
    char **ia = (char **)a;
    char **ib = (char **)b;

    if (strstr((*ia), "wm4._"))
        for (int i = 4; (*ia)[i + 2] != ' '; i++)
            (*ia)[i] = (*ia)[i + 2];
    if (strstr((*ib), "wm4._"))
        for (int i = 4; (*ib)[i + 2] != ' '; i++)
            (*ib)[i] = (*ib)[i + 2];
    for (int i = 0; (*ia)[i] == '_'; (*ia)++);
    for (int i = 0; (*ib)[i] == '_'; (*ib)++);
    return strcasecmp(*ia, *ib);
}

bool is_truncated_nm(elf_t *elf, char architecture)
{
    if (architecture == ELFCLASS64)
    {
        if ((elf->ehdr64->e_shnum * elf->ehdr64->e_shentsize)
        + elf->ehdr64->e_shoff > elf->size)
        {
            dprintf(2, "nm: %s: file truncated\n", elf->filename);
            return true;
        }
    }
    else if (architecture == ELFCLASS32)
    {
        if ((elf->ehdr32->e_shnum * elf->ehdr32->e_shentsize)
        + elf->ehdr32->e_shoff > elf->size)
        {
            dprintf(2, "nm: %s: file truncated\n", elf->filename);
            return true;
        }
    }
    return false;
}