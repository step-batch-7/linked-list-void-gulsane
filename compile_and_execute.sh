mkdir -p bin
executable=$1

echo "compiling..."
gcc -c ./*.c
gcc -o ${executable} ./*.o
echo "commpiling done..."

mv ${executable} ./bin
./bin/${executable}
rm -rf *.o