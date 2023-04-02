#!/bin/bash
#Jonathan Collazo || Recitation 4 || EUID: 11535014
read -p "Enter a Linux command to perform:  " command
if [ -z "$command" ]
then
    echo "You did not enter a command."
else
    echo "Command to be executed: $command"
    $command 
fi