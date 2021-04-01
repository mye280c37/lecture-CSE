echo "working directory:"
read path

if [ -n "$path" ]
then
    cd "$path"
    if [ $? -ne 0 ]
    then
        echo "can not access such directory"
	    exit 0
    fi
fi

for i in *
do
    if [ -f $i ]
    then
        mv $i `echo $i | tr '([a-z])([A-Z])' '([A-Z])([a-z])'` 
    fi

done

