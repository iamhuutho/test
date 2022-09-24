#include<bits/stdc++.h>
using namespace std;
char* reverseNode(char* s){
    int n = 0;
    while(s[n] != '\0'){
        n++;
    }
    int i = 0;
    char *res;
    while(s[i] != '\0'){
        res[i] = s[n - i];
        i++;
    }
    return res;
}
int main(){
}