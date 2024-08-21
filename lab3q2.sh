echo "Enter the number of odd numbers to print:"
read n
count=0
num=1
while [ $count -lt $n ]; do
    echo $num
    num=$((num + 2))
    count=$((count + 1))
done