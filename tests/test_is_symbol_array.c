/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** test_is_symbol_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_nm.h"

Test(is_symbol_array, isAnSymbolArray)
{
    cr_assert_eq(is_symbol_array("__init_array_end"), true);
}

Test(is_symbol_array, isNOTAnSymbolArray)
{
    cr_assert_eq(is_symbol_array("HelloWorld"), false);
}