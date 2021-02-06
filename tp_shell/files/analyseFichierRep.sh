#!/bin/bash

if test $# -eq 2
then
    var=$2$1
    ./analyseFichier.sh $var
fi
if test $# -lt 2
then
    echo "One parameter is missing!"
    echo "usage: ./analyseFichierRep.sh <param> <dir>"
fi
if test $# -gt 2
then
    echo "Too much parameters!"
    echo "usage: ./analyseFichierRep.sh <param> <dir>"
fi
