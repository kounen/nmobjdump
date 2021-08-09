/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** my_objdump
*/

#ifndef MY_OBJDUMP_H_
#define MY_OBJDUMP_H_

#include <stdbool.h>
#include <link.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ar.h>

typedef struct
{
    const char *filename;
    size_t size;
    void *data;
    Elf32_Ehdr *ehdr32;
    Elf32_Shdr *shdr32;
    Elf64_Ehdr *ehdr64;
    Elf64_Shdr *shdr64;
    void *strtable;
    bool is_archive;
} elf_t;

bool is_valid_elf(elf_t *elf, const char *filename);
int initialize_elf_structure(elf_t *elf);
void dump_elf(elf_t *elf, const char *filename);
int my_objdump(const char *filename);

// 64BITS ARCHITECTURE
void dump_binary_info64(elf_t *elf, const char *filename);
void dump_section_info64(elf_t *elf, const char *filename);

// 32BITS ARCHITECTURE
void dump_binary_info32(elf_t *elf, const char *filename);
void dump_section_info32(elf_t *elf, const char *filename);

// UTILS
const char *get_flag_name(uint32_t flag_type);
void dump_flags(uint32_t flags);
void dump_section_line(uint8_t *line_data, size_t line_size);
bool is_truncated_objdump(elf_t *elf, char architecture);
void set_debug_flag(bool *is_debug_str, const char *filename,
const char *section_name);

// ARCHIVE
typedef struct ar_hdr ar_hdr_t;
bool is_archive(elf_t *elf);
void dump_archive(elf_t *elf);

#endif /* !MY_OBJDUMP_H_ */
