diff <(./test) <(echo "false")
diff <(./test "" value) <(echo "false")
diff <(./test 1 1) <(echo "false")
diff <(./test key) <(echo "key=")
diff <(./test key value) <(echo "key=value")
diff <(./test KEY value) <(echo "KEY=value")
diff <(./test key VALUE) <(echo "key=VALUE")
diff <(./test KEY VALUE) <(echo "KEY=VALUE")
diff <(./test key_11 test) <(echo "key_11=test")