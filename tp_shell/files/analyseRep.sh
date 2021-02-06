#!/bin/bash

if test $# -eq 1
then
    cmd="ls $1"
    res=$(eval "$cmd")
    for var in $res ; do
        ./analyseFichier.sh $var
    done
fi
if test $# -lt 1
then
    echo "One parameter is missing!"
    echo "usage: ./analyseRep.sh <dir>"
fi
if test $# -gt 1
then
    echo "Too much parameters!"
    echo "usage: ./analyseRep.sh <dir>"
fi
