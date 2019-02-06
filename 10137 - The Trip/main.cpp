#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main(){
    double n;
    while(true){
        cin >> n;
        if(n == 0) break;
        vector<double> v(n);
        double sum = 0;
        for(int i=0;i<n;i++){ cin >> v[i]; sum += v[i]; }
        double average = sum / n;
        double deviation = 0;
        double upperAverage = ceil(average * 100) / 100;
        double lowerAverage = floor(average * 100) / 100;
        double toTake = 0;
        double toPay = 0;
        for(int i=0;i<n;i++){
            if(v[i] > upperAverage){
                toTake += v[i] - upperAverage;
            } else if(v[i] < lowerAverage) {
                toPay += lowerAverage - v[i];
            }
        }
        printf("$%.2f\n", round(max(toTake, toPay)*100) / 100);
    }
}