#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

char **lines;
size_t total_lines = 0;
size_t total_chars = 0;

int calculate01(){
    int sum = 0;

    for(size_t i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);
        printf("line lenght: %zu | ", line_lenght);
        char left_most;
        char right_most;
        for(size_t j = 0;j < line_lenght; j++){
            if(lines[i][j] <= '9' && lines[i][j] != '\n'){
                left_most = lines[i][j];
                printf("%c", left_most);
                break;
            }
        }
        for(size_t j = line_lenght-1;j >= 0; j--){
            if(lines[i][j] <= '9' && lines[i][j] != '\n'){
                right_most = lines[i][j];
                printf(" %c", right_most);
                break;
            }
        }
        
        int sub_sum = 0;
        sub_sum = (left_most - '0') * 10;
        sub_sum += right_most - '0';
        printf("   sum: %d \n", sub_sum);

        sum += sub_sum;
    }
    return sum;
}

int main(void){
    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL){
        printf("Error opening file.\n");
        perror("Error");
        return 1;
    }

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
                lines[total_lines] = realloc(lines[total_lines], total_chars + 1 );
                lines[total_lines][total_chars] = '\0';

                total_lines++;
            }

            break; 
        }


        if (total_chars == 0)
            lines[total_lines] = malloc(MORE_CHARS); 
        
        lines[total_lines][total_chars] = c; 
        total_chars++;

        if (c == '\n'){
            lines[total_lines] = realloc(lines[total_lines], total_chars + 1 );

            lines[total_lines][total_chars] = '\0';

            total_lines++;

            total_chars = 0;

            if (total_lines % MORE_LINES == 0){
                size_t new_size = total_lines + MORE_LINES;
                lines = realloc(lines, sizeof(char *) * new_size);
            }
            }
            else if (total_chars % MORE_CHARS == 0){
                size_t new_size = total_chars + MORE_CHARS;
                lines[total_lines] = realloc(lines[total_lines], new_size); 
        }

    } while (true);
    lines = realloc(lines, sizeof(char *) * total_lines);

    //for (size_t i = 0; i < total_lines; i++)
    //    printf("%s", lines[i]);

    int total_sum = calculate01();
    printf("\n\ntotal Sum: %d\n", total_sum);

    // Free the block of memory allocated for each string
    for (size_t i = 0; i < total_lines; i++)
        free(lines[i]);

    free(lines);

    fclose(file);

    return 0;
}