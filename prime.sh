read -p "Enter the limit:=> " limit
for (( num = 2; num <= limit ; num++ ))
do
is_prime=1
for (( i = 2; i*i <= num; i++ ))
do
if [ $((num % i)) -eq 0 ]
then
is_prime=0
break
fi
done
if [ $is_prime -eq 1 ]
then
echo "$num"
fi
done

