#include <stdio.h>
#include <string.h>
void cat_str(char chuoi[], char str[], char xau[])
{
   strcpy(chuoi, str);
   strcat(chuoi," ");
   strcat(chuoi, xau);
}
int main()
{
    char str[5] , xau[10], chuoi[20];
    strcpy(str,"01a");
    strcpy(xau,"chieu di");
    cat_str(chuoi,str,xau);
    
    printf("%s\n", str);
    printf("%s\n",xau);
    printf("%s\n",chuoi);
    return 0;
}