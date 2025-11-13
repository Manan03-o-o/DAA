#include <stdio.h>

void greedyActivitySelector(int s[], int f[], int n) {
    int A[n];
    int k = 0;
    int count = 1;

    A[0] = 0;

    for (int m = 1; m < n; m++) {
        if (s[m] >= f[k]) {
            A[count] = m;
            k = m;
            count++;
        }
    }

    printf("Selected activities: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", A[i] + 1);
    }
    printf("\n");
}

int main() {
    int s[] = {1, 3, 0, 5, 8, 5};
    int f[] = {2, 4, 6, 7, 9, 9};
    int n = sizeof(s) / sizeof(s[0]);

    greedyActivitySelector(s, f, n);

    return 0;
}

  