#! /usr/bin/bash

CLANG=/usr/bin/clang++
GPP=/usr/bin/g++

OUT_FILE=server.out
FLAGS="--std=c++17 -pipe -lpthread"

if test -f "$CLANG"
then
	echo "Clang доступен..."
	$CLANG $FLAGS *.cpp -o $OUT_FILE

	echo "Проверьте присутствие исполняемого файла $OUT_FILE"
	echo ""
elif test -f "$GPP"
then
	echo "g++ доступен..."
	$GPP $FLAGS *.cpp -o $OUT_FILE

	echo "Проверьте присутствие исполняемого файла $OUT_FILE"
	echo ""
else
	if [[ -z "$1" ]] # Если $1 не задан или пуст
	then
		echo ""
		echo "Не найдены компиляторы! Укажите путь к компилятору:"
		echo "$ ./build.sh /путь/к/компилятору"
		echo ""
	else
		$1 $FLAGS *.cpp -o $OUT_FILE
	fi
fi

