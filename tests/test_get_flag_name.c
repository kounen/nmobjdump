/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** test_get_flag_name
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_objdump.h"
#include "flags.h"

Test(get_flag_name, relocFlag)
{
    cr_assert_str_eq(get_flag_name(0x01), "HAS_RELOC");
}

Test(get_flag_name, execFlag)
{
    cr_assert_str_eq(get_flag_name(0x02), "EXEC_P");
}

Test(get_flag_name, symsFlag)
{
    cr_assert_str_eq(get_flag_name(0x10), "HAS_SYMS");
}

Test(get_flag_name, dynamicFlag)
{
    cr_assert_str_eq(get_flag_name(0x40), "DYNAMIC");
}

Test(get_flag_name, pagedFlag)
{
    cr_assert_str_eq(get_flag_name(0x100), "D_PAGED");
}

Test(get_flag_name, unknownFlag)
{
    cr_assert_str_eq(get_flag_name(0x03), "");
}