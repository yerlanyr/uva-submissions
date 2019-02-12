#include <iostream>
#include <vector>
using namespace std;
int execute(vector<int> ram){
    if(ram.size() == 0) return 0;
    int ramIndex = 0;
    int numberOfCommandsExecuted = 0;
    vector<int> regs(10, 0);
    while(true){
        int c = ram[ramIndex] / 100;
        int d = ram[ramIndex] / 10 % 10;
        int n = ram[ramIndex] % 10;
        bool halt = false;
        bool debug = false;
        numberOfCommandsExecuted++;
        ramIndex++;
        switch(c){
            case 1 : {
                if(c == 1)
                    halt = true;
                break;
            }
            case 2 : {
                regs[d] = n;
                break;
            }
            case 3 : {
                regs[d] += n;
                regs[d] %= 1000;
                break;
            }
            case 4 : {
                regs[d] *= n;
                regs[d] %= 1000;
                break;
            }
            case 5 : {
                regs[d] = regs[n];
                break;
            }
            case 6 : {
                regs[d] += regs[n];
                regs[d] %= 1000;
                break;
            }
            case 7 : {
                regs[d] *= regs[n];
                regs[d] %= 1000;
                break;
            }
            case 8 : {
                regs[d] = ram[regs[n]];
                break;
            }
            case 9 : {
                ram[regs[n]] = regs[d];
                break;
            }
            case 0 : {
                if(regs[n] != 0) {
                    ramIndex = regs[d];
                }
                break;
            }
        }
        if(halt) break;
    }
    return numberOfCommandsExecuted;
}
int main(){
    int numberOfTests;
    cin >> numberOfTests;
    cin.get();            
    cin.ignore();
    bool first = true;
    for(int indexOfTest = 0; indexOfTest < numberOfTests; indexOfTest++){
        vector<int> ram(1000, 0);
        int k = 0;
        while(true){
            string line;
            getline(cin, line);
            if(line == "") break;
            ram[k++] = stoi(line, nullptr, 10);
        }
        if(!first) { cout << endl; }
        int result = execute(ram);
        cout << result << endl;
        first = false;
    }
}