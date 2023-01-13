if [ -z $LD_LIBRARY_PATH ]
then
        export LD_LIBRARY_PATH=/usr/local/lib
else
        export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
fi

if [ -z $LIBRARY_PATH ]
then
        export LIBRARY_PATH=/usr/local/lib
else
        export LIBRARY_PATH=/usr/local/lib:$LIBRARY_PATH
fi
