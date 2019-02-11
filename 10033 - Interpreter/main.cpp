#include <iostream>
#include <vector>
using namespace std;
int execute(vector<string> ram){
    
    if(ram.size() == 0) return 0;
    int currentCommand = 0;
    int numberOfCommandsExecuted = 0;
    vector<int> regs(10, 0);
    /*cout << "Commands: \n";*/
    while(true){
        //cout << ram[currentCommand] << endl;
        vector<int> cmd(3, 0);
        for(int i=0;i<3;i++) cmd[i] = ram[currentCommand][i] - '0';
        bool halt = false;
        bool debug = false;
        numberOfCommandsExecuted++;
        currentCommand++;
        switch(cmd[0]){
            case 1 : {
                if(cmd[0] == 1)
                    halt = true;
                break;
            }
            case 2 : {
                regs[cmd[1]] = cmd[2];
                break;
            }
            case 3 : {
                regs[cmd[1]] = (regs[cmd[1]] + cmd[2]) % 1000;
                break;
            }
            case 4 : {
                regs[cmd[1]] = (regs[cmd[1]] * cmd[2]) % 1000;
                break;
            }
            case 5 : {
                regs[cmd[1]] = regs[cmd[2]];
                break;
            }
            case 6 : {
                regs[cmd[1]] = (regs[cmd[1]] + regs[cmd[2]]) % 1000;
                break;
            }
            case 7 : {
                regs[cmd[1]] = (regs[cmd[1]] * regs[cmd[2]]) % 1000;
                break;
            }
            case 8 : {
                regs[cmd[1]] = stoi(ram[cmd[2]]);
                break;
            }
            case 9 : {
                ram[regs[cmd[2]]] = to_string(regs[cmd[1]]);
                ram[regs[cmd[2]]].insert(ram[regs[cmd[2]]].begin(), 3 - ram[regs[cmd[2]]].length(), '0');
                break;
            }
            case 0 : {
                if(regs[cmd[2]] != 0) {
                    currentCommand = regs[cmd[1]];
                }
                break;
            }
        }

        // cout << "currentCommand " << currentCommand << endl;
        // cout << "Regs" << endl; 
        // for(int i=0;i<regs.size();i++){
        //     cout << regs[i] << endl;
        // }
        // cin.get();
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
        vector<string> ram(1000, "000");
        int k = 0;
        while(true){
            string line;
            getline(cin, line);
            if(line == "") break;
            ram[k++] = line;
        }
        //cout << "commands" << endl;
        // int z = 0;
        // for(string line : ram){
        //     cout << line << endl;
        //     z++;
        //     if(z == 20) break;
        // }
        if(!first) { cout << endl; }
        cout << execute(ram) << endl;
        first = false;
    }
}