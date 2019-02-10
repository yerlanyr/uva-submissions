#include<map>
#include<iostream>
#include<tuple>
#include<utility>
#include<vector>
using namespace std;

pair<int,int> find(char figure, char board[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j] == figure) return make_pair(i,j);
        }
    }
    return make_pair(0,0);
}

int main(){
    int gameNumber = 1;
    char board[8][8] = {0};
    while(true){
        string line;
        bool isLast = true;
        for(int i=0;i<8;i++) {
            getline(cin, line);
            for(int j=0;j<8;j++){
                board[i][j] = line[j];
                if(board[i][j] != '.') isLast = false;
            }
        }
        if(isLast) break;
        else getline(cin, line);
        // array of items where we show what is hit by which 1b 
        // is hit by black 10b hit by white 11b by both.
        int hit[8][8] = {0};
        auto project = [&hit](int i,int j,int v){
            if(i >= 0 && i < 8 && j >= 0 && j < 8){
                hit[i][j] |= v;
            }
        };
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                switch(board[i][j]){
                    case 'p': {
                        project(i+1, j+1, 1);
                        project(i+1, j-1, 1);
                        break;
                    }
                    case 'P': {
                        project(i-1, j+1, 2);
                        project(i-1, j-1, 2);
                        break;
                    }
                    case 'k': 
                    case 'K': {
                        for(int k=i-1;k<=i+1;k++){
                            for(int p=j-1;p<=j+1;p++){
                                if(k == i && p == j) continue;
                                project(k, p, board[i][j] == 'k' ? 1 : 2);
                            }
                        }
                        break;
                    }
                    case 'n':
                    case 'N':
                    {
                        int k[] = {-1, 1};
                        for(auto l: k){
                            for(auto m: k){
                                auto val = board[i][j] == 'n' ? 1 : 2;
                                project(i+1*l, j+2*m, val);
                                project(i+2*l, j+1*m, val);
                            }
                        }
                        break;
                    }
                    case 'R':
                    case 'r':
                    case 'Q':
                    case 'q':
                    {
                        int v = board[i][j] == 'r' || board[i][j] == 'q' ? 1 : 2;
                        for(int l = j - 1; l >= 0; l--){
                            project(i, l, v);
                            if(board[i][l] != '.') break;
                        }
                        for(int r = j + 1; r < 8; r++){
                            project(i,r, v);
                            if(board[i][r] != '.') break;
                        }
                        for(int l = i - 1; l >= 0; l--){
                            project(l, j, v);
                            if(board[l][j] != '.') break;
                        }
                        for(int l = i + 1; l < 8; l++){
                            project(l, j, v);
                            if(board[l][j] != '.') break;
                        }
                        if(board[i][j] == 'R') break;
                        if(board[i][j] == 'r') break;
                    }
                    case 'B':
                    case 'b':
                    {
                        int d[] = {-1, 1};
                        int v = board[i][j] == 'b' || board[i][j] == 'q' ? 1 : 2;
                        for(auto d1: d){
                            for(auto d2:d){
                                bool exitCycle = false;
                                for(int k = i+d1, l = j+d2; !exitCycle && k >= 0 && k < 8 && l >= 0 && l < 8 ; k+= d1, l+= d2){
                                    project(k,l,v);
                                    if(board[k][l] != '.') { exitCycle = true; }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        auto blackKing = find('k', board);
        auto whiteKing = find('K', board);
        
        if(hit[whiteKing.first][whiteKing.second] & 1) cout << "Game #" << gameNumber++ <<": white king is in check." << endl;
        else
        if(hit[blackKing.first][blackKing.second] & 2) cout << "Game #" << gameNumber++ <<": black king is in check." << endl; 
        else cout << "Game #" << gameNumber++ <<": no king is in check." << endl;
    }
    return 0;
}