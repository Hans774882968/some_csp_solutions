#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
const int SZ = 10000 + 5;

int n;

struct Node{
    char op;int to;
};queue<Node> q[SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

int update(){
    int snum = 0;
    re_(i,0,n){
        if(q[i].empty()) continue;
        Node u = q[i].front();
        if(u.op == 'S'){
            int v = u.to;
            if(q[v].empty()) return 0;
            Node nv = q[v].front();
            if(nv.op == 'R' && nv.to == i){
                q[i].pop();
                q[v].pop();
                snum += 2;
            }
        }
    }
    return snum;
}

bool suc(){
    re_(i,0,n) if(!q[i].empty()) return false;
    return true;
}

int main(int argc, char** argv) {
    int T;read(T);read(n);
    while(T--){
        re_(i,0,n) while(!q[i].empty()) q[i].pop();
        re_(i,0,n){
            string s;getline(cin,s);
            re_(j,0,s.size()){
                char op = s[j++];int v = 0;
                for(;j < s.size() && s[j] != ' ';++j) v = 10 * v + s[j] - '0';
                q[i].push({op,v});
            }
        }
        while(1){
            int snum = update();
            if(!snum) break;
        }
        cout << !suc() << endl;
    }
    return 0;
}