#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void){
      double angB, angE, angI;
      FILE *file;

      //Open a file for writing
      file = fopen("anglestable.txt","w");
      if (file == NULL)
      {
            printf("FIle does not exist. \n");
            
      }
      

       printf("AngleB? ");
      scanf("%lf",&angB);
       printf("AngleE? ");
      scanf("%lf",&angE);
       printf("AngleI? "); //increment value
      scanf("%lf",&angI);
       fprintf(file,"-------------------------------------------------\n");
	fprintf(file,"|\tang\t|\tsin(ang)\t|\tcos(ang)\t|\n");
	 fprintf(file,"-------------------------------------------------\n");
      /*printf("%3s %-11s %-11s \n","ang","sin(ang)","cos(ang)");
      printf("%3s %-11s %-11s \n","--------","--------","-------");*/
      for (double ang = angB; ang <= angE; ang += angI)
      {
           double rad = (ang*M_PI)/180.0;
           //printf("%3.0f %11.8f %11.8f \n", ang, sin(ang), cos(ang)); 
           fprintf(file,"|\t%3.0f\t|\t%11.8f\t|\t%11.8f\t|\n", ang, sin(ang), cos(ang));
           fprintf(file,"|\t%3.0f\t|\t%11.8f\t|\t%11.8f\t|\n", ang, sin(ang), cos(ang));
      }
      fprintf(file,"-------------------------------------------------\n");

      fclose(file);

      return 0;
}