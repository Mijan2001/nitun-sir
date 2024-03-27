// Banker's Algorithm
#include <iostream>
using namespace std;

int main()
{


int n, m, i, j, k;
n = 5;
m = 3;
cout<<"Enter the number of process and resource : ";
cin>>n>>m;

int alloc[n][m],max[n][m],avail[m];

cout<<"Enter value for allocate : "<<endl;
for(i=0;i<n;i++)
{
	for(j=0;j<m;j++)
	{
		cin>>alloc[i][j];
	}
}

cout<<"Enter value for maxneed : "<<endl;
for(i=0;i<n;i++)
{
	for(j=0;j<m;j++)
	{
		cin>>max[i][j];
	}
}

// int alloc[5][3] = { { 0, 1, 0 },
					// { 2, 0, 0 },
					// { 3, 0, 2 },
					// { 2, 1, 1 },
					// { 0, 0, 2 } };
//
// int max[5][3] = { { 7, 5, 3 },
				// { 3, 2, 2 },
				// { 9, 0, 2 },
				// { 2, 2, 2 },
				// { 4, 3, 3 } };

cout<<"Enter the value of available : "<<endl;
for(i=0;i<m;i++)
{
	cin>>avail[i];
}
// int avail[3] = { 3, 3, 2 };

int f[n], ans[n], ind = 0;
for (k = 0; k < n; k++)
{
	f[k] = 0;
}

int need[n][m];
for (i = 0; i < n; i++)
{
	for (j = 0; j < m; j++)
	{
		need[i][j] = max[i][j] - alloc[i][j];
	}
}
int y = 0;
for (k = 0; k < 5; k++)
{
	for (i = 0; i < n; i++)
	{
	if (f[i] == 0)
	{

		int flag = 0;
		for (j = 0; j < m; j++)
		{
		if (need[i][j] > avail[j])
		{
			flag = 1;
			break;
		}
		}

		if (flag == 0)
		{
		ans[ind++] = i;
		for (y = 0; y < m; y++)
			avail[y] += alloc[i][y];
		f[i] = 1;
		}
	}
	}
}

int flag = 1;

for(int i = 0;i<n;i++)
{
		if(f[i]==0)
	{
		flag = 0;
		cout << "The sequence is not safe"<<endl;
		break;
	}
}

if(flag==1)
{
	cout << "The sequence is : " << endl;
	for (i = 0; i < n - 1; i++)
		cout << " P" << ans[i] << " ->";
	cout << " P" << ans[n - 1] <<endl;
}

	return (0);
}
