# C-Wheel-ArrayList
java's ArrayList of C version

compile command: 
gcc -c ArrayList.c // generate ArrayList.o
ar rcs ArrayList.a ArrayList.o // generate ArrayList.a
gcc ArrayListTest.c -static ArrayList.a -o ArrayListTest.exe // generate ArrayListTest.exe
