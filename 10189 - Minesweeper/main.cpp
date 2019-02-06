#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
	int m, n;
	string line;
	int k = 1;
	while(true){
		cin >> m >> n;
		if(m == 0 && n == 0) break;
		vector<vector<char> > v(m, vector<char>());
		for(int i=0;i<m;i++){
			cin >> line;
			copy(line.begin(), line.end(), back_inserter(v[i]));
		}
		if(k != 1) cout << endl;
		cout << "Field #" << k++ << ":"<< endl;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(v[i][j] != '*') {
					int cnt = 0;
					for(int wi = max(0, i - 1); wi <= min(m - 1, i + 1); wi++){
						for(int wj = max(0, j - 1); wj <= min(n - 1, j + 1); wj++){
							if(v[wi][wj] == '*') cnt ++;
						}
					}
					v[i][j] = (char)((int)'0' + cnt);
				}
				cout << v[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}
