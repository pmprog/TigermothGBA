#!/bin/bash
make clean && make -j4

if [ -f 2021.GBAJam.gba ]; then
    ./mGBA 2021.GBAJam.gba &
fi
