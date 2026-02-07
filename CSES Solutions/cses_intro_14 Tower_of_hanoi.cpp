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

vector<pll> steps;
vector<pll> prev_steps;

pll transform(pll inp,int l,int m,int r)
{
  pll ans={0,0};
  if(inp.ff==1)
    ans.ff=l;
  else if(inp.ff==2)
    ans.ff=m;
  else if(inp.ff==3)
    ans.ff=r;

  if(inp.ss==1)
    ans.ss =l;
  else if(inp.ss==2)
    ans.ss=m;
  else if(inp.ss==3)
    ans.ss=r;
  return ans;
}
void get_h(int l,int m,int r)
{
  for(ll i=0;i<prev_steps.size();i++)
  {
    pll mid = transform(prev_steps[i],l,m,r);
    //cout<<mid.ff<<" "<<mid.ss<<endl;
    steps.pb(mid);
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
    ll n,m,t;
    t =1;
    //cin>>t;
    while(t--)
    {
      cin>>n;
      int c=2;
      prev_steps.pb({1,3});
      while(c<=n)
      {
        get_h(1,3,2);
        steps.pb({1,3});
        get_h(2,1,3);
        prev_steps=steps;
        steps.clear();
        c++;
      }
      cout<<pow(2,n)-1<<endl;
      fo(i,prev_steps.size())
      {
        cout<<prev_steps[i].ff<<" "<<prev_steps[i].ss<<endl;
      }
    }
    return 0;
}