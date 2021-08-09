/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** my_objdump
*/

#include "../../include/my_objdump.h"

static elf_t *get_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    elf_t *elf = malloc(sizeof(elf_t));

    if (!elf) return NULL;
    if (fd == -1) {
        dprintf(2, "objdump: '%s': No such file\n", filename);
        return NULL;
    }
    if ((elf->size = lseek(fd, 0, SEEK_END)) <= 0) return NULL;
    elf->filename = filename;
    elf->data = mmap(NULL, elf->size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (elf->data == MAP_FAILED) return NULL;
    elf->ehdr64 = (Elf64_Ehdr *)elf->data;
    close(fd);
    return elf;
}

bool is_valid_elf(elf_t *elf, const char *filename)
{
    if (elf->ehdr64->e_ident[EI_MAG0] != ELFMAG0 ||
    elf->ehdr64->e_ident[EI_MAG1] != ELFMAG1 ||
    elf->ehdr64->e_ident[EI_MAG2] != ELFMAG2 ||
    elf->ehdr64->e_ident[EI_MAG3] != ELFMAG3 ||
    (elf->ehdr64->e_type != ET_REL
    && elf->ehdr64->e_type != ET_DYN
    && elf->ehdr64->e_type != ET_EXEC))
    {
        dprintf(2, "objdump: %s: file format not recognized\n", filename);
        return false;
    }
    return true;
}

int initialize_elf_structure(elf_t *elf)
{
    if (elf->ehdr64->e_ident[EI_CLASS] == ELFCLASS64)
    {
        elf->shdr64 =
        (Elf64_Shdr *)((uint8_t *)elf->data + elf->ehdr64->e_shoff);
        elf->strtable =
        (uint8_t *)elf->data + elf->shdr64[elf->ehdr64->e_shstrndx].sh_offset;
    }
    else if (elf->ehdr64->e_ident[EI_CLASS] == ELFCLASS32)
    {
        elf->ehdr32 = (Elf32_Ehdr *)elf->data;
        elf->shdr32 =
        (Elf32_Shdr *)((uint8_t *)elf->data + elf->ehdr32->e_shoff);
        elf->strtable =
        (uint8_t *)elf->data + elf->shdr32[elf->ehdr32->e_shstrndx].sh_offset;
    }
    return EXIT_SUCCESS;
}

void dump_elf(elf_t *elf, const char *filename)
{
    if (elf->ehdr64->e_ident[EI_CLASS] == ELFCLASS64)
    {
        dump_binary_info64(elf, filename);
        dump_section_info64(elf, filename);
    }
    else if (elf->ehdr64->e_ident[EI_CLASS] == ELFCLASS32)
    {
        dump_binary_info32(elf, filename);
        dump_section_info32(elf, filename);
    }
}

int my_objdump(const char *filename)
{
    elf_t *elf = get_file(filename);

    if (elf && is_archive(elf))
    {
        dump_archive(elf);
    }
    else
    {
        if (!elf || !is_valid_elf(elf, filename))
            return EXIT_FAILURE;
        if (initialize_elf_structure(elf) == EXIT_FAILURE)
            return EXIT_FAILURE;
        dump_elf(elf, filename);
    }
    if (munmap(elf->data, elf->size) == -1)
        return EXIT_FAILURE;
    free(elf);
    return EXIT_SUCCESS;
}
