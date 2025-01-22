#include<stdio.h>
#include<stdlib.h>

void print_to_file(int n,double **A,int format_flag)
{
    FILE* outptr;
    
    if(format_flag==0)
    {
        char filename[]="array_nnnnnn_asc.out";
        for(int p=11,l=n;p>=6;p--,l/=10)
        {
        filename[p]='0'+l%10;
        }

        outptr=fopen(filename,"w+");
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                fprintf(outptr,"%.15lf ",A[i][j]);
            }
            fprintf(outptr,"\n");
        }
    }
    else{
        char filename[]="array_nnnnnn_bin.out";
        for(int p=11,l=n;p>=6;p--,l/=10)
        {
        filename[p]='0'+l%10;
        }

        outptr=fopen(filename,"w+");
        for (int i = 0; i < n; i++)
        {
            fwrite(A[i], sizeof(double), n, outptr);
        }

    }
}

int main()
{
    FILE* fptr;
    fptr=fopen("input.in","r+");
    int n;
    fscanf(fptr,"%d",&n);
    double** A;
    A=(double **)malloc(n*sizeof(double *));
    for(int i=0;i<n;i++)
    {
        A[i]=(double *)malloc(n*sizeof(double));
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            A[i][j]=i+j;
        }

    }
    print_to_file(n,A,0);
    print_to_file(n,A,1);
    return 0;
}