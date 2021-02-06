#!/bin/bash

NB_FILES=0
NB_DIR=0

case $# in
    0)
        echo "One parameter is missing!"
        echo "usage: ./compteRep.sh <dir>"
        ;;
    1)
        cmd="ls"
        res=$(eval "$cmd")
        for i in $res ; do
            if [ -f $i ]
            then
                let NB_FILES++
            else
                $NB_DIR='expr $NB_DIR + 1'
            fi
        done
        echo "$1 has $NB_FILES files and $NB_DIR folders."
        ;;
    *)
        echo "Too much parameters!"
        echo "usage: ./compteRep.sh <dir>"
        ;;
esac
