This repo is effort to solve problems described in: Programming challenges The complete guide.
# g++ -std=c++11 -ggdb main.cpp -o main.exe
To build.
# main.exe > output.txt
To generate an output.
# g++ -std=c++11 -ggdb main.cpp -o main.exe && main.exe
To build and run.
# g++ -std=c++11 -ggdb main.cpp -o main.exe && main.exe > output.txt
To build and run and generate an output.
# gdb main.exe
To debug program.
# g++ -std=c++11 -ggdb main.cpp -o main.exe && main.exe < input.txt > output.txt && FC output.txt expected.txt
To test.