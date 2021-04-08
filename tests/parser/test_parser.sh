#!/bin/bash

./test "ls >>"
./test "ls >> ;"
./test "ls >>> file1"
./test "ls >>>> file1"
./test "export | grep TEST"
./test "ls '>>outfile'"
./test "echo hello > file1 > file2 world ; cat < file2 | head -n 1 | wc"