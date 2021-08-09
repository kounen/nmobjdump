/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** my_nm
*/

#ifndef MY_NM_H_
#define MY_NM_H_

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <elf.h>
#include <stdbool.h>
#include <link.h>
#include <string.h>
#include <ar.h>

#define SYMBOL_VALUE \
strcmp(symbol_value, "0000000000000000") \
? symbol_value : (!strcmp(symbol_type, "n") \
|| !strcmp(symbol_type, "t") \
|| !strcmp(symbol_type, "T")) \
? "0000000000000000" : "                "

#define IS_IO \
!strcmp(symbol_name, "_IO_stdin_used")

typedef struct
{
    const char *filename;
    size_t size;
    void *data;
    Elf32_Ehdr *ehdr32;
    Elf32_Shdr *shdr32;
    Elf64_Ehdr *ehdr64;
    Elf64_Shdr *shdr64;
    char **symbols_info;
} elf_t;

bool is_valid_elf(elf_t *elf, const char *filename);
int initialize_elf_structure(elf_t *elf);
void dump_elf(elf_t *elf, int argc);
int my_nm(const char *filename, int argc);

// 64BITS ARCHITECTURE
void dump_symbols64(elf_t *elf, int argc);
void sort_symbols64(elf_t *elf, size_t symnb, Elf64_Sym *symtab,
uint8_t *strtab);
char get_symbol_type64(elf_t *elf, Elf64_Sym symbol,
const char *symbol_name);

// 32BITS ARCHITECTURE
void dump_symbols32(elf_t *elf, int argc);
void sort_symbols32(elf_t *elf, size_t symnb, Elf32_Sym *symtab,
uint8_t *strtab);
char get_symbol_type32(elf_t *elf, Elf32_Sym symbol,
const char *symbol_name);

// SORT FUNCTIONS
void sort_same_name_symbols(elf_t *elf, size_t symnb);
void sort_specific_symbols(elf_t *elf, size_t symnb, const char *symbol_name);

// UTILS
void dump_symbol_name(char *symbol_name, int dash_nbr);
int get_dash_nbr(const char *symbol_name);
bool is_symbol_array(const char *symbol_name);
int compar(const void *a, const void *b);
bool is_truncated_nm(elf_t *elf, char architecture);

// ARCHIVE
typedef struct ar_hdr ar_hdr_t;
bool is_archive(elf_t *elf);
void dump_archive(elf_t *elf);

#endif /* !MY_NM_H_ */
