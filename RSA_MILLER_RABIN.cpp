#include<bits/stdc++.h>
using namespace std;
long long e,d,tot,temp[50],m[50],en[50];
char message[50];
long power(long a,long d,long n)
{
    if(d==0)
        return 1%n;
    int temp=power(a,d/2,n);
    if(d%2==0)
        return (temp*temp)%n;
    else
        return (a*temp*temp)%n;
}
bool miller_rabin(long d,long n)
{
    //int a=2+rand()%(n-3);
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<unsigned long>dis(2,n-2);
    long a=dis(gen);
    long x=power(a,d,n);
    if(x==1||x==n-1)
        return true;
    while(d!=n-1)
    {
        x=(x*x)%n;
        d*=2;
        if(x==1)
            return false;
        if(x==n-1)
        return true;
    }
    return false;
}

bool isPrime(long n,int p)
{
    if(n<=1||n==4)
        return false;
    if(n==2||n==3)
        return true;
    int d=n-1;
    while(d%2==0)
        d/=2;
    for(int i=0;i<p;i++)
    {
        if(miller_rabin(d,n)==false)
            return false;
    }
    return true;
}
long long cd(long long x)
{
    long k=1;
    while(1)
    {
        k+=tot;
        if(k%x==0)
            return (k/x);
    }
}
void encrypt(long long n)
{
    long pt,ct,key,k,len;
    key=e;
    len=strlen(message);
    long i=0;
    while(i!=len)
    {
        pt=m[i];
        pt=pt-96;
        k=1;
        for(int j=0;j<key;j++)
        {
            k*=pt;
            k%=n;
        }
        temp[i]=k;
        ct=k+96;
        en[i]=ct;
        i++;
    }
    en[i]=-1;
    cout<<"The encrypted message is: ";
    for(int h=0;en[h]!=-1;h++)
        printf("%c",en[h]);
    cout<<endl;
}
void decrypt(long long n)
{
    long pt,ct,key,k;
    int i=0;
    key=d;
    while(en[i]!=-1)
    {
        ct=temp[i];
        k=1;
        for(int j=0;j<key;j++)
        {
            k*=ct;
            k%=n;
        }
        pt=k+96;
        m[i]=pt;
        i++;
    }
    m[i]=-1;
    cout<<"The decrypted message is: ";
    for(int h=0;m[h]!=-1;h++)
        printf("%c",m[h]);
    cout<<endl;
}
void rsa(long p,long q,int k)
{
    tot=(p-1)*(q-1);
    for(long long i=2;i<tot;i++)
    {
        if(tot%i==0)
            continue;
        bool flag=isPrime(i,k);
        if(flag&& i!=p && i!=q)
        {
            e=i;
            long f=cd(e);
            if(f>0)
            {
                d=f;
                break;
            }
        }
    }
}
int main()
{
    int k=15;
    cout<<"START"<<endl;
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<unsigned long>dis;
    int t=0;
    unsigned long p[2];
    cout<<"Enter message."<<endl;
    scanf("%s",message);
    clock_t start=clock();
    while(t!=2)
    {
        unsigned long l=dis(gen);
        if(isPrime(l,k))
        {
            p[t]=l;
            t++;
        }
    }
    rsa(p[0],p[1],k);
    cout<<"Encryption Key: "<<e<<endl;
    cout<<"Decryption key: "<<d<<endl;
    for(int j=0;message[j]!=NULL;j++)
    {
        m[j]=message[j];
    }
    long long f=p[0]*p[1];
    encrypt(f);
    decrypt(f);
    cout<<"END"<<endl<<endl;
    cout<<"TIME TAKEN: "<<(double)(clock()-start)/CLOCKS_PER_SEC;
    return 0;
}
