#!bin/bash
#Jonathan Collazo | Recitation 5 | EUID: 11535014


curve() 
{ 
    incr=$1
    shift 
    arr=($@)

    index=0
    
    for i in "${arr[@]}"
    do 
        let grades[$index]=$i+$incr
        index=$index+1
    done 
}

echo "-----Grade Curve-----"
read -p "Enter the amount to curve the grades by:  " amount

if [ -z "$amount" ]
then
    echo "Curve amount needs to be entered."
else
    for i in {1..5}
    do 
        read -p "Enter Quiz #$i: " grades[$i-1]
    done

    curve $amount "${grades[@]}"
    
    echo "---------------------"
    echo "Curved Grades:"
    for (( i=0 ; $i<${#grades[*]}; i=$i+1 ))
    do
        quizNum=$((i+1))
        echo "Quiz #$quizNum: ${grades[$i-1]}"
    done
fi 