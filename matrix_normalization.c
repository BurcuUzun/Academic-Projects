#include <stdio.h>
#include <math.h>

/* * Project: Z-Score Matrix Normalization
 * Description: Normalizes 3D matrix data sets by calculating mean 
 * and standard deviation for each element position.
 */

int main()
{
    int k;
    int rows,columns;
    double M[100][100][100];
    int row_counts[100];
    int col_counts[100];
    scanf(" %d", &k);
    for(int i=0; i<k; i++)
    {
        scanf(" %d %d", &rows, &columns);
        for(int r=0; r<rows; r++)
        {
            for(int c=0; c<columns; c++)
            {
                scanf(" %lf", &M[i][r][c]);
                row_counts[i]=rows;
                col_counts[i]=columns;
            }
        }
    }

    for(int r=0; r<100; r++)
    {
        for(int c=0; c<100; c++)
        {
            int count=0;
            double sum=0;
            for(int i=0; i<k; i++)
            {
                if(r<row_counts[i] && c<col_counts[i])
                {
                    count+=1;
                    sum+=M[i][r][c];
                }
            }

            if(count==0)
            {
                continue;
            }

            double mean=sum/count;
            double deviation_sum=0;

            for(int i=0; i<k; i++)
            {
                if(r<row_counts[i] && c<col_counts[i])
                {
                    deviation_sum+=((M[i][r][c]-mean)*(M[i][r][c]-mean));
                }
            }

            double deviation=sqrt(deviation_sum/count);

            for(int i=0; i<k; i++)
            {
                if(r<row_counts[i] && c<col_counts[i])
                {
                    if(deviation< 0.000001)
                    {
                        M[i][r][c]=0;
                    }
                    else
                    {
                        M[i][r][c]=(M[i][r][c]-mean)/deviation;
                    }
                }
            }

            mean=0;
            deviation=0;
        }
    }

    for(int i=0; i<k; i++)
    {
        for(int r=0; r<row_counts[i]; r++)
        {
            for(int c=0; c<col_counts[i]; c++)
            {
                printf("%lf ", M[i][r][c]);
            }
            printf("\n");
        }
    }

    return 0;
}