#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads a string from an input file and returns a pointer to it
char* readline(FILE* input){
    char* str = calloc(1, sizeof(char));
    char ch;
    
    ch = getc(input);
    while (ch != '\n' && ch != EOF){
        str = realloc(str, strlen(str)*sizeof(char) + 2*sizeof(char));
        strncat(str, &ch, 1);
        ch = getc(input);
    }
    strncat(str, "\0", 1);

    return str;
}

// Recieves a text and replace all the old_str contained in it with the new_str
char* replaceStr(char* text, char* old_str, char* new_str) { 
    char* new_text; 
    new_text = calloc(150, sizeof(char));

    int i = 0; 
    while (*text && strlen(new_text)<100) { 
        if (strstr(text, old_str) == text) { 
            strcpy(&new_text[i], new_str); 
            i += strlen(new_str); 
            text += strlen(old_str); 
        } 
        else
            new_text[i++] = *text++; 
    } 
  
    new_text[i] = '\0'; 
    return new_text; 
} 

// Prits at most the first 100 characters of a string
void printStr(char* str){
    for(int i=0; i<100 && i < (int) strlen(str); i++){
        printf("%c", str[i]);
    }
    printf("\n");
    return;
}

int main(){
    char* text = NULL;
    char* new_str = NULL;
    char* old_str = NULL;
    char* new_text = NULL;

    // Reading all imput lines
    char* line = readline(stdin);
    for(int i=1; line[0] != '\0'; i++){
        // Checks what the line is based on the format of the input
        if(i%3 == 1) text = line;
        if(i%3 == 2) old_str = line;
        if(i%3 == 0) new_str = line;

        if(i%3 == 0 && i != 0){
            new_text = replaceStr(text, old_str, new_str);
            printStr(new_text);
            
            free(new_text);
            free(text);
            free(old_str);
            free(new_str);
        }
    
        line = readline(stdin);
    }
    free(line);

    return 0;
}
