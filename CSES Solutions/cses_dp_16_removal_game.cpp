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
  ll n,sum=0;
  cin>>n;
  vector<ll> arr(n,0);
  fo(i,n)
  {
    cin>>arr[i];
    sum+=arr[i];
  }
  
  vector<vector<ll>> dp(n,vector<ll>(n,0));
  for(ll i=0;i<n;i++)
    dp[i][i] = arr[i];
  
  for(int sz = 2;sz<=n;sz++)
  {
    for(int i =0;i+sz-1<n;i++)
    {
      ll j = i+sz-1;
      dp[i][j] = max(arr[i]-dp[i+1][j],arr[j]-dp[i][j-1]);
    }
  }
  ll ans = (dp[0][n-1]+sum)/2;
  cout<<ans;
}
 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll t = 1;
    //cin>>t;
    while(t--)
    {
      solve();
    }
  return 0;
}