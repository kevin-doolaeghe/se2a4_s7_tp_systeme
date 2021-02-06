#!/bin/bash

if test $# -eq 1
then
    if test -d $1
    then
        echo "$1 is a directory."
    fi
    if test -f $1
        then echo "$1 is a file."
    fi
    if test -e $1
        then :
        else echo "$1 does not exist!"
    fi
fi
if test $# -lt 1
then
    echo "One parameter is missing!"
    echo "usage: ./analyseFichier.sh <param>"
fi
if test $# -gt 1
then
    echo "Too much parameters!"
    echo "usage: ./analyseFichier.sh <param>"
fi
