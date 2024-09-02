#include <stdio.h>
#include <stdlib.h>


void printMatrix(double **matrix, int rows, int cols){
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(j == (cols-1)){
                printf("%lf", matrix[i][j]);
            }
            else{
                printf("%lf ", matrix[i][j]);
            }
        }
        printf("\n");
    }

}

void printVector(double *matrix, int rows){
    for (int i = 0; i < rows; i++){
        if (i == rows-1){
            printf("%.0f\n", matrix[i]);
        }
        else{
            printf("%.0f\n", matrix[i]);
        }
        //printf("\n");
    }
}

void transpose(double **matrix, double **transposedMatrix, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
}

void multiply(double **matrix1, double **matrix2, double **productMatrix, int rows1, int cols1, int rows2, int cols2){
    
    for (int i = 0; i < rows1; i++){
        for (int j = 0; j < cols2; j++){
            productMatrix[i][j] = 0;
            for (int x = 0; x < rows2; x++){
                productMatrix[i][j] += matrix1[i][x] * matrix2[x][j];
            }
        }
    }
        
}

void matrixByVectorMultiply(double **matrix1, double *matrix2, double *productMatrix, int rows1, int cols1, int rows2, int cols2){
    
    for (int i = 0; i < rows1; i++){
        productMatrix[i] = 0;
        for (int x = 0; x < rows2; x++){
            productMatrix[i] += matrix1[i][x] * matrix2[x];
        }
    }
}

void inverse(double **matrix, double **inverted, int n){
    //BELOW THE DIAGONAL
    for (int p = 0; p < n; p++){
        double f = matrix[p][p];
        //divide Mp by f and Np by f
        for (int c = 0; c < n; c++){
            matrix[p][c] = (matrix[p][c] / f);
            inverted[p][c] = (inverted[p][c] / f);
        }
        
        for (int i = p+1; i < n; i++){
            f = matrix[i][p];
            //subtract Mp x f from Mi and Np x f from Ni
            for (int c = 0; c < n; c++){
                matrix[i][c] = (matrix[i][c] - (matrix[p][c] * f));
                inverted[i][c] = (inverted[i][c] - (inverted[p][c] * f));
            }
        }
    }
    
    //ABOVE THE DIAGONAL
    for (int p = n-1; p >= 0; p--){
        for (int i = p-1; i >= 0; i--){
            double f = matrix[i][p];
            //Subtract Mp x f from Mi and Np x f from Ni
            for (int c = n-1; c >= 0; c--){
                matrix[i][c] = (matrix[i][c] - (matrix[p][c] * f));
                inverted[i][c] = (inverted[i][c] - (inverted[p][c] * f));
            }
        }
    }
}


int main(int argc, char** argv){
    
    FILE *fp = fopen(argv[1], "r");
    char str[6];
    int attributeCount;
    int houseCount;
    
    
    fscanf(fp, "%s", str);
    fscanf(fp, "%d", &attributeCount);
    fscanf(fp, "%d", &houseCount);
    
    //MALLOCS==========================================================================================
    //malloc first matrix
    double **matrixX;
    matrixX = (double**) calloc(houseCount, sizeof(double*));
    for (int i = 0; i < houseCount; i++){
        matrixX[i] = (double*) calloc(attributeCount+1, sizeof(double*));
    }
    
    //malloc Y matrix
    double *matrixY = (double*)calloc(houseCount, sizeof(double));
    
    //malloc matrixXT
    double **matrixXTransposed;
    matrixXTransposed = (double**) calloc(attributeCount+1, sizeof(double*));
    for (int i = 0; i < attributeCount+1; i++){
        matrixXTransposed[i] = (double*) calloc(houseCount, sizeof(double*));
    }
    
    //malloc matrixProduct1
    double **matrixProduct1;
    matrixProduct1 = (double**) calloc(attributeCount+1, sizeof(double*));
    for (int i = 0; i < attributeCount+1; i++){
        matrixProduct1[i] = (double*) calloc(attributeCount+1, sizeof(double*));
    }
    
    //malloc matrixProduct1Inverse
    double **matrixProduct1Inverse;
    matrixProduct1Inverse = (double**) calloc(attributeCount+1, sizeof(double*));
    for (int i = 0; i < attributeCount+1; i++){
        matrixProduct1Inverse[i] = (double*) calloc(attributeCount+1, sizeof(double*));
    }
    
    //malloc matrixProduct2
    double **matrixProduct2;
    matrixProduct2 = (double**) calloc(attributeCount+1, sizeof(double*));
    for (int i = 0; i < attributeCount+1; i++){
        matrixProduct2[i] = (double*) calloc(houseCount, sizeof(double*));
    }
    
    //malloc matrixW
    double *matrixW = (double*)calloc(attributeCount+1, sizeof(double));
    
    //Filling Matrices=========================================================================
    //Fill matrixX and matrixY
    for (int i = 0; i < houseCount; i++){
        for (int j = 0; j < attributeCount+2; j++){
            if (j == 0){
                matrixX[i][j] = 1.0;
            } else if (j == attributeCount+1){
                fscanf(fp, "%lf", &matrixY[i]);
            } else{
                fscanf(fp, "%lf", &matrixX[i][j]);
            }
        }
    }
    fclose(fp);
    //Fill matrixProduct1Inverse with identity matrix
    for (int i = 0; i < attributeCount+1; i++){
        for (int j = 0; j < attributeCount+1; j++){
            if (j == i){
                matrixProduct1Inverse[i][j] = 1.0;
            }
            else{
                matrixProduct1Inverse[i][j] = 0.0;
            }
        }
    }
    
    
    //OPERATIONS=======================================================================================
    //Transpose matrixX
    transpose(matrixX, matrixXTransposed, houseCount, attributeCount+1);
    //multiply matrixXTranspose with matrixX
    multiply(matrixXTransposed, matrixX, matrixProduct1, attributeCount+1, houseCount, houseCount, attributeCount+1);
    //Obtain inverse of matrixProduct1
    inverse(matrixProduct1, matrixProduct1Inverse, attributeCount+1);
    //multiply matrixProduct1Inverse with matrixXTransposed to get matrixProduct2
    multiply(matrixProduct1Inverse, matrixXTransposed, matrixProduct2, attributeCount+1, attributeCount+1, attributeCount+1, houseCount);
    //multiply matrixProduct2 with matrixY into matrixW
    matrixByVectorMultiply(matrixProduct2, matrixY, matrixW, attributeCount+1, houseCount, houseCount, 1);
    
    
    //PRINT MATRICES/VECTORS===========================================================================
    /*
    printMatrix(matrixX, houseCount, attributeCount+1);
    printf("\n");
    printVector(matrixY, houseCount);
    printf("\n");
    printMatrix(matrixXTransposed, attributeCount+1, houseCount);
    printf("\n");
    printMatrix(matrixProduct1, attributeCount+1, attributeCount+1);
    printf("\n");
    printMatrix(matrixProduct1Inverse, attributeCount+1, attributeCount+1);
    printf("\n");
    printMatrix(matrixProduct2, attributeCount+1, houseCount);
    printf("\n");
    printVector(matrixW, attributeCount+1);
    */
    
    //DATA SECTION=====================================================================================
    //=================================================================================================
    
    FILE *fp2 = fopen(argv[2], "r");
    char str2[5];
    int dAttributeCount;
    int dHouseCount;
    fscanf(fp2, "%s", str2);
    fscanf(fp2, "%d", &dAttributeCount);
    fscanf(fp2, "%d", &dHouseCount);
    
    
    /*
    printf("\n");
    printf("%s\n",str2);
    printf("%d\n",dAttributeCount);
    printf("%d\n",dHouseCount);
    */
    
    //Create dataMatrix1
    double **dataMatrix1;
    dataMatrix1 = (double**) calloc(dHouseCount, sizeof(double*));
    for (int i = 0; i < dHouseCount; i++){
        dataMatrix1[i] = (double*) calloc(dAttributeCount+1, sizeof(double*));
    }
    //Create resultMatrix
    double *resultMatrix = (double*) calloc(dHouseCount, sizeof(double));
    
    //fill dataMatrix1
    for (int i = 0; i < dHouseCount; i++){
        for (int j = 0; j < dAttributeCount+1; j++){
            if (j == 0){
                dataMatrix1[i][j] = 1;
            }
            else{
                fscanf(fp2, "%lf", &dataMatrix1[i][j]);
            }
        }
    }
    
    fclose(fp2);
    matrixByVectorMultiply(dataMatrix1, matrixW, resultMatrix, dHouseCount, dAttributeCount+1, attributeCount+1, 1);
    
    //print
    printVector(resultMatrix, dHouseCount);
    
    //=================================================================================================
    //FREEEEEEE========================================================================================
    //matrixX
    for (int i = 0; i < houseCount; i++){
        free(matrixX[i]);
    }
    free(matrixX);
    //matrixY
    free(matrixY);
    //matrixXTransposed
    for (int i = 0; i < attributeCount+1; i++){
        free(matrixXTransposed[i]);
    }
    free(matrixXTransposed);
    //matrixProduct1
    for (int i = 0; i < attributeCount+1; i++){
        free(matrixProduct1[i]);
    }
    free(matrixProduct1);
    //matrixProduct1Inverse
    for (int i = 0; i < attributeCount+1; i++){
        free(matrixProduct1Inverse[i]);
    }
    free(matrixProduct1Inverse);
    //matrixProduct2
    for (int i = 0; i < attributeCount+1; i++){
        free(matrixProduct2[i]);
    }
    free(matrixProduct2);
    //matrixW
    free(matrixW);
    //dataMatrix1
    for (int i = 0; i < dHouseCount; i++){
        free(dataMatrix1[i]);
    }
    free(dataMatrix1);
    //resultMatrix
    free(resultMatrix);
    
    
    return 0;
}
