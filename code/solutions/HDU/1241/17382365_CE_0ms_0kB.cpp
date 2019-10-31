int main(){
    while(cin>>n>>m){
        if(n==0)break;
        for(int i=1;i<=n;i++){
                cin>>game[i];
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(game[i][j]=='@'){
                    dfs(i,j);
                    ans++;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
