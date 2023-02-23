#!bin/bash
#Jonathan Collazo || Recitation 4 || EUID: 11535014
randnum=$(($RANDOM % 10 + 1 ))
guess=0

while [ $guess -ne $randnum ]
do
    read -p "Enter a number between 1 and 10: " guess
    if [ $guess -lt $randnum ]
    then
        echo "Too low!"
    elif [ $guess -gt $randnum ]
    then
        echo "Too high!"
    else
        echo "Congratulations! The number was $randnum."
    fi
done
