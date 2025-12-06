#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RANGES 1000

typedef struct {
    long long start;
    long long end;
} Range;

// Merge overlapping ranges, returns number of ranges eliminated
int merge_ranges(Range *ranges, int *count) {
    int original_count = *count;
    Range merged[MAX_RANGES];
    int merged_count = 0;
    int used[MAX_RANGES] = {0};
    
    for (int i = 0; i < *count; i++) {
        if (used[i]) continue;
        
        Range current = ranges[i];
        
        // Check for overlaps with other ranges
        for (int j = 0; j < *count; j++) {
            if (i == j || used[j]) continue;
            
            // Check if ranges overlap
            if ((current.start >= ranges[j].start && current.start <= ranges[j].end) ||
                (current.end >= ranges[j].start && current.end <= ranges[j].end) ||
                (ranges[j].start >= current.start && ranges[j].start <= current.end)) {
                
                // Merge the ranges
                if (ranges[j].start < current.start) current.start = ranges[j].start;
                if (ranges[j].end > current.end) current.end = ranges[j].end;
                
                used[j] = 1;
            }
        }
        
        merged[merged_count++] = current;
        used[i] = 1;
    }
    
    // Remove duplicates from merged ranges
    Range final[MAX_RANGES];
    int final_count = 0;
    
    for (int i = 0; i < merged_count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < final_count; j++) {
            if (final[j].start == merged[i].start && final[j].end == merged[i].end) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            final[final_count++] = merged[i];
        }
    }
    
    // Copy back to original array
    for (int i = 0; i < final_count; i++) {
        ranges[i] = final[i];
    }
    *count = final_count;
    
    return original_count - final_count;
}

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
        }
    }
    fclose(file);
    
    // Merge ranges
    while (merge_ranges(ranges, &range_count) != 0);
    
    // Count total fresh IDs
    long long total_fresh = 0;
    for (int i = 0; i < range_count; i++) {
        total_fresh += ranges[i].end - ranges[i].start + 1;
    }
    
    printf("%lld\n", total_fresh);
    
    return 0;
}