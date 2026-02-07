#include<iostream>
#include<bits/stdc++.h>
 
typedef long long int ll;
 
#define vi vector<int>
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define pll pair<ll,ll>
#define mk make_pair
#define ff first
#define ss second
#define deb(x) cout<<#x<<" is "<<i<<"\n"
#define fo(i,n) for(ll i=0;i<n;i++)
 
using namespace std;
ll mod = 1e9+7;
 
int main()
{
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ll n;
	cin>>n;
 
	vll dp(n+1,0);
	dp[0] = 1;
	dp[1] = 1;
	for(int i = 2;i<=n;i++)
	{
		for(int j = 1;j<=6;j++)
		{
			if(i-j>=0)
				dp[i]=(dp[i]+dp[i-j])%mod;
		}
	}
	cout<<dp[n];
}