#!/bin/bash --posix

bsh_name="./42sh"

if [ -x $bsh_name ]
then
    echo -en "\n                              \033[42;1m###START CHECKS###\033[0m\n\n"
else
    echo -en "\033[31;1mERROR: no such $bsh_name file\033[0m\n"
    exit
fi

echo -en "                              \033[45;1m____TEST PARSER____\033[0m\n"

echo -en "---test non existen command---\n"
err=$($bsh_name -c "ololo" 2>&1)
suc="21sh: ololo: command not found"
if [ "$err" = "$suc" ]
then
    echo -en "\033[32;1m SUCCESS \033[0m"
    echo -e "\n"
else
    echo -en "\033[31;1m FAULT \033[0m"
    echo -e "\n"
fi


echo -en "                              \033[45;1m____TEST CD____\033[0m\n"

echo -e "---test permission---"
mkdir test1
chmod 000 test1
err=$($bsh_name -c "cd test1" 2>&1)
suc="21sh: cd: test1: permission denied"
if [ "$err" = "$suc" ]
then
    echo -en "\033[32;1m SUCCESS \033[0m"
    echo -e "\n"
else
    echo -en "\033[31;1m FAULT \033[0m"
    echo -e "\n"
fi
rm -rf test1

echo -en "---test 'no such file or directory'---\n"
err=$($bsh_name -c "cd ololo" 2>&1)
suc="21sh: cd: ololo: no such file or directory"
if [ "$err" = "$suc" ]
then
    echo -en "\033[32;1m SUCCESS \033[0m"
    echo -e "\n"
else
    echo -en "\033[31;1m FAULT \033[0m"
    echo -e "\n"
fi
