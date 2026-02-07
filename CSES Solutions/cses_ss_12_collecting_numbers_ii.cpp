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
 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,t,m,q;
    string s;
    t = 1;
    //cin>>t;
    while(t--)
    {
      cin>>n>>m;
      vll a(n,0);
      fo(i,n)
      {
        cin>>a[i];
      }
     unordered_map<ll,ll>ip; 
     ll j=0;
     for(int i=0;i<n;i++)
     {
        if(ip.find(a[i]-1)==ip.end())
            j++;
        ip[a[i]] = i;
     }
     vpll q(m,make_pair(0,0));
     fo(i,m)
     {
        ll l,r;
        cin>>l>>r;
        q[i].ff=l;
        q[i].ss=r;
     }
     fo(i,m)
     {
        ll l,r;
        ll curr = j;
        l = q[i].ff;
        r = q[i].ss;
        if(l>r)
        {
          swap(l,r);
        }
        ll cl=a[l-1],cr=a[r-1];
        if(abs(cl-cr)==1)
        {
          if(cr>cl)
          {
            curr++;
            if(cl!=1&&ip[cl-1]<ip[cr]&&ip[cl-1]>ip[cl])
              curr--;
            if(cr!=n&&ip[cr+1]>ip[cl]&&ip[cr+1]<ip[cr])
              curr--;
 
          }
          else
          {
            curr--;
            if(cl!=n&&ip[cl+1]<ip[cr]&&ip[cl+1]>ip[cl])
              curr++;
            if(cr!=1&&ip[cr-1]>ip[cl]&&ip[cr-1]<ip[cr])
              curr++;
          }
        }
        else
        {
            if(cl!=1&&ip[cl-1]<=ip[cr]&&ip[cl-1]>ip[cl])
              curr--;
            if(cr!=n&&ip[cr+1]>=ip[cl]&&ip[cr+1]<ip[cr])
              curr--;
            if(cl!=n&&ip[cl+1]<=ip[cr]&&ip[cl+1]>ip[cl])
              curr++;
            if(cr!=1&&ip[cr-1]>=ip[cl]&&ip[cr-1]<ip[cr])
              curr++;
        }
        swap(ip[cl],ip[cr]);
        swap(a[l-1],a[r-1]);
        cout<<curr<<endl;
        j=curr;
      }
    }
  return 0;
}