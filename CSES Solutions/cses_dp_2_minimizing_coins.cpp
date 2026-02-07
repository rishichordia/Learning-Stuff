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
#define pb push_back
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
	ll n,x, temp;
	cin>>n>>x;
	vll coins(n,0);
	fo(i,n)
		cin>>coins[i];
	sort(coins.begin(),coins.end());

	vll dp(x+1,mod+1);
	dp[0] = 0;
	for(ll i = 1;i<=x;i++)
	{
		fo(j,n)
		{
			if(i-coins[j]>=0 && dp[i-coins[j]]!=mod+1 && dp[i]>dp[i-coins[j]] + 1)
				dp[i] = dp[i-coins[j]]+1;
		}
	}
	if(dp[x]==mod+1)
		cout<<-1<<endl;
	else
		cout<<dp[x]<<endl;
}