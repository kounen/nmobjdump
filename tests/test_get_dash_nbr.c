/*
** EPITECH PROJECT, 2021
** B-PSU-400-LYN-4-1-nmobjdump-lucas.guichard
** File description:
** test_get_dash_nbr
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_nm.h"

Test(get_dash_nbr, simpleSymbolName)
{
    cr_assert_eq(get_dash_nbr("__HelloWorld"), 2);
}

Test(get_dash_nbr, noneDash)
{
    cr_assert_eq(get_dash_nbr("HelloWorld"), 0);
}

Test(get_dash_nbr, relocatableSymbolName)
{
    cr_assert_eq(get_dash_nbr("wm4._HelloWorld"), 1);
}
