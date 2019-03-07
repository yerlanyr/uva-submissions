
#include<algorithm>
#include<iostream>
using namespace std;
int main(){
    while(true){
        string a,b;
        getline(cin, a);
        getline(cin, b);
        if(a == "" && b == "") break;
        
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            int i = 0;
            int j = 0;
            while(i < a.length() && j < b.length()){
                if(a[i] < b[j]){
                    i++;
                } else if(a[i] > b[j]){
                    j++;
                } else {
                    cout << a[i];
                    i++;
                    j++;
                }
            }
            cout << endl;
        
    }
}