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
    ll n,m,t;
    string s;
    t =1;
    //cin>>t;
    while(t--)
    {
      cin>>s;
      ll c[26]={0};
      fo(i,s.size())
        {
          c[s[i]-65]++;
        }
      ll odd=0,x;
      fo(i,26)
      {
        if(c[i]&1)
         {
          x=i;
          odd++;
        }
      }
      if(odd>1)
        cout<<"NO SOLUTION";
      else
      {
        string s="";
        fo(i,26)
        {
          if(i==x)
            continue;
          ll times=c[i]/2;
          while(times--)
          {
            s+=(char)(i+65);
          }
        }
        string rev = s;
        reverse(rev.begin(),rev.end());
        fo(i,c[x])
            s+=((char)(x+65));
        s+=rev;
        cout<<s;    
      }
    }
    return 0;
}