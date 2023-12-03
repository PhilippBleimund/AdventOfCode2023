#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int readFile(FILE* file, char** lines, size_t* total_lines, size_t MORE_LINES, size_t MORE_CHARS){
    if (file == NULL){
        printf("Error opening file.\n");
        perror("Error");
        return 1;
    }

    size_t total_chars = 0;

    lines = malloc(sizeof(char *) * MORE_LINES);

    char c;

    do{
        c = fgetc(file);

        if (ferror(file)){
            printf("Error reading from file.\n");
            return 1;
        }

        if (feof(file)){
            if (total_chars != 0){        
                lines[*total_lines] = realloc(lines[*total_lines], total_chars + 1 );
                lines[*total_lines][total_chars] = '\0';

                total_lines++;
            }

            break; 
        }


        if (total_chars == 0)
            lines[*total_lines] = malloc(MORE_CHARS); 
        
        lines[*total_lines][total_chars] = c; 
        total_chars++;

        if (c == '\n'){
            lines[*total_lines] = realloc(lines[*total_lines], total_chars + 1 );

            lines[*total_lines][total_chars] = '\0';

            total_lines++;

            total_chars = 0;

            if (*total_lines % MORE_LINES == 0){
                size_t new_size = *total_lines + MORE_LINES;
                lines = realloc(lines, sizeof(char *) * new_size);
            }
        }
        else if (total_chars % MORE_CHARS == 0){
            size_t new_size = total_chars + MORE_CHARS;
            lines[*total_lines] = realloc(lines[*total_lines], new_size); 
        }

    } while (true);
    lines = realloc(lines, sizeof(char *) * (*total_lines));
    
    fclose(file);
    return 0;
}