/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** archive
*/

#include "../../include/my_objdump.h"

bool is_archive(elf_t *elf)
{
    if (!strncmp(elf->data, ARMAG, SARMAG))
    {
        elf->is_archive = true;
        return true;
    }
    return false;
}

void dump_archive(elf_t *elf)
{
    void *elf_data = elf->data;
    ar_hdr_t *archive_header = (ar_hdr_t *)((uint8_t *)elf->data + SARMAG);
    size_t file_member_size = strtoul(archive_header->ar_size, NULL, 10);
    char archive_name[16];

    printf("In archive %s:\n", elf->filename);
    archive_header = (void *)((size_t)archive_header + sizeof(*archive_header))
    + file_member_size;
    while (!strncmp(archive_header->ar_fmag, ARFMAG, strlen(ARFMAG))) {
        sprintf(archive_name, "%.*s",
        (int)strcspn(archive_header->ar_name, "/"), archive_header->ar_name);
        elf->data = archive_header + 1;
        elf->ehdr64 = (Elf64_Ehdr *)elf->data;
        if (is_valid_elf(elf, archive_name)
            && initialize_elf_structure(elf) == EXIT_SUCCESS)
            dump_elf(elf, archive_name);
        file_member_size = strtoul(archive_header->ar_size, NULL, 10);
        archive_header = (void *)((size_t)archive_header
        + sizeof(*archive_header)) + file_member_size;
    }
    elf->data = elf_data;
}