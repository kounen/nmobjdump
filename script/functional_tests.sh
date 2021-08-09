#!/bin/bash

Color_Off='\033[0m'
BCyan='\033[1;36m'
Green='\033[0;32m'
Red='\033[0;31m'

test_nm ()
{
    nm ${1} &> real_nm.txt
    ./../my_nm ${1} &> my_nm.txt

    diff real_nm.txt my_nm.txt > /dev/null

    if [ $? -eq 0 ]
    then
        printf "${Green}OK${Color_Off}]\n"
    else
        printf "${Red}KO${Color_Off}]\n"
    fi
}

test_objdump ()
{
    objdump -fs ${1} &> real_objdump.txt
    ./../my_objdump ${1} &> my_objdump.txt

    diff real_objdump.txt my_objdump.txt > /dev/null

    if [ $? -eq 0 ]
    then
        printf "${Green}OK${Color_Off}]\n"
    else
        printf "${Red}KO${Color_Off}]\n"
    fi
}

# Clear terminal
clear

# Run Makefile rule
make -C ../

echo -e "${BCyan}Run functional tests${Color_Off}"

###############################################################################
printf "Executing nm with relocatable files .o\t\t["
test_nm "dump_binary_info64.o"
###############################################################################

###############################################################################
printf "Executing nm with relocatable files .a\t\t["
test_nm "libmy.a"
###############################################################################

###############################################################################
printf "Executing nm with shared files .so\t\t["
test_nm "libmy_malloc.so"
###############################################################################

###############################################################################
printf "Executing nm with 64 bits executable file\t["
test_nm "../my_nm"
###############################################################################

###############################################################################
printf "Executing nm with 32 bits executable file\t["
test_nm "32bits"
###############################################################################

###############################################################################
printf "Executing nm with nonexistent file\t\t["
test_nm "nonexistent"
###############################################################################

###############################################################################
printf "Executing nm with non-format file\t\t["
test_nm "functional_tests.sh"
###############################################################################

###############################################################################
printf "Executing nm with none parameter\t\t["
test_nm
###############################################################################

###############################################################################
printf "Executing nm with several good parameters\t["
test_nm "dump_binary_info64.o ../my_objdump libmy_malloc.so ../my_nm 32bits"
###############################################################################

###############################################################################
printf "Executing nm with several bad parameters\t["
test_nm "nonexistent functional_tests.sh"
###############################################################################

###############################################################################
printf "Executing objdump with relocatable files .o\t["
test_objdump "dump_binary_info64.o"
###############################################################################

###############################################################################
printf "Executing objdump with relocatable files .a\t["
test_objdump "libmy.a"
###############################################################################

###############################################################################
printf "Executing objdump with shared files .so\t\t["
test_objdump "libmy_malloc.so"
###############################################################################

###############################################################################
printf "Executing objdump with 64 bits executable file\t["
test_objdump "../my_objdump"
###############################################################################

###############################################################################
printf "Executing objdump with 32 bits executable file\t["
test_objdump "32bits"
###############################################################################

###############################################################################
printf "Executing objdump with nonexistent file\t\t["
test_objdump "nonexistent"
###############################################################################

###############################################################################
printf "Executing objdump with non-format file\t\t["
test_objdump "functional_tests.sh"
###############################################################################

###############################################################################
printf "Executing objdump with none parameter\t\t["
test_objdump
###############################################################################

###############################################################################
printf "Executing objdump with several good parameters\t["
test_objdump "dump_binary_info64.o ../my_nm libmy_malloc.so ../my_objdump"
###############################################################################

###############################################################################
printf "Executing objdump with several bad parameters\t["
test_objdump "nonexistent functional_tests.sh"
###############################################################################
