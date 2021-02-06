#!/bin/bash

case $# in
    0)
        echo "Argument is missing!"
        ;;
    *)
        for var in $* ; do
            ./analyseFichier.sh $var
        done
        ;;
esac
