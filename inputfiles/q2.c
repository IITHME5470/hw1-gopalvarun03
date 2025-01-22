#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to check if the vector is an eigenvector and return the eigenvalue
double checkeigen(double **A, double *arr, int n) {
    double *dum = (double *)malloc(sizeof(double) * n);
    double ans = __INT_MAX__;

    for (int i = 0; i < n; i++) {
        double u = 0;
        for (int j = 0; j < n; j++) {
            u += A[i][j] * arr[j];
        }
        dum[i] = u;
    }

    // Check if the vector is valid
    for(int i=0;i<n;i++)
    {
        if(arr[i]!=0)
        {
            ans=dum[i]/arr[i];
            break;
        }
    }
    
    if(ans==__INT_MAX__)
    {
        free(dum);
        return ans;
    }

    for (int i = 0; i < n; i++) {
        if (fabs(ans * arr[i] - dum[i]) > 1e-6) {
            free(dum);
            return __INT_MAX__;
        }
    }

    free(dum);
    return ans;
}

int main() {
    int n;
    FILE *fptr;

    // Open the input file
    fptr = fopen("input.in", "r");
    if (fptr == NULL) {
        printf("Error: Unable to open input.in\n");
        return 1;
    }

    fscanf(fptr, "%d", &n);
    fclose(fptr);

    // Open the matrix file
    char filename[20];
    sprintf(filename, "mat_%06d.in", n);
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error: Unable to open %s\n", filename);
        return 1;
    }

    // Allocate memory for the matrix
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    // Read the matrix from the file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fptr, "%lf,", &A[i][j]);
        }
    }
    fclose(fptr);

    // Check the eigenvectors
    int vecnum = 4;
    for (int i = 0; i < vecnum; i++) {
        double *arr = (double *)malloc(sizeof(double) * n);
        char filename2[30];
        sprintf(filename2, "vec_%06d_%06d.in", n, i + 1);

        FILE *fptr2 = fopen(filename2, "r+");
        if (fptr2 == NULL) {
            printf("Error: Unable to open %s\n", filename2);
            free(arr);
            continue;
        }

        for (int j = 0; j < n; j++) {
            fscanf(fptr2, "%lf,", &arr[j]);
        }

        double eigen = checkeigen(A, arr, n);
        if (eigen == __INT_MAX__) {
            printf("%s : No\n", filename2);
        } else {
            fclose(fptr2);
            printf("%s : Yes : %lf\n", filename2, eigen);
            fptr2=fopen(filename2,"a");
            fprintf(fptr2,"\n Eigen Value: %lf",eigen);
        }

        fclose(fptr2);
        free(arr);
    }

    // Free matrix memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}
