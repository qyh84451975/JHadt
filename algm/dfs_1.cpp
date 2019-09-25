#include<iostream>
#include<string>
#define yes 1
#define no 0
using namespace std;
static int kind = 0;//可行的方案数 
static int H,W;
//判断是否可以在该位置放置砖块 
int IsOk(string abv, int w){
    if(w>W)
        return no;
    else if (w==W)
        return yes;
    return (abv[w]-'0')?no:yes;
}
//深搜 
void dfs(int h, int w, string above[]){
    if(h == (H+1)){   //搜索的出口，输出合适的方案 
        kind ++;
        for(int i=1;i<=H;i++)
            cout<<above[i]<<endl;
        cout<<"---------------"<<endl;
        return;
    }
    for(int i = 2; i <=3; i++){
        if(IsOk(above[h-1], w+i)){
            above[h][w+i] = '1';   //放置砖块，标记砖缝位置。 
            if((w+i)==W)
                dfs(h+1, 0, above);
            else 
                dfs(h, w+i, above);
            above[h][w+i] = '0';  //回溯，搜索另一条路径。 
        }
    }
    return;
}

int main(){
    cin>>W;
    cin>>H;
    string above[H+1];
    for(int i = 0; i <= H; i++){   //初始化字符串数组，用来记录砖缝位置。 
        above[i] = '1';
        for(int j = 1; j <= W; j++)
            above[i] += '0';
        }
    dfs(1, 0, above);
    cout<<kind<<endl;
}
