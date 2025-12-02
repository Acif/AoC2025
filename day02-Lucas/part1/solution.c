#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

bool is_invalid_id(long long id){
    char id_str[32];                // Buffer to hold the string representation of the number
    
    sprintf(id_str, "%lld", id);
    int len = strlen(id_str);

                                    // Check for even length since only even length numbers can have repeated halves
    if (len % 2 != 0) return false;

    int half_len = len / 2;
                                    // Compare the two halves
    for (int i = 0; i < half_len; i++) { 
        if (id_str[i] != id_str[i + half_len]) {
            return false;
        }
    }
    return true;                    // If all characters matched, invalid ID
}

int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : NULL;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        fprintf(stderr, "Usage: %s [input_file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_END); // Move to end of file
    long fsize = ftell(fp); // Get current file pointer
    fseek(fp, 0, SEEK_SET); // Move back to beginning of file

    char *buffer = malloc(fsize + 1); // Allocate buffer for file content
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(fp);  // Clean up: close file before exiting
        return EXIT_FAILURE;
    }
    
    size_t read_size = fread(buffer, 1, fsize, fp);
    buffer[read_size] = '\0';       // Null-terminate the string
    fclose(fp);

    while (read_size > 0 && isspace(buffer[read_size - 1])) { 
        buffer[--read_size] = '\0';  // Decrement size and null-terminate
    }

    long long total_invalid_sum = 0;
    int total_invalid_count = 0;
    int range_count = 0;
    char *token = strtok(buffer, ","); // Split by commas

    while (token) {
        while (*token && isspace(*token)) token++; // Trim leading whitespace

        long long start, end;

        if (sscanf(token, "%lld-%lld", &start, &end) != 2) {
            // If parsing failed, print error and skip this token
            fprintf(stderr, "Invalid range format: %s\n", token);
            token = strtok(NULL, ",");  // Get next token
            continue;  // Skip to next iteration
        }

        if (start > end) {
            fprintf(stderr, "Warning: Invalid range %lld-%lld (start > end)\n", start, end);
            token = strtok(NULL, ",");
            continue;
        }
        range_count++;

        long long range_size = end - start + 1;

        #if DEBUG
        printf("\n[Range %d] Processing %lld-%lld (size: %lld)\n", 
               range_count, start, end, range_size);
        
        // Warn user if range is very large (could take a long time)
        if (range_size > 1000000) {
            printf("  WARNING: Large range detected! This may take a while...\n");
        }
        #endif

        int invalid_in_range = 0;
        

        for (long long id = start; id <= end; id++) {
            // Check if this ID is invalid using our helper function
            if (is_invalid_id(id)) {
                // Add this invalid ID to our running total
                total_invalid_sum += id;
                
                // Increment counters
                invalid_in_range++;
                total_invalid_count++;
                
                // Debug: print each invalid ID as we find it
                #if DEBUG
                printf("  Found invalid ID: %lld\n", id);
                #endif
            }
        }
        #if DEBUG
        printf("  Found %d invalid ID(s) in this range\n", invalid_in_range); 
        #endif
        token = strtok(NULL, ",");
    }
    free(buffer); // Free allocated memory

    // Debug: print detailed statistics
    #if DEBUG
    printf("\n=== Summary ===\n");
    printf("Ranges processed: %d\n", range_count);
    printf("Total invalid IDs found: %d\n", total_invalid_count);
    #endif
    
    // Always print the final answer (sum of all invalid IDs)
    printf("Total sum of invalid IDs: %lld\n", total_invalid_sum);
    
    // Return success code to operating system
    return 0;
}