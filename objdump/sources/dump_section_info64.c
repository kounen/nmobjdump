/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** dump_section_info64
*/

#include "../../include/my_objdump.h"

static bool is_valid_section64(Elf64_Shdr shdr)
{
    if (shdr.sh_size
    && shdr.sh_type != SHT_NOBITS
    && (shdr.sh_addr || (!shdr.sh_addr
    && shdr.sh_type != SHT_STRTAB
    && shdr.sh_type != SHT_SYMTAB
    && shdr.sh_type != SHT_RELA)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

static void dump_section_content64(Elf64_Shdr shdr, elf_t *elf,
bool is_debug_str)
{
    uint8_t *line_data;
    size_t line_size;
    size_t line_address;

    for (size_t i = 0; i < shdr.sh_size; i += 16)
    {
        line_address = (size_t)shdr.sh_addr + i;
        if (is_debug_str && line_address <= 0xfff0 && !elf->is_archive)
            printf(" 0%04lx ", line_address);
        else
            printf(" %04lx ", line_address);
        line_data = (uint8_t *)elf->ehdr64 + shdr.sh_offset + i;
        line_size = shdr.sh_size - i;
        dump_section_line(line_data, line_size);
    }
}

void dump_section_info64(elf_t *elf, const char *filename)
{
    const char *section_name;
    bool is_debug_str;

    if (!elf->strtable)
        return;
    for (int i = 0; i < elf->ehdr64->e_shnum; i++) {
        section_name = elf->strtable + elf->shdr64[i].sh_name;
        if (section_name && is_valid_section64(elf->shdr64[i])) {
            is_debug_str = false;
            printf("Contents of section %s:\n", section_name);
            set_debug_flag(&is_debug_str, filename, section_name);
            dump_section_content64(elf->shdr64[i], elf, is_debug_str);
        }
    }
}