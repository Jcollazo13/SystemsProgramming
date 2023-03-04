#!/bin/bash

printDateTime () {
    echo "Current date and time: $(date '+%a %b %d %H:%M:%S %Z %Y')"
}

# Define function to print number of logged in users
printNumUsers(){
    numUsers=$(who | wc -l)
    echo "$(date '+%a %b %d %H:%M:%S %Z %Y') # of users: $numUsers"
}

printHeader(){
    
    echo "            User Monitor "
    echo "============================================ "
}

confirmExit(){
    read -p " Are you sure you want to exit(y/n)?" -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        echo "Exiting ......."
        exit 1
    else 
        echo "Continuing ......."
    fi
}

# Traps
trap confirmExit SIGINT

# Print current date and time and number of logged in users
printDateTime
printHeader
printNumUsers

# create array of currently logged in users
currentUsers=($(users))

#print current users logged in
echo "Current users logged in: "
for user in "${currentUsers[@]}"
do
    echo "${user} is logged in to $HOSTNAME"
done

# Loop to monitor users logging in and out
while true
do
    # Wait for 5 seconds
    sleep 5

    # Create new array of currently logged in users 
    newUsers=($(users))

    # Compare current and new user arrays to detect changes
    for user in "${newUsers[@]}"
    do
        # Looking for new users that are not in currentUsers array, if found, means that user logged in 
        if [[ ! " ${currentUsers[@]} " =~ " ${user} " ]]
        then
            echo "${user} logged in to $HOSTNAME"
        fi
    done

    #Looking for users that are not in newUsers array, if found, means that user logged out
    for user in "${currentUsers[@]}"
    do
        if [[ ! " ${newUsers[@]} " =~ " ${user} " ]]
        then
            echo "${user} logged out of $HOSTNAME"
        fi
    done

    # Update current user array before next loop
    currentUsers=("${newUsers[@]}")

    # Print number of logged in users
    printNumUsers
done