swag=f
f()
{
    echo $1
}
$swag hello
exit
echo second
echo third >& 1 cat
echo fourth >| sixth
echo fifth 1> sixth
cat sixth
echo seventh

echo ****Sixth****
cat < echo sixth
echo ****Now is****
iiii="nineth"
je="sixth"
echo ${iiii} >> $je
cat < echo sixth
rm sixth
exit 55