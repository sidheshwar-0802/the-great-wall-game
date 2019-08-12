#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 9999;

class Grid
{
	public:
	int W[105][105], N;
	int mx[105], my[105]; 	// match arr
	int lx[105], ly[105]; 	// label arr
	int x[105], y[105];  	// used arr

	int wall(int nd);
	int run();

} Grid;

int Grid::wall(int nd)
{
    int i;
    x[nd] = 1;

	for(i = 0; i < N; i++)
	{
        if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i])
		{
            y[i] = 1;

			if(my[i] == -1 || wall(my[i]))
			{
                my[i] = nd;
                return 1;
            }
        }
    }

    return 0;
}

int Grid::run()
{
    int i, j, k, d;

	memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));

	for (i = 0; i < N; i++)
    	lx[i] = -MAX, ly[i] = 0;

	for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];

	for(i = 0; i < N; i++)
	{
        while(1)
		{
            memset(x, 0, sizeof(x));
            memset(y, 0, sizeof(y));

			if(wall(i))  break;
            d = MAX;

			for(j = 0; j < N; j++)
			{
                if(x[j])
				{
                    for(k = 0; k < N; k++)
                        if(!y[k])
                        d = d < lx[j]+ly[k]-W[j][k] ? d : lx[j]+ly[k]-W[j][k];
                }
            }

			if(d == MAX)  break;

			for(j = 0; j < N; j++)
			{
                if(x[j])    lx[j] -= d;
                if(y[j])    ly[j] += d;
            }
        }
    }

    int res = 0;

	for(i = 0; i < N; i++)
	{
        if(my[i] != -1)
            res += W[my[i]][i];
    }

	return res;
}

int dist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

int max(int num1, int num2)
{
	return num1 >= num2 ? num1 : num2;
}

int main()
{
	int cases = 0, flag = 0;
    int n, x[105], y[105], i, j, k, s;

	do
	{
	    //printf("Enter number of Stones [Enter zero to Quit] : ");
		s = scanf("%d", &n);

		if(s == 1 && n)
	    {
	        for (i = 0; i < n; i++)
	        {
	        	do
	        	{
		        	flag = 0;
	        		//printf("Enter the co-ordinates for Stone %d : ", i + 1);
		        	scanf("%d %d", &x[i], &y[i]);

		    		if (x[i] <= 0 || y[i] <= 0 || x[i] > n || y[i] > n)
	        		{
	        			printf("Co-ordinates must follow : 0 < x,y <= %d\n", n);
	        			flag = 1;
	        		}

		        	for(j = 0; j < i; j++)
		        	{
		        		if(x[i] == (x[j] + 1) && y[i] == (y[j] + 1))
		        		{
		        			printf("Do not repeat Co-ordinates\n");
		        			flag = 1;
		        			break;
		        		}
		        	}
		        } while(flag != 0);

		    	x[i]--, y[i]--;
	        }

		    Grid.N = n;

		    int ret = -MAX;

		    for (i = 0; i < n; i++)		// For Horizontal Wall
	        {
	        	for (j = 0; j < n; j++)
	        		for (k = 0; k < n; k++)
	        			Grid.W[j][k] = -dist(x[j], y[j], i, k);
	        	ret = max(ret, Grid.run());
	        }

		    for (i = 0; i < n; i++)		// For Vertical Wall
	        {
	        	for (int j = 0; j < n; j++)
	        		for (int k = 0; k < n; k++)
	        			Grid.W[j][k] = -dist(x[j], y[j], k, i);
	        	ret = max(ret, Grid.run());
	    	}

			for (i = 0; i < n; i++)		// For Forward Diagonal Wall
	    	{
	        	for (int j = 0; j < n; j++)
	        		Grid.W[j][i] = -dist(x[j], y[j], i, i);
	    	}
			ret = max(ret, Grid.run());

			for (i = 0; i < n; i++)		// For Backward Diagonal Wall
	    	{
	        	for (int j = 0; j < n; j++)
	        		Grid.W[j][i] = -dist(x[j], y[j], i, n - i - 1);
	    	}
			ret = max(ret, Grid.run());

		    printf("%d moves required.\n\n", -ret);
		    ++cases;
	    }

	} while(n != 0);

	return 0;
}
