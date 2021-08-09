/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** dump_binary_info32
*/

#include "../../include/my_objdump.h"
#include "../../include/flags.h"

static uint32_t get_flags32(elf_t *elf)
{
    uint32_t flags = 0;
    const char *section_name;

    flags |= (elf->ehdr32->e_type == ET_REL) ? HAS_RELOC : 0;
    flags |= (elf->ehdr32->e_type == ET_EXEC) ? EXEC_P : 0;
    for (int i = 0; elf->strtable && i < elf->ehdr32->e_shnum; i++)
    {
        section_name = elf->strtable + elf->shdr32[i].sh_name;
        if (!strcmp(section_name, ".dynsym")
        || !strcmp(section_name, ".symtab"))
        {
            flags |= HAS_SYMS;
            break;
        }
    }
    flags |= (elf->ehdr32->e_type == ET_DYN) ? DYNAMIC : 0;
    flags |= (elf->ehdr32->e_phnum) ? D_PAGED : 0;
    return flags;
}

void dump_binary_info32(elf_t *elf, const char *filename)
{
    uint32_t flags = get_flags32(elf);

    printf("\n%s:     file format elf32-i386\n", filename);
    printf("architecture: i386, flags 0x%08x:\n", flags);
    dump_flags(flags);
    printf("start address 0x%08x\n\n", elf->ehdr32->e_entry);
}