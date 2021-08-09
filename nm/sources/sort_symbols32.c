/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** sort_symbols32
*/

#include "../../include/my_nm.h"

static void get_unsorted_symbols32(elf_t *elf, size_t symnb, Elf32_Sym *symtab,
uint8_t *strtab)
{
    char buffer[128] = {0};

    elf->symbols_info = malloc(sizeof(char *) * symnb);
    for (size_t i = 0; i < symnb; i++)
    {
        if (symtab[i].st_name && symtab[i].st_info != STT_FILE)
        {
            sprintf(buffer, "%s %c %08x %d",
            &strtab[symtab[i].st_name],
            get_symbol_type32(elf, symtab[i],
            (char *)&strtab[symtab[i].st_name]),
            symtab[i].st_value,
            get_dash_nbr((char *) &strtab[symtab[i].st_name]));
        }
        else
        {
            memset(buffer, 0, sizeof(buffer));
        }
        elf->symbols_info[i] = strdup(buffer);
    }
}

void sort_symbols32(elf_t *elf, size_t symnb, Elf32_Sym *symtab,
uint8_t *strtab)
{
    get_unsorted_symbols32(elf, symnb, symtab, strtab);
    qsort(elf->symbols_info, symnb, sizeof(char *), compar);
    sort_same_name_symbols(elf, symnb);
    sort_specific_symbols(elf, symnb, "data_start");
    sort_specific_symbols(elf, symnb, "wm4.floatn.h");
}