#include <stdio.h>
char *program = "#include <stdio.h>%cchar *program = %c%s%c;%cint main()%c{printf(%chello world%c);FILE *fp;fp=fopen(%cmain2.c%c,%cw%c);fprintf(fp,program, 10, 34, program, 34,10,10,34,34,34,34,34,34,10);fclose(fp);return 0;}%c";
int main()
{printf("hello world");FILE *fp;fp=fopen("main2.c","w");fprintf(fp,program, 10, 34, program, 34,10,10,34,34,34,34,34,34,10);fclose(fp);return 0;}
