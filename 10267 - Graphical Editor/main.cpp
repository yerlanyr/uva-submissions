#include<iostream>
#include<vector>
#include<sstream>
#include<utility>
#include<set>
#include<stack>
using namespace std;
int main(){
    vector<vector<char> > pano;
    int m,n;

    while(true){
    
        string command;
        getline(cin, command);
        char type = command[0];
        istringstream iss(command);
        
        int x,y,x1,x2,y1,y2;
        char c;
    
        switch(type){
            case 'I': 
                iss >> type >> m >> n;
                pano.assign(n, vector<char>(m, 'O'));
            break;
            case 'C': 
                pano.assign(n, vector<char>(m, 'O'));
            break;
            case 'L': 
                iss >> type >> x >> y >> c;
                pano[y - 1][x - 1] = c;
            break;
            case 'V': 
                iss >> type >> x >> y1 >> y2 >> c;
                for(int y = min(y1,y2)-1; y<max(y1,y2); y++) pano[y][x-1] = c;
            break;
            case 'H': 
                iss >> type >> x1 >> x2 >> y >> c;
                for(int x = min(x1,x2)-1; x<max(x1,x2); x++) pano[y-1][x] = c;
            break;
            case 'K': 
                iss >> type >> x1 >> y1 >> x2 >> y2 >> c;
                for(int x=min(x1,x2)-1;x <max(x1,x2);x++)
                    for(int y=min(y1,y2)-1;y<max(y1,y2);y++)
                        pano[y][x] = c;
            break;
            case 'F': {
                // DFS
                iss >> type >> x >> y >> c;
                stack<pair<int,int> > s;
                s.push(make_pair(y-1,x-1));
                set<pair<int,int> > visited;
                char indicatorColor = pano[y-1][x-1];
                while(!s.empty()){
                    // analyze the s.
                    pair<int,int> current = s.top();
                    s.pop();
                    if(visited.count(current)) continue;
                    visited.insert(current);
                    // now we iterate all that adjucent skipping that the same color or the current one.
                    for(y=max(0, current.first - 1); y <= min(current.first + 1, n - 1); y++){
                        for(x = max(0, current.second - 1); x <= min(current.second + 1, m - 1); x++){
                            if(pano[y][x] == indicatorColor && !visited.count(make_pair(y,x))){
                                s.push(make_pair(y,x));
                            }
                        }
                    }
                }
                // we have at the end all that has been visited and had the same color so we iterate on them
                for(auto& current : visited){
                    pano[current.first][current.second] = c;
                }
            break;
            }
            case 'S':{
                cout << command.substr(2, command.length() - 2) << endl;
                for(y=0;y<n;y++){
                    for(x=0;x<m;x++){
                        cout << pano[y][x];
                    }
                    cout << endl;
                }
                break;
            }
            case 'X': 
                return 0;
            break;
        }
    }    
}