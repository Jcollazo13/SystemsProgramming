#!/bin/bash

# Define function to print current date and time
print_datetime() {
    echo "Current date and time: $(date '+%Y-%m-%d %H:%M:%S')"
}

# Define function to print number of logged in users
print_num_users() {
    num_users=$(who | wc -l)
    echo "Number of logged in users: $num_users"
}

# Define function to handle SIGINT signal
trap 'echo "SIGINT signal trapped. Press ^C one more time to terminate the script."' SIGINT

# Print current date and time and number of logged in users
print_datetime
print_num_users

# Initialize array of current logged in users
current_users=($(who | awk '{print $1 "@" $NF}'))

# Loop indefinitely to monitor users
while true
do
    # Wait for 5 seconds
    sleep 5

    # Print current date and time
    print_datetime

    # Get list of currently logged in users
    new_users=($(who | awk '{print $1 "@" $NF}'))

    # Compare current and new user arrays to detect changes
    for user in "${new_users[@]}"
    do
        if [[ ! " ${current_users[@]} " =~ " ${user} " ]]
        then
            # User logged in
            echo "User ${user%*@} logged in from ${user#*@}"
        fi
    done

    for user in "${current_users[@]}"
    do
        if [[ ! " ${new_users[@]} " =~ " ${user} " ]]
        then
            # User logged out
            echo "User ${user%*@} logged out from ${user#*@}"
        fi
    done

    # Update current user array
    current_users=("${new_users[@]}")

    # Print number of logged in users
    print_num_users
done
