# enter notes directory
mkdir -p ~/Documents/todo
cd ~/Documents/todo

# start git
git init

# initialize date to today
date=$(date +%F)

# main input loop
while [[ $input != "q" ]]; do
    clear

    # print selected date
    date --date=$date '+%A, %B %d, %Y'

    # print selected date's tasks
    if [ ! -f $date ]; then
        echo "Nothing to do!"
    else
        cat -n $date
    fi
    echo

    # user input
    echo -n "(c)hange day; (a)dd task; (r)emove task; (s)how all tasks; (q)uit: "
    read input
    case $input in
        "c")
            exit_status="1"
            while [[ $exit_status != "0" ]]; do
                echo -n "Enter desired day: "
                read input
                date=$(date --date="$input" +%F)
                exit_status=$(echo $?)
            done
            ;;
        "a")
            echo -n ">>> "
            read input
            echo $input >> $date
            ;;
        "r")
            echo -n "Enter line number: "
            read input
            sed -i -e ${input}d $date
            if [[ $(cat $date) == "" ]]; then
                rm $date
            fi
            ;;
        "s")
            clear
            if [ -z "$(ls .)" ]; then
                echo "All tasks are complete!"
                echo "Press enter to continue..."
                read input
                continue
            fi
            for date_file in *; do
                date --date=$date_file '+%A, %B %d, %Y'
                cat -n $date_file
                echo
            done
            echo "Press enter to continue..."
            read input
            ;;
    esac

    # git commit
    git add $date
    git commit -m "automated"
done
clear
