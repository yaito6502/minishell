#!/bin/bash

<< COMMENTOUT

#export
./test
#export TEST
./test TEST
#export TEST=1
./test TEST=1
#export TEST=first TEST=second TEST=third
./test TEST=first TEST=second TEST=third
#export FIRST=1 SECOND=2 THIRD=3
./test FIRST=1 SECOND=2 THIRD=3

COMMENTOUT

#export
./test "export"
#export TEST
./test "export,TEST"
#export TEST=1
./test "export,TEST=1"
#export TEST=first TEST=second TEST=third
./test "export,TEST=first TEST=second TEST=third"
#export FIRST=1 SECOND=2 THIRD=3
./test "export,FIRST=1 SECOND=2 THIRD=3"
