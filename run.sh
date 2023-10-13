#!/bin/bash

rm -rf build && mkdir build && cd build && cmake .. && make

./matching ../resources/olympus/pic.0343.jpg ../resources/olympus 11 findCenterSmall &
wait