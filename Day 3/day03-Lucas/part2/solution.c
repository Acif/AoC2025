#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BATTERIES_TO_SELECT 12

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
    
    char line[1024];
    unsigned long long total = 0;
    int bank_num = 1;
    
    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        int len = strlen(line);
        if (len < BATTERIES_TO_SELECT) {
            printf("Bank %d: %s (too short, skipping)\n\n", bank_num, line);
            bank_num++;
            continue;
        }
        
        printf("Bank %d: %s (length %d)\n", bank_num, line, len);
        
        char result[BATTERIES_TO_SELECT + 1];
        result[BATTERIES_TO_SELECT] = '\0';
        int last_selected = -1;
        
        // Greedily select the largest digit for each position
        for (int output_pos = 0; output_pos < BATTERIES_TO_SELECT; output_pos++) {
            int remaining_needed = BATTERIES_TO_SELECT - output_pos - 1;
            int search_start = last_selected + 1;
            int search_end = len - remaining_needed - 1;
            
            printf("  Position %d: searching indices [%d, %d], need %d more after\n",
                   output_pos, search_start, search_end, remaining_needed);
            
            char max_digit = '0';
            int max_idx = -1;
            
            // Find the largest digit in the valid range
            for (int j = search_start; j <= search_end; j++) {
                if (line[j] > max_digit) {
                    max_digit = line[j];
                    max_idx = j;
                }
            }
            
            result[output_pos] = max_digit;
            last_selected = max_idx;
            
            printf("    → Selected '%c' at index %d\n", max_digit, max_idx);
        }
        
        printf("  Result: %s\n", result);
        
        // Convert to unsigned long long
        unsigned long long joltage = strtoull(result, NULL, 10);
        printf("  Joltage: %llu\n", joltage);
        
        total += joltage;
        printf("  Running total: %llu\n\n", total);
        
        bank_num++;
    }
    
    fclose(file);
    
    printf("==================\n");
    printf("Total output joltage: %llu\n", total);
    
    return 0;
}