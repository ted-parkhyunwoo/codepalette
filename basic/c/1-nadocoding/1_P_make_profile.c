#include <stdio.h>

int main(void)
{   
    //str not use & in front of var in scanf
    char name[256], crime[256];
    printf("What is your name? : ");
    scanf("%s", name);
    
    int age;
    printf("How old are you? : ");
    scanf("%d", &age);

    float weight;
    printf("What is your weight? : ");
    scanf("%f", &weight);
    
    //double use %lf instead of %f
    double height;
    printf("What is your height? : ");
    scanf("%lf", &height);
    
    printf("What is your crime? : ");
    scanf("%s", crime);

    printf("\nname : %s\nage : %d\nweight : %f\nheight : %lf\ncrime : %s\n", name, age, weight, height, crime);

    return 0;
}
