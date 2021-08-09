/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** utils
*/

#include "../../include/my_objdump.h"
#include "../../include/flags.h"

const char *get_flag_name(uint32_t flag_type)
{
    switch (flag_type) {
    case HAS_RELOC:
        return "HAS_RELOC";
        break;
    case EXEC_P:
        return "EXEC_P";
        break;
    case HAS_SYMS:
        return "HAS_SYMS";
        break;
    case DYNAMIC:
        return "DYNAMIC";
        break;
    case D_PAGED:
        return "D_PAGED";
        break;
    default:
        return "";
        break;
    }
}

void dump_flags(uint32_t flags)
{
    bool first_flag = true;

    for (uint32_t i = 1; i <= D_PAGED; i = (i << 1))
    {
        if ((flags & i) && first_flag)
        {
            printf("%s", get_flag_name(i));
            first_flag = false;
        }
        else if ((flags & i) && !first_flag)
        {
            printf(", %s", get_flag_name(i));
        }
    }
    printf("\n");
}

void dump_section_line(uint8_t *line_data, size_t line_size)
{
    for (size_t i = 0; i < 16; i++)
    {
        (i < line_size) ? printf("%02x", line_data[i]) : printf("  ");
        if ((i + 1) % 4 == 0)
        {
            printf(" ");
        }
    }
    printf(" ");
    for (size_t i = 0; i < 16; i++)
    {
        if (i < line_size)
        {
            printf("%c", isprint(line_data[i]) ? line_data[i] : '.');
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}

bool is_truncated_objdump(elf_t *elf, char architecture)
{
    if (architecture == ELFCLASS64)
    {
        if ((elf->ehdr64->e_shnum * elf->ehdr64->e_shentsize)
        + elf->ehdr64->e_shoff != elf->size)
        {
            dprintf(2, "objdump: %s: file truncated\n", elf->filename);
            return true;
        }
    }
    else if (architecture == ELFCLASS32)
    {
        if ((elf->ehdr32->e_shnum * elf->ehdr32->e_shentsize)
        + elf->ehdr32->e_shoff != elf->size)
        {
            dprintf(2, "objdump: %s: file truncated\n", elf->filename);
            return true;
        }
    }
    return false;
}

void set_debug_flag(bool *is_debug_str, const char *filename,
const char *section_name)
{
    if (!strcmp(section_name, ".debug_str") && !strstr(filename, ".so"))
        (*is_debug_str) = true;
}