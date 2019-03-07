#include<map>
#include<sstream>
#include<iostream>
using namespace std;

int main(){
    string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
    map<int, char> indexToKey;
    map<char, int> keyToIndex;
    for(int i=0;i<keyboard.length();i++){
        indexToKey[i] = keyboard[i];
        keyToIndex[keyboard[i]] = i;
    }
    string line;
    while(true){
        getline(cin, line);
        if(line == "") break;
        ostringstream ss;
        for(auto& x : line) {
            if(keyToIndex.count(x)){
                ss << indexToKey[keyToIndex[x] - 1];
            } else {
                ss << x;
            }
            
        }
        cout << ss.str() << endl;
    }
}