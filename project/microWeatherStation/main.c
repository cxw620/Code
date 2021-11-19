#include <stdio.h>
#include <stdlib.h>
#define N 10
int main()
{
    int m,n;
    printf("input m,n:");
    scanf("%d%d",&m,&n);
    int a[m][n],b[n][m];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",a[i][j]);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            b[i][j]=a[j][i];
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%4d",b[i][j]);
        }
        printf("\n");
    }
    return 0;
}
