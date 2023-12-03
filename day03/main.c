#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fileRead.h"

#define MORE_LINES 1024
#define MORE_CHARS 1024

char** lines;
size_t total_lines = 0;
size_t total_chars = 0;

typedef struct{
    int value;
    int length;
    int* x;
    int* y;
} number;

number* all_numbers;
int all_numbers_index = 0;

int total_sum = 0;

void freeNumbers(){
    for(int i = 0; i < all_numbers_index; i++){
        free(all_numbers[i].x);
        free(all_numbers[i].y);
    }
    free(all_numbers);
}

void calculate01(){

    all_numbers = malloc(sizeof(number) * total_lines * 140);

    for(int i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);

        bool is_new_number = false;
        int curr_value = 0;
        int curr_lenght = 0;
        int *curr_x = malloc(sizeof(int)*141);
        int *curr_y = malloc(sizeof(int)*141);

        for(int j = 0; j < line_lenght; j++){
            if(lines[i][j] <= '9' && lines[i][j] >= '0' && lines[i][j] != '\n'){
                if(is_new_number == false){
                    is_new_number = true;
                    curr_value = (lines[i][j] - '0');
                    curr_x[curr_lenght] = i;
                    curr_y[curr_lenght] = j;
                    curr_lenght++;
                }else{
                    curr_value = curr_value * 10;
                    curr_value += (lines[i][j] - '0');
                    curr_x[curr_lenght] = i;
                    curr_y[curr_lenght] = j;
                    curr_lenght++;
                }
            }else{
                if(is_new_number == true){
                    number new_number;
                    new_number.value = curr_value;
                    new_number.length = curr_lenght;
                    new_number.x = malloc(sizeof(int) * curr_lenght);
                    new_number.y = malloc(sizeof(int) * curr_lenght);
                    for(int k = 0; k < curr_lenght; k++){
                        new_number.x[k] = curr_x[k];
                        new_number.y[k] = curr_y[k];
                    }
                    all_numbers[all_numbers_index] = new_number;
                    all_numbers_index++;
                    is_new_number = false;

                    // reset
                    curr_value = 0;
                    curr_lenght = 0;
                }
            }
        }

        free(curr_x);
        free(curr_y);
    }

    for(int i = 0; i < all_numbers_index; i++){
        printf("%d \n", all_numbers[i].value);
    }

    for(int i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);

        for(int j = 0; j < line_lenght; j++){
            if((lines[i][j] >= '!' && lines[i][j] <= '/' && lines[i][j] != '.') || 
               (lines[i][j] >= ':' && lines[i][j] <= '~')){
                
                // found special character
                // check every number if it is in range
                for(int k = 0; k < all_numbers_index; k++){
                    // check every coordinate of number. It is in range when one coordinate is in range
                    int sub_sum = 0;
                    for(int l = 0; l < all_numbers[k].length; l++){
                        int diff_x = abs(all_numbers[k].x[l] - i);
                        int diff_y = abs(all_numbers[k].y[l] - j);
                        
                        if(diff_x <= 1 && diff_y <= 1){
                            sub_sum = all_numbers[k].value;
                        }
                    }
                    if(sub_sum != 0)
                        printf("\nvalid number: %d", sub_sum);
                    total_sum += sub_sum;
                }
            }
        }
    }

    printf("\n Total Sum: %d \n ", total_sum);
    
    freeNumbers();
}

void calculate02(){

    all_numbers = malloc(sizeof(number) * total_lines * 140);

    for(int i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);

        bool is_new_number = false;
        int curr_value = 0;
        int curr_lenght = 0;
        int *curr_x = malloc(sizeof(int)*141);
        int *curr_y = malloc(sizeof(int)*141);

        for(int j = 0; j < line_lenght; j++){
            if(lines[i][j] <= '9' && lines[i][j] >= '0' && lines[i][j] != '\n'){
                if(is_new_number == false){
                    is_new_number = true;
                    curr_value = (lines[i][j] - '0');
                    curr_x[curr_lenght] = i;
                    curr_y[curr_lenght] = j;
                    curr_lenght++;
                }else{
                    curr_value = curr_value * 10;
                    curr_value += (lines[i][j] - '0');
                    curr_x[curr_lenght] = i;
                    curr_y[curr_lenght] = j;
                    curr_lenght++;
                }
            }else{
                if(is_new_number == true){
                    number new_number;
                    new_number.value = curr_value;
                    new_number.length = curr_lenght;
                    new_number.x = malloc(sizeof(int) * curr_lenght);
                    new_number.y = malloc(sizeof(int) * curr_lenght);
                    for(int k = 0; k < curr_lenght; k++){
                        new_number.x[k] = curr_x[k];
                        new_number.y[k] = curr_y[k];
                    }
                    all_numbers[all_numbers_index] = new_number;
                    all_numbers_index++;
                    is_new_number = false;

                    // reset
                    curr_value = 0;
                    curr_lenght = 0;
                }
            }
        }

        free(curr_x);
        free(curr_y);
    }

    for(int i = 0; i < all_numbers_index; i++){
        printf("%d \n", all_numbers[i].value);
    }

    for(int i = 0; i < total_lines; i++){
        size_t line_lenght = strlen(lines[i]);

        for(int j = 0; j < line_lenght; j++){
            if(lines[i][j] == '*'){

                int gears[6];
                int num_gears = 0;

                // found special character
                // check every number if it is in range
                for(int k = 0; k < all_numbers_index; k++){
                    bool valid_number = false;

                    // check every coordinate of number. It is in range when one coordinate is in range
                    for(int l = 0; l < all_numbers[k].length; l++){
                        int diff_x = abs(all_numbers[k].x[l] - i);
                        int diff_y = abs(all_numbers[k].y[l] - j);
                        
                        if(diff_x <= 1 && diff_y <= 1){
                            valid_number = true;
                        }
                    }
                    if(valid_number){
                        gears[num_gears] = all_numbers[k].value;
                        num_gears++;
                    }
                }

                // add gear ratio to total sum when it is valid
                if(num_gears == 2){
                    printf("valid gears: %d | %d\n", gears[0], gears[1]);
                    int sub_ratio = gears[0] * gears[1];
                    total_sum += sub_ratio;
                }

                // reset
                num_gears = 0;
            }
        }
    }

    printf("\n Total Sum: %d \n ", total_sum);
    
    freeNumbers();
}

int main(){
    
    FILE* file;
    file = fopen("input.txt", "r");
    int error = readFile(file, lines, &total_lines, MORE_LINES, MORE_CHARS);
    if(error != 0)
        return error;

    calculate02();

    // Free the block of memory allocated for each string
    for (size_t i = 0; i < total_lines; i++)
        free(lines[i]);

    free(lines);
}