#!/bin/bash
make clean && make -j4

if [ -f 2021.GBAJam.gba ]; then
    export LD_LIBRARY_PATH=/opt/Qt/5.15.2/gcc_64/lib
    mgba-qt 2021.GBAJam.gba &
fi
