#!/bin/bash
#Jonathan Collazo || Recitation 4 || EUID: 11535014

read -p "What is your name? " name
if [ -z "$name" ] 
then
    echo "Hope you have a great day!"
else
    
    echo "Good day, $name ! Nice to meet you!" 
fi