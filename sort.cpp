#include <iostream>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;
int arr[(int)1e5+7];
int inf = 0x3f3f3f3f;
std::mutex mtx;
void merge(int low,int mid ,int high){
    int sizel=1+mid-low,sizer=high-mid;
    int *left = (int*)malloc(sizel*sizeof(int));
    int *right = (int*)malloc(sizer*sizeof(int));
    for(int i=0;i<sizel;++i)left[i]=arr[i+low];
    for(int i=0;i<sizer;++i)right[i]=arr[mid+1+i];
    int cnt=low,i=0,j=0;
    while(i<sizel&&j<sizer)
        if(left[i]<right[j])arr[cnt++]=left[i++];
        else arr[cnt++]=right[j++];
    while(i<sizel)arr[cnt++]=left[i++];
    while(j<sizer)arr[cnt++]=right[j++];
}
void* mergesort(void *arg){
    pair<int,int> lr = *(pair<int,int>*)arg;
    int mid=(lr.first+lr.second)>>1;
    pthread_t p1,p2;
    pair<int,int> pair1={lr.first,mid},pair2={mid+1,lr.second};
    if(lr.first<lr.second){
        pthread_create(&p1,NULL,&mergesort,&pair1);
        pthread_create(&p2,NULL,&mergesort,&pair2);
        pthread_join(p1,NULL);
        pthread_join(p2,NULL);
        merge(lr.first,mid,lr.second);
    }
}
int main()
{
    memset(arr,inf,sizeof(arr));
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    for(int i=0;i<n;++i)cin>>arr[i];
    clock_t st=clock();
    pthread_t p1,p2;
    pair<int,int> pair1={0,n/2},pair2{n/2+1,n};
    pthread_create(&p1,NULL,&mergesort,&pair1);
    pthread_create(&p2,NULL,&mergesort,&pair2);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    merge(0,n/2,n);
    clock_t en=clock();
    for(int i=0;i<n;++i)cout<<arr[i]<<" ";
    cout<<"\nTime is "<<(double)(en-st)/CLOCKS_PER_SEC<<"S.\n";
}
