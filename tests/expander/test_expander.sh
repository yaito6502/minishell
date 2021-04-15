#!/bin/bash

./test "'$?',$?,\"$?\",\"world's end\",'$HOME'aaaa\"$TEST\",$PWD"
./test "\"'$?$?'\",'$?',$??,\"world's end\",'$HOME'aaaa\"$TEST\",$PWD"
./test "\"$?\"$?\"$?\",'$?'$?'$?','','\"\"'"
./test "\"\'$?\"\'\"$?\', $??, $$$$$$$"
./test "$$$$$$"
./test "$$$$$$$"