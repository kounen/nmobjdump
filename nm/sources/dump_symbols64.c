/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** dump_symbols64
*/

#include "../../include/my_nm.h"

static void get_symbol_setup64(elf_t *elf, size_t *symnb, Elf64_Sym **symtab,
uint8_t **strtab)
{
    for (int i = 0; i < elf->ehdr64->e_shnum; i++)
    {
        if (elf->shdr64[i].sh_type == SHT_SYMTAB)
        {
            (*symnb) = elf->shdr64[i].sh_size / elf->shdr64[i].sh_entsize;
            (*symtab) =
            (Elf64_Sym *)((uint8_t *)elf->ehdr64 + elf->shdr64[i].sh_offset);
            (*strtab) =
            (uint8_t *)elf->data +
            elf->shdr64[elf->shdr64[i].sh_link].sh_offset;
            break;
        }
    }
}

//FIXME: free strdup
static void display_symbols_info64(elf_t *elf, size_t symnb, Elf64_Sym *symtab,
uint8_t *strtab)
{
    char delim[] = " ";
    char *symbol_value, *symbol_type, *symbol_name;
    int dash_nbr = 0;

    sort_symbols64(elf, symnb, symtab, strtab);
    for (size_t i = 0; i < symnb; i++)
        if (elf->symbols_info[i][0])
        {
            symbol_name = strtok(elf->symbols_info[i], delim);
            symbol_type = strtok(NULL, delim);
            symbol_value = strtok(NULL, delim);
            dash_nbr = atoi(strtok(NULL, delim));
            printf("%s %s ", SYMBOL_VALUE, symbol_type);
            dump_symbol_name(symbol_name, dash_nbr);
        }
    free(elf->symbols_info);
}

void dump_symbols64(elf_t *elf, int argc)
{
    size_t symnb = 0;
    Elf64_Sym *symtab = NULL;
    uint8_t *strtab = NULL;

    get_symbol_setup64(elf, &symnb, &symtab, &strtab);
    if (symnb) {
        if (argc > 2)
            printf("\n%s:\n", elf->filename);
        display_symbols_info64(elf, symnb, symtab, strtab);
    } else
        dprintf(2, "nm: %s: no symbols\n", elf->filename);
}