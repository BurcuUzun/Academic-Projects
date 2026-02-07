#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* * Simple Interpreter Project
 * Features: Variable set/show, arithmetic operations, and conditional jumps.
 */

struct Variable {
    char name[100];
    int value;
};

int main() 
{
    struct Variable memory[100] = {0};
    int var_count = 0;
    char program[100][100];
    int line_count = 0;

    while (1) 
    {
        if (fgets(program[line_count], 100, stdin) == NULL) break;
        program[line_count][strcspn(program[line_count], "\r\n")] = 0;
        if (strcmp(program[line_count], "exit") == 0) {
            line_count++;
            break;
        }
        line_count++;
    }

    for (int k = 0; k < line_count; k++)
    {
        char temp_line[100];
        strcpy(temp_line, program[k]); 
        
        char *command = strtok(temp_line, " ");
        if (command == NULL) continue;

        if (strcmp(command, "set") == 0) 
        {
            char *var_name = strtok(NULL, " ");
            char *val_str = strtok(NULL, " ");
            int val = atoi(val_str);

            int found = 0;
            for(int j = 0; j < var_count; j++) 
            {
                if(strcmp(memory[j].name, var_name) == 0) 
                {
                    memory[j].value = val;
                    found = 1; break;
                }
            }
            if(!found) 
            {
                strcpy(memory[var_count].name, var_name);
                memory[var_count].value = val;
                var_count++;
            }
        } 
        else if (strcmp(command, "show") == 0) 
        {
            char *var_name = strtok(NULL, " ");
            int found = 0;
            for(int j = 0; j < var_count; j++) 
            {
                if(strcmp(memory[j].name, var_name) == 0) 
                {
                    printf("%s = %d\n", memory[j].name, memory[j].value);
                    found = 1; break;
                }
            }
            if(!found) 
            { 
                printf("%s = 0\n", var_name);
                strcpy(memory[var_count].name, var_name);
                memory[var_count].value = 0;
                var_count++;
            }
        }
        else if (strcmp(command, "add") == 0 || strcmp(command, "sub") == 0) 
        {
            char *v1_name = strtok(NULL, " ");
            char *v2_name = strtok(NULL, " ");
            int idx1 = -1, idx2 = -1;

            for(int j = 0; j < var_count; j++) 
            {
                if(strcmp(memory[j].name, v1_name) == 0) idx1 = j;
                if(strcmp(memory[j].name, v2_name) == 0) idx2 = j;
            }

            if(idx1 == -1) { 
                strcpy(memory[var_count].name, v1_name);
                memory[var_count].value = 0;
                idx1 = var_count++;
            }
            int v2_val = 0;
            if(idx2 != -1) v2_val = memory[idx2].value;
            else 
            { 
                strcpy(memory[var_count].name, v2_name);
                memory[var_count].value = 0;
                var_count++;
            }

            if(command[0] == 'a') 
            { 
                memory[idx1].value += v2_val;
                if(memory[idx1].value > 99) memory[idx1].value = 99;
            } 
            else 
            { 
                memory[idx1].value -= v2_val;
                if(memory[idx1].value < 0) memory[idx1].value = 0;
            }
        }
        else if (strcmp(command, "goback") == 0) 
        {
            int lines = atoi(strtok(NULL, " "));
            char *vD_name = strtok(NULL, " ");
            char *vS_name = strtok(NULL, " ");
            int vD = 0, vS = 0;

            for(int j = 0; j < var_count; j++) 
            {
                if(strcmp(memory[j].name, vD_name) == 0) vD = memory[j].value;
                if(strcmp(memory[j].name, vS_name) == 0) vS = memory[j].value;
            }

            if (vD < vS) 
            {
                k = k - lines - 1;
            }
        }
    }
    return 0;
}