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
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,1,0,-1};
const char mov[4]={'R','U','L','D'};
using namespace std;
 
void solve()
{
  ll n,x;
  cin>>n>>x;
  vll a(n,0);
  fo(i,n)
    cin>>a[i];

  unordered_map<ll,pll> hash;
  fo(i,n-1)
    for(ll j=i+1;j<n;j++)
      hash[a[i]+a[j]]={i,j};

  fo(i,n-1)
  {
    for(ll j=i+1;j<n;j++)
    {
      ll sum = a[i]+a[j];
      if(hash.find(x-sum)!=hash.end())
      {
        auto t = hash[x-sum];
        if(t.ff!=i&&t.ff!=j&&t.ss!=i&&t.ss!=j)
        {
          cout<<t.ff+1<<" "<<t.ss+1<<" "<<i+1<<" "<<j+1<<" "<<endl;
          return;
        }   
      }
    }
  }
  cout<<"IMPOSSIBLE\n";
}
 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL)  ;
    ll t = 1;
    //cin>>t;
    while(t--)
    {
      solve();
    }
  return 0;
}