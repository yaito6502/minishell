#!/bin/bash

# 必要に応じて自由にテストケースを追加してください

#　リダイレクト先の有無
./test "ls >>"
./test "ls >> ;"

#　リダイレクションマークの個数
./test "ls >>> file1"
./test "ls >>>> file1"
./test "ls << file1"
./test "ls <<< file1"

#　ノーマルケース
./test "export | grep TEST"
./test "echo hello > file1 > file2 world ; cat < file2 | head -n 1 | wc"

#　正常なリダイレクション
./test "ls 2>outfile"
./test "ls 2>>outfile"
./test "ls <infile"

# クオートと区切り文字
./test "export '| grep TEST'"
./test "echo hello \"; sleep 10\""

# クオートとリダイレクション
./test "ls '2>outfile"
./test "ls 2>outfile'"
./test "ls '2>outfile'"
./test "ls \"2>outfile"
./test "ls 2>outfile\""
./test "ls \"2>outfile\""