#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

char **lines;
size_t total_lines = 0;
size_t total_chars = 0;

char numbers[9][5] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int calculate01(){
    int sum = 0;

    for(size_t i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);
        printf("line lenght: %zu | ", line_lenght);
        char left_most;
        char right_most;
        for(int j = 0;j < line_lenght; j++){
            if(lines[i][j] <= '9' && lines[i][j] != '\n'){
                left_most = lines[i][j];
                printf("%c", left_most);
                break;
            }
        }
        for(int j = line_lenght-1;j >= 0; j--){
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

int calculate02(){
    int sum = 0;

    // scope one line
    for(size_t i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);
        printf("line lenght: %zu | ", line_lenght);

        char left_most = '0';
        char right_most = '0';
        size_t left_most_index = line_lenght;
        size_t right_most_index = 0;
        int left_most_str = 0;
        int right_most_str = 0;

        for(int j = 0;j < line_lenght; j++){
            if(lines[i][j] <= '9' && lines[i][j] != '\n'){
                left_most = lines[i][j];
                left_most_index = j;
                printf("%c", left_most);
                break;
            }
        }
        for(int j = line_lenght-1;j >= 0; j--){
            if(lines[i][j] <= '9' && lines[i][j] != '\n'){
                right_most = lines[i][j];
                right_most_index = j;
                printf(" / %c", right_most);
                break;
            }
        }

        int *final_pos_min = malloc(sizeof(int) * 9);
        int *final_pos_max = malloc(sizeof(int) * 9);
        // scope one number
        for(size_t j = 0; j < 9; j++){
            int *pos = malloc(line_lenght);
            int counter = 0;
            // scope for every occurance of number
            for(size_t k = 0; k < line_lenght; k++){
                char *position_ptr = strstr(lines[i]+k, numbers[j]);

                if(position_ptr != NULL){
                    int position = position_ptr - lines[i];
                    pos[counter] = position;
                    counter++;
                }
            }
            int current_min = line_lenght;
            int current_max = 0;
            for(int k = 0; k < counter; k++){
                if(pos[k] < current_min)
                    current_min = pos[k];
                if(pos[k] > current_max)
                    current_max = pos[k];
            }
            final_pos_min[j] = current_min;
            final_pos_max[j] = current_max;
        }

        // determine the winner min number and winner max number
        int left_most_str_index = line_lenght;
        int right_most_str_index = 0;
        for(int j = 0; j < 9; j++){
            if(final_pos_min[j] < left_most_str_index){
                left_most_str_index = final_pos_min[j];
                left_most_str = j+1;
            }
            if(final_pos_max[j] > right_most_str_index){
                right_most_str_index = final_pos_max[j];
                right_most_str = j+1;
            }
        }
        
        // calculate final number
        int sub_sum = 0;
        if(left_most_str_index < left_most_index){
            sub_sum = left_most_str * 10;
        }else{
            sub_sum = (left_most - '0') * 10;
        }
        if(right_most_str_index > right_most_index){
            sub_sum += right_most_str;
        }else{
            sub_sum += right_most - '0';
        }
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

    int total_sum = calculate02();
    printf("\n\ntotal Sum: %d\n", total_sum);

    // Free the block of memory allocated for each string
    for (size_t i = 0; i < total_lines; i++)
        free(lines[i]);

    free(lines);

    fclose(file);

    return 0;
}