#include <stdio.h>

int main() {
    int t[20], n, i, j, tohm[20], tot = 0;
    float avhm;

    printf("Enter the number of tracks: ");
    scanf("%d", &n);

    printf("Enter the tracks to be traversed: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &t[i]); // Use i as the index, starting from 0
    }

    for (i = 0; i < n; i++) {
        tohm[i] = abs(t[i + 1] - t[i]); // Calculate absolute difference
    }

    for (i = 0; i < n; i++) {
        tot += tohm[i];
    }

    avhm = (float)tot / n;

    printf("Tracks traversed\tDifference between tracks\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t\t%d\n", t[i], tohm[i]);
    }

    printf("\nAverage head movements: %.2f\n", avhm);

    return 0;
}
