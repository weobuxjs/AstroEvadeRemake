#include<math.h>
#include<vector>
int pow(int a,int b)
{
    int ketqua=1;
    for(int i=1;i<=b;i++)
    {
        ketqua*=a;
    }
    return ketqua;
}
int GetChuSo(int n)
{
    int x=n;
    int dem=0;
    if(x==0) return 1;
    while(x!=0)
    {
        dem++;
        x/=10;
    }
    
    return dem;
}
/*float CaculateDistane(vector<int>a,vector<int>b)
{
    return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]));
}*/