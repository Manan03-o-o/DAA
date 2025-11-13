#include <stdio.h>
#include <string.h>

#define MAX 100

void printLCS(char b[MAX][MAX], char X[], int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == '-') { 
        printLCS(b, X, i - 1, j - 1);
        printf("%c", X[i - 1]);
    }
    else if (b[i][j] == '|') { 
        printLCS(b, X, i - 1, j);
    }
    else { 
        printLCS(b, X, i, j - 1);
    }
}

void LCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int c[MAX][MAX];
    char b[MAX][MAX];

    
    for (int i = 0; i <= m; i++)
        c[i][0] = 0;
    for (int j = 0; j <= n; j++)
        c[0][j] = 0;

    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '-'; 
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|'; 
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '<'; 
            }
        }
    }

    printf("\nLength of LCS: %d\n", c[m][n]);
    printf("LCS: ");
    printLCS(b, X, m, n);
    printf("\n");
}

int main() {
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";

    printf("Sequence X: %s\n", X);
    printf("Sequence Y: %s\n", Y);

    LCS(X, Y);
    return 0;
}
