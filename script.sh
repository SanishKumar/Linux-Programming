echo "Enter The number for multiplication table: "
read num
temp=num
# num2=2
i=1
while [ $i -lt 11 ]
do

let "temp=$num * $i"
#let "num2=$num2 + 1"
echo $num "X" $i "=" $temp
let "i=$i + 1"
done
