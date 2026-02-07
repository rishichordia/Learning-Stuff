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
  ll n,m;
  cin>>n>>m;
  vll a(n+1,0);
  vll b(m+1,0);
  fo(i,n)
    cin>>a[i];
  fo(i,m)
    cin>>b[i];
  vector<vll> dp(n+1, vll(m+1,0));
  vector<vector<char>> dir(n+1,vector<char>(m+1,' '));
  for(int i =1;i<=n;i++)
  {
    for(int j = 1;j<=m;j++)
    {
      if(a[i-1]==b[j-1])
      {
        dp[i][j] = dp[i-1][j-1]+1;
        dir[i][j] = 'd';
      }
      else
      {
        if(dp[i][j-1]>dp[i-1][j])
          dir[i][j] = 'u';
        else dir[i][j] = 'l';
        dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
      }
    }
  }
  vector<ll> ans;
  ll cx = n,cy=m;
  while(cx>0 && cy>0)
  {
    if(dir[cx][cy]=='d')
    {
      ans.pb(a[cx-1]);
      cx--;
      cy--;
    }
    else if(dir[cx][cy]=='l')
    {
      cx--;
    }
    else if(dir[cx][cy]=='u')
    {
      cy--;
    }
  }
  reverse(ans.begin(),ans.end());
  cout<<dp[n][m]<<endl;
  fo(i,ans.size())
    cout<<ans[i]<<" ";

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