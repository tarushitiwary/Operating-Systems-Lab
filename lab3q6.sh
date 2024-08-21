echo "Enter n number of numbers to sum:"
read n
i=0
sum=0
for ((i=0; i<n; i++)); do
    echo "Enter number: "
    read num
    sum=$((sum + num))
done
echo "Sum is $sum"