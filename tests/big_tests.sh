for i in 1 2 3 4 5 6
do
    echo $i
done

f()
{
    x=4
    echo $1
}

f Bonsoir

echo $1
echo $1 $x