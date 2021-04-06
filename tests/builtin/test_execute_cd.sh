cd ../../minishell
make execute_cd
echo ""
./test
echo ""
echo "unset HOME"
unset HOME
echo ""
./test
echo ""
echo "export HOME=/Users/yamato"
export HOME=/Users/yamato
echo ""
echo "export CDPATH=srcs/:tests"
export CDPATH=srcs/:tests
echo ""
./test execute
echo ""
echo "unset CDPATH"
unset CDPATH
./test execute
echo ""
./test ~
echo ""
./test ~/Desktop