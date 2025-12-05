#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    int total = 0;
    int bank_num = 1;
    
    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        int len = strlen(line);
        if (len < 2) continue; // Need at least 2 batteries
        
        printf("Bank %d: %s\n", bank_num, line);
        
        int max_joltage = 0;
        int best_i = -1, best_j = -1;
        
        // Try each position as the tens digit
        for (int i = 0; i < len - 1; i++) {
            char tens_digit = line[i];
            char max_units = '0';
            int max_j = -1;
            
            // Find the maximum digit after position i
            for (int j = i + 1; j < len; j++) {
                if (line[j] > max_units) {
                    max_units = line[j];
                    max_j = j;
                }
            }
            
            // Calculate joltage for this combination
            int joltage = (tens_digit - '0') * 10 + (max_units - '0');
            
            printf("  Position %d (%c) + max after (%c at pos %d) = %d\n", 
                   i, tens_digit, max_units, max_j, joltage);
            
            if (joltage > max_joltage) {
                max_joltage = joltage;
                best_i = i;
                best_j = max_j;
            }
        }
        
        printf("  → Best: positions %d and %d (%c%c) = %d jolts\n", 
               best_i, best_j, line[best_i], line[best_j], max_joltage);
        
        total += max_joltage;
        printf("  Running total: %d\n\n", total);
        
        bank_num++;
    }
    
    fclose(file);
    
    printf("==================\n");
    printf("Total output joltage: %d\n", total);
    
    return 0;
}