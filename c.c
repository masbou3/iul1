#include <stdio.h>

int main() {
    int age = 20;           // entier
    float note ;  
    printf("quelle est ta note \n");
    scanf("%f" , &note);
    if (note>=10){
        printf("tu as reussi avec %.2f de moyenne \n ", note );
    } 
    else{
        printf("barra nayek t'as pas la moyenne ! ta moyenne est de  %.2f\n", note);
    }
    {
        /* code */
    }
    

    return 0;
}
