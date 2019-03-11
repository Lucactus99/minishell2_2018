#!/bin/sh

echo "Entrez votre test: "
read COMMAND

echo $COMMAND | ./mysh > text.txt 2>&1
echo $? > status1.txt
echo $COMMAND | tcsh > text2.txt 2>&1
echo $? > status2.txt

if diff text.txt text2.txt && diff status1.txt status2.txt
then
    echo "Le programme fonctionne !"
fi