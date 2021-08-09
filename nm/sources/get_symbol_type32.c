/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** get_symbol_type32
*/

#include "../../include/my_nm.h"

static char get_global_symbol_type32(Elf32_Shdr *shdr, Elf32_Sym symbol,
const char *symbol_name)
{
    if (symbol.st_shndx == SHN_ABS)
        return 'A';
    if (shdr[symbol.st_shndx].sh_type == SHT_NOBITS
        && shdr[symbol.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return 'B';
    if (symbol.st_shndx == SHN_COMMON)
        return 'C';
    if ((shdr[symbol.st_shndx].sh_type == SHT_PROGBITS
        && shdr[symbol.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        || shdr[symbol.st_shndx].sh_type == SHT_DYNAMIC)
        return 'D';
    if ((shdr[symbol.st_shndx].sh_type == SHT_PROGBITS
        && shdr[symbol.st_shndx].sh_flags == SHF_ALLOC) || IS_IO)
        return 'R';
    if (shdr[symbol.st_shndx].sh_type == SHT_PROGBITS
        && shdr[symbol.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        return 'T';
    if (symbol.st_shndx == SHN_UNDEF)
        return 'U';
    else
        return '?';
}

char get_symbol_type32(elf_t *elf, Elf32_Sym symbol,
const char *symbol_name)
{
    char symbol_type = get_global_symbol_type32(elf->shdr32,
    symbol, symbol_name);

    if (ELF32_ST_BIND(symbol.st_info) == STB_GNU_UNIQUE)
        return 'u';
    if (ELF32_ST_BIND(symbol.st_info) == STB_WEAK
        && ELF32_ST_TYPE(symbol.st_info) == STT_OBJECT)
        return (symbol.st_shndx != SHN_UNDEF) ? 'V' : 'v';
    if (ELF32_ST_BIND(symbol.st_info) == STB_WEAK)
        return (symbol.st_shndx != SHN_UNDEF) ? 'W' : 'w';
    else {
        if (symbol_type == '?' && is_symbol_array(symbol_name))
            return 'd';
        if (symbol_type == '?' && elf->ehdr32->e_type == ET_REL)
            return 'n';
        if (symbol_type != '?'
            && ELF32_ST_BIND(symbol.st_info) == STB_LOCAL)
            return symbol_type + 32;
        else
            return symbol_type;
    }
}