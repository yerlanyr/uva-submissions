#include<iostream>
#include<vector>
using namespace std;
int solve(vector<int> p, int n){
    vector<bool> days(n+1, false);
    for(int pi: p){
        for(int cur = 0; cur <= n; cur += pi){
            if(cur % 7 != 6 && cur % 7 != 0) {
                days[cur] = true;
            }
        }
    }
    int res = 0;
    for(int i=0;i<=n;i++){
        if(days[i]) res++;
    }
    return res;
}
int main(){
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        int n;
        cin >> n;
        int pn;
        cin >> pn;
        vector<int> p(pn);
        for(int j=0;j<pn;j++){
            cin >> p[j];
        }
        cout << solve(p, n) << endl;
    }
}