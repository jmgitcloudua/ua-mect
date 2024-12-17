#include <stdio.h>

//program to read a file and print its contents

int main(){
    FILE *fp;
    //char ch;
    int I, H, O;
    int li, ui, lo, uo;
    double w;
    fp = fopen("weights.txt", "r");
    if (fp == NULL){
        fprintf(stderr, "Error occured on trying to open a file \n");
        return 1;
    }
    fscanf(fp, "%d %d %d", &I, &H, &O);
    printf("I = %d, H = %d, O = %d\n", I, H, O);
    while (fscanf(fp,"%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w) == 5)
    {
        // process the data
        printf("Li -> %d:%d %d:%d %f\n", li, ui, lo, uo, w);
    }
    
    // while ((ch = fgetc(fp)) != EOF){
    //     printf("%c", ch);
    // }
    fclose(fp);
    return 0;
}