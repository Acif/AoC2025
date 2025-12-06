#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RANGES 1000
#define MAX_INGREDIENTS 1000

typedef struct {
    long long start;
    long long end;
} Range;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'\n", argv[1]);
        return 1;
    }
    
    Range ranges[MAX_RANGES];
    int range_count = 0;
    long long ingredients[MAX_INGREDIENTS];
    int ingredient_count = 0;
    
    char line[256];
    int reading_ranges = 1;
    
    // Read the file
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) == 0) {
            reading_ranges = 0;
            continue;
        }
        
        if (reading_ranges) {
            long long start, end;
            if (sscanf(line, "%lld-%lld", &start, &end) == 2) {
                ranges[range_count].start = start;
                ranges[range_count].end = end;
                range_count++;
            }
        } else {
            long long id = atoll(line);
            ingredients[ingredient_count++] = id;
        }
    }
    fclose(file);
    
    // Check each ingredient
    int fresh_count = 0;
    
    for (int i = 0; i < ingredient_count; i++) {
        long long id = ingredients[i];
        
        for (int r = 0; r < range_count; r++) {
            if (id >= ranges[r].start && id <= ranges[r].end) {
                fresh_count++;
                break;
            }
        }
    }
    
    printf("%d\n", fresh_count);
    
    return 0;
}