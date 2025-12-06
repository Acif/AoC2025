#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int main(int args, char *argv[]) {
    if (args != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
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


     // Print the grid
    printf("Original grid:\n");
    for (int i = 0; i < rows; i++) {
        printf("%s\n", grid[i]);
    }
    printf("\n");

    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    int accessible_count = 0;
    char result[MAX_SIZE][MAX_SIZE];
    
    // Copy grid to result for visualization
    for (int i = 0; i < rows; i++) {
        strcpy(result[i], grid[i]);
    }

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
                    accessible_count++;
                    result[r][c] = 'x';
                } else {
                    printf("\n");
                }
            }
        }
    }
    
    printf("\n");
    printf("Accessible rolls marked with 'x':\n");
    for (int i = 0; i < rows; i++) {
        printf("%s\n", result[i]);
    }
    
    printf("\n==================\n");
    printf("Total accessible rolls: %d\n", accessible_count);
    
    return 0;

}