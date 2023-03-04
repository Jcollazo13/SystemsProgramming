#!/bin/bash

printDateTime () {
    echo "Current date and time: $(date '+%m-%d-%Y %H:%M')"
}

# Define function to print number of logged in users
printNumUsers(){
    numUsers=$(who | wc -l)
    echo "Number of logged in users: $numUsers"
}

printHeader(){
    
    echo "User ID  ||  Date/Time   ||    Process Count "
    echo "============================================ "
}

# Function to confirm exit command
trap 'read -p " Are you sure you want to exit(y/n)?" -n 1 -r; echo; if [[ $REPLY =~ ^[Yy]$ ]]; then exit 1; fi' INT

# Print current date and time and number of logged in users
printDateTime
printHeader
printNumUsers

# Initialize array of current logged in users
currentUsers=($(who | awk '{print $1 "@" $NF}'))

# Loop indefinitely to monitor users
while true
do
    # Wait for 5 seconds
    sleep 5

    # Print current date and time
    printDateTime

    # Get list of currently logged in users
    newUsers=($(who | awk '{print $1 "@" $NF}'))

    #print current users logged in 
    for user in "${currentUsers[@]}"
    do
        echo "${user%*@} || $(date '+%m-%d-%Y %H:%M') || $(ps -u ${user%*@} | wc -l)"
    done

    # Compare current and new user arrays to detect changes
    for user in "${newUsers[@]}"
    do
        if [[ ! " ${currentUsers[@]} " =~ " ${user} " ]]
        then
            # User logged in
            echo "User ${user%*@} logged in from ${user#*@}"
        fi
    done

    for user in "${currentUsers[@]}"
    do
        if [[ ! " ${newUsers[@]} " =~ " ${user} " ]]
        then
            # User logged out
            echo "User ${user%*@} logged out from ${user#*@}"
        fi
    done

    # Update current user array
    current_users=("${newUsers[@]}")

    # Print number of logged in users
    printNumUsers
done