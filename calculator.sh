echo "Enter number 1: "
read num1
echo "Enter number 2: "
read num2
echo "What would like to do?:(Add, Sub, Mul, Div)"
read cal

case "$cal" in
"Add") let "num1 = $num1 + $num2"
echo "The Sum is: " $num1
;;
"Sub") let "num1 = $num1 - $num2"
echo "The Difference is: " $num1
;;
"Mul") let "num1 = $num1 * $num2"
echo "The Multiplication is: " $num1
;;
"Div") let "num1 = $num1 / $num2"
echo "The Division is: " $num1
;;
*) echo "Not a valid option."
;;
esac
