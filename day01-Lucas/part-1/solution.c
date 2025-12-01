#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        fprintf(stderr, "Usage: %s [input_file]\n", argv[0]);
        return EXIT_FAILURE;
}

    int position = 50;
    int zero_counter = 0;
    int rotation_counter = 0;
    char direction;
    int distance;

    printf("Starting position: %d\n", position);

    while (fscanf(fp, " %c%d", &direction, &distance) == 2) {
        rotation_counter++;

        if (direction == 'L') {
            position = (position - distance % 100 + 100) % 100;
        } else if (direction == 'R') {
            position = (position + distance) % 100;
        } else {
            fprintf(stderr, "Invalid direction: %c\n", direction);
            continue;
        }
        if (position == 0) {
            zero_counter++;
            printf(" <- ZERO! (count: %d)", zero_counter);
        }
        printf("\n");
    }
    fclose(fp);
    
    printf("\n");
    printf("Processed %d rotations\n", rotation_counter);
    printf("PASSWORD: %d\n", zero_counter);

    return 0;
}