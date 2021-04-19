#include <iostream>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;
int a[200][200],b[200][200],ans[200][200],ans2[200][200],m,n,k;
int arr[200*200];
unordered_map<int,pair<int,int>> thread_id;
void* mul(void *arg){
            int index=*(int*)arg;
            auto x=thread_id[index];
            for(int i=0;i<m;++i)
            ans[x.first][x.second]+=a[x.first][i]*b[i][x.second];
}
void* mul2(void *arg){
            int index=*(int*)arg;
            for(int i=0;i<k;++i)
            for(int j=0;j<m;++j)
            ans2[index][i]+=a[index][j]*b[j][i];
}
void init(){
    for(int i=0;i<100*100;++i)arr[i]=i;
    }
int main()
{
    init();
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin>>n>>m;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            cin>>a[i][j];
    cin>>m>>k;
    for(int i=0;i<m;++i)
        for(int j=0;j<k;++j)
            cin>>b[i][j];
    clock_t st=clock();
    pthread_t p[200][200];
    int cnt=0;
    for(int i=0;i<n;++i)
    for(int j=0;j<k;++j){
        thread_id[cnt++]={i,j};
        pthread_create(&p[i][j],NULL,&mul,&arr[cnt]);
    }
	for(int i = 0 ;i < n; i++){
		for(int j= 0 ; j < k ; j++){
			pthread_join(p[i][j], NULL);
		}
	}
    for(int i=0;i<n;++i){
        for(int j=0;j<k;++j)
            cout<<ans[i][j]<<" ";
            puts("");
    }
    clock_t en=clock();
    cout<<"END1\t"<<(double)(en-st)/CLOCKS_PER_SEC<<"s\n";
    // 2nd tare2a
    st=clock();
    pthread_t p2[100];
    cnt=0;
    for(int i=0;i<n;++i)
    pthread_create(&p2[i],NULL,&mul2,&arr[i]);
    for(int i =0 ; i < n ; i++)
    pthread_join(p2[i],NULL);
    for(int i=0;i<n;++i){
        for(int j=0;j<k;++j)
            cout<<ans2[i][j]<<" ";
            puts("");
    }
    en=clock();
    cout<<"END2\t"<<(double)(en-st)/CLOCKS_PER_SEC<<"s\n";
}
