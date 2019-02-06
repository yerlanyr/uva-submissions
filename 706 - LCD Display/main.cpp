#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>
using namespace std;
function<bool(char)> in(vector<char> xs){
    return [&xs](char x){ return any_of(xs.begin(), xs.end(), [x](char z) { return z == x; }); };
}
void line(function<bool(char)> pred, string n, int s){
    bool first = true;
    for(auto& letter: n){
        if(first) {
            cout <<  ' ';
            first = false;
        } else {
            cout << "  ";
        }
        for(int i=0;i<s;i++){
            cout << (pred(letter) ? ' ' : '-');
        }
        cout << ' ';
    }
    cout << endl;
}
void center(function<bool(char)> predLeft, function<bool(char)> predRight, string n, int s){
    for(int i=0;i<s;i++){
        bool first = true;
        for(auto& letter: n){
            if(first){
                first = false;
            } else {
                cout << " ";
            }
            cout << (predLeft(letter) ? ' ' : '|');
            for(int j=0;j<s;j++) cout << ' ';
            cout << (predRight(letter) ? ' ' : '|');
        }
        cout << endl;
    }
}
int main(){
    int s;
    string n;
    while(true){
        cin >> s >> n;
        if(s == 0) break;
        line(in({'1', '4'}), n, s);
        center(in({'1', '2', '3', '7'}), in({'5', '6'}), n, s);
        line(in({'0','1','7'}), n, s);
        center(in({'1','3','4','5','7','9'}), in({'2'}), n, s);
        line(in({'1','4','7'}), n, s);
        // separater between words.
        cout << endl;
    }
}