echo "Enter number to find factorial of:"
read n
x=1
i=0
for ((i=n; i>0; i--)); do
    x=$((x * i))
done
echo "Factorial is $x"