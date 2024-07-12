#include <stdio.h>
#include <math.h>

int main(void){
      double angB, angE, angI;
       printf("AngleB? ");
      scanf("%lf",&angB);
       printf("AngleE? ");
      scanf("%lf",&angE);
       printf("AngleI? "); //increment value
      scanf("%lf",&angI);
      printf("-----------------------------------------------------------------\n");
	printf("|\tang\t|\tsin(ang)\t|\tcos(ang)\t|\n");
	printf("-----------------------------------------------------------------\n");
      /*printf("%3s %-11s %-11s \n","ang","sin(ang)","cos(ang)");
      printf("%3s %-11s %-11s \n","--------","--------","-------");*/
      for (double ang = angB; ang <= angE; ang += angI)
      {
           double rad = (ang*M_PI)/180.0;
           //printf("%3.0f %11.8f %11.8f \n", ang, sin(ang), cos(ang)); 
           printf("|\t%3.0f\t|\t%11.8f\t|\t%11.8f\t|\n", ang, sin(ang), cos(ang));
           printf("|\t%3.0f\t|\t%11.8f\t|\t%11.8f\t|\n", ang, sin(ang), cos(ang));
      }
      printf("-----------------------------------------------------------------\n");

      return 0;
}