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
    string s="";
    t =1;
    //cin>>t;
    while(t--)
    {
      cin>>n;
      int c=0,i=n-1;
      while(c<pow(2,n))
      {
        s="";
        fo(i,n)
        {
          ll rem=c%((ll)(pow(2,i+2)));
          rem/=(pow(2,i));
          if(rem==0||rem==3)
          {
            s="0"+s;
          }
          else if(rem==1||rem==2)
          {
            s="1"+s;
          }
        }
        cout<<s<<endl;
        c++;
      }
    }
    return 0;
}