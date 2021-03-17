/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Lianne Perez
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

char command[100]; // to store the command
char before[100]; //store the command before pipe symbol
char after[100]; //store the command after pipe symbol
int i,j=0,k=0; // counters
int flag = 0;
int length;

int main(int argc, char** argv)
{
    printf("Enter your command:\n");
    fgets(command, 100, stdin);
    
    length = strlen(command) - 1;
    for (i=0;i<length;i++){
        if (command[i] != '|' && flag == 0){
            before[j] = command[i];
            j++;
        }
        else if(command[i] == '|') {
            flag = 1;
            i++;
        }
        else{
            after[k] = command[i];
            k++;
        }
    }
    
    int fd[2];
    pipe(fd);
    if (fork()==0){
        dup2(fd[1],1); 
        close(fd[0]);
        system(before);
        exit(0);
    }
    else{
        dup2(fd[0],0); 
        close(fd[1]);
        system(after);
    }
    
    return (EXIT_SUCCESS);
}