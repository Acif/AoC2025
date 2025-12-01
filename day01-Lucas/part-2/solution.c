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
    int zero_counter_1 = 0;
    int zero_counter_2 = 0;
    int rotation_counter = 0;
    char direction;
    int distance;

    printf("Starting position: %d\n", position);

    while (fscanf(fp, " %c%d", &direction, &distance) == 2) {
        rotation_counter++;
        int clicks_through_zero = 0;

        if (direction == 'L') {
            clicks_through_zero = distance / 100;
            if (position > 0 && (distance % 100) >= position) {
                clicks_through_zero++;
            }
            position = (position - distance % 100 + 100) % 100;
        
        } else if (direction == 'R') {
            clicks_through_zero = (position + distance) / 100;
            position = (position + distance) % 100;
        } else {
            fprintf(stderr, "Invalid direction: %c\n", direction);
            continue;
        }
        zero_counter_2 += clicks_through_zero;
        
        if (position == 0) {
            zero_counter_1++;
        }
    }
    fclose(fp);
    
    printf("\n");
    printf("Processed %d rotations\n", rotation_counter);
    printf("PASSWORD Part 1: %d\n", zero_counter_1);
    printf("PASSWORD Part 2 (all clicks that pass through or end on 0): %d\n", zero_counter_2);

    return 0;
}