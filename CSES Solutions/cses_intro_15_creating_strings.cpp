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
vector<string> ans;

void solve(char s[],string st,int n)
{
  if(st.size()==n)
    {
      ans.pb(st); 
      return;
    }
  fo(i,26)
  {
    if(s[i]>0)
    {
      s[i]--;
      string temp=st+(char)(i+97);
      solve(s,temp,n);
      s[i]++;
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
    t =1;
    //cin>>t;
    while(t--)
    {
      cin>>n;
      vll a(n,0);
      ll total=0;
      fo(i,n)
      {
        cin>>a[i];
        total+=a[i];
      }
      ll ans=LONG_MAX,curr,s,diff;
      fo(i,1<<n)
      {
        curr=0;
        fo(j,n)
        {
          if(i&(1<<j))
            curr=curr+a[j];
        }
        s=abs(total-2*curr);
        ans=min(ans,s);
      }
      cout<<ans;
    }
    return 0;
}