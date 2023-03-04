#!/bin/bash

printDateTime () {
    echo "Current date and time: $(date '+%Y-%m-%d %H:%M:%S')"
}

# Define function to print number of logged in users
printNumUsers(){
    numUsers=$(who | wc -l)
    echo "Number of logged in users: $numUsers"
}

# Function to handle INT signal
trap 'echo "Signal trapped. Press ^C one more time to terminate the script."' INT

# Print current date and time and number of logged in users
printDateTime
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