#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 200

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
    
    char grid[MAX_SIZE][MAX_SIZE];
    int rows = 0;
    int cols = 0;
    
    // Read the grid
    while (fgets(grid[rows], MAX_SIZE, file)) {
        // Remove newline
        grid[rows][strcspn(grid[rows], "\n")] = 0;
        int len = strlen(grid[rows]);
        if (len > cols) cols = len;
        rows++;
    }
    fclose(file);
    
    printf("Grid size: %d rows x %d cols\n\n", rows, cols);
    
    // Print the initial grid
    printf("Initial state:\n");
    for (int i = 0; i < rows; i++) {
        printf("%s\n", grid[i]);
    }
    printf("\n");
    
    // Directions for 8 neighbors
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    int total_removed = 0;
    int round = 1;
    
    while (1) {
        // Find all accessible rolls in this round
        int accessible[MAX_SIZE][MAX_SIZE] = {0};
        int round_count = 0;
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < strlen(grid[r]); c++) {
                if (grid[r][c] == '@') {
                    // Count adjacent rolls of paper
                    int adjacent_rolls = 0;
                    
                    for (int d = 0; d < 8; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];
                        
                        // Check bounds
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < strlen(grid[nr])) {
                            if (grid[nr][nc] == '@') {
                                adjacent_rolls++;
                            }
                        }
                    }
                    
                    // If fewer than 4 adjacent rolls, it's accessible
                    if (adjacent_rolls < 4) {
                        accessible[r][c] = 1;
                        round_count++;

                    }
                }
            }
        }
        
        // If no rolls are accessible, we're done
        if (round_count == 0) {
            break;
        }
        
        printf("Removing %d rolls:\n", round_count);
        
        // Remove all accessible rolls (mark as 'x' for visualization first)
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < strlen(grid[r]); c++) {
                if (accessible[r][c]) {
                    grid[r][c] = 'x';
                }
            }
        }
        
        // Print the grid with 'x' markers
        for (int i = 0; i < rows; i++) {
            printf("%s\n", grid[i]);
        }
        printf("\n");
        
        // Now convert 'x' to '.'
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < strlen(grid[r]); c++) {
                if (grid[r][c] == 'x') {
                    grid[r][c] = '.';
                }
            }
        }
        
        total_removed += round_count;
        round++;
    }
    
    printf("Final state:\n");
    for (int i = 0; i < rows; i++) {
        printf("%s\n", grid[i]);
    }
    
    printf("\n==================\n");
    printf("Total rolls removed: %d\n", total_removed);
    
    return 0;
}