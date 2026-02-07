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

vector<vector<bool>> vis;
ll cnt=0;
vector<string>ans;
void dfs(int x,int y,string s,bool& f)
{
  if(f)
  return; 
  if(s.size()==48 && x==0 && y==6)
  {
    ans.pb(s);
   cnt++;
   if(cnt==88418)
    f=1; 
    return;
  }
  else if(s.size()==48)
    return;
  else if(x==0&&y==6)
    return;

  fo(i,4)
  {
    int ci=x+dirx[i];
    int cj=y+diry[i];
    if(f)
      break;
    if(ci<0||ci>=7||cj<0||cj>=7)
    {
      continue;
    }
    if(!vis[ci][cj])
    {
      vis[ci][cj]=1;
      dfs(ci,cj,s+mov[i],f);
      vis[ci][cj]=0;
    } 
  }
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
    ll n,t;
    string s;
    t = 1;
    //cin>>t;
    while(t--)
    {
      cin>>s;
      vis.assign(7,vector<bool>(7,0));
      vis[0][0]=1;
      bool f = 0;
      dfs(0,0,"",f);
      
      fo(i,ans.size())
      {
        cout<<ans[i]<<endl;
      } 
    }
  return 0;
}