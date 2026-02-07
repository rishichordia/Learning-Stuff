#include <iostream>
#include <bits/stdc++.h>
#include <string>
typedef long long int ll;
 
#define deb(x) cout << #x << " is " << x << "\n"
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << "\n"
#define fo(i,n) for(ll i=0;i<n;i++)
#define rep(i,j,n) for(ll i=j;i<n;i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pll pair<ll,ll>
#define vll vector<ll>
#define vpll vector<pll>
 
const ll mod = 1e9+7;
const ll nmax = 2e5 + 5;
const ll cnmax = 1e5+1;
using namespace std;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,t,c,dig,num,x,num_dig,rem=0;
    string s;
    t =1;
    cin>>t;
    while(t--)
    {
      cin>>n;
      c=1;
      ll curr=9;
      dig=1;
      x=n;
      while(x>curr)
      {
        x-=curr;
        c++;
        curr=9*pow(10,c-1)*c;
        dig*=10;
      }
      num=dig+x/c-1;
      num_dig=c-1;
      if(x%c!=0)
      {
        num++;
        num_dig=x%c-1;
      }
      string nm = to_string(num);
      cout<<nm[num_dig]<<endl;
    }
  return 0;
}