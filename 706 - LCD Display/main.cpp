#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>
using namespace std;
function<bool(char)> in(vector<char> xs){
    return [&xs](char x){ return any_of(xs.begin(), xs.end(), [x](char z) { return z == x; }); };
}
int main(){
    int s;
    string n;
    while(true){
        cin >> s >> n;
        if(s == 0) break;
        auto liner = [&](function<bool(char)> pred){
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
        };
        auto centerPieceWriter = [&](function<bool(char)> predLeft, function<bool(char)> predRight){
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
        };
        liner(in({'1', '4'}));
        centerPieceWriter(
            in({'1', '2', '3', '7'}),
            in({'5', '6'})
        );
        // central piece
        liner(in({'0','1','7'}));
        //liner([](char x) { return x == '7' || x == '1' || x == '0'; });
        // bottom part
        centerPieceWriter(
            in({'1','3','4','5','7','9'}),
            in({'2'})
        );
        // bottom line
        liner([](char x) { return x == '1' || x == '4' || x == '7'; });
        cout << endl;
    }
}