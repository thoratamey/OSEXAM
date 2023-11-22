#include <stdio.h>
int main(){
char filename[100];
printf("Enter the filename:");
scanf("%s",filename);
FILE*file=fopen(filename,"r");
if(file==NULL){
printf("Error opening the file.\n");
return 1;
}
int wordCount=0;
char ch;
while((ch=fgetc(file))!=EOF){
if(ch==' ' || ch=='\n' || ch=='\t'){
wordCount++;
}
}
printf("Word count in %s:%d\n",filename,wordCount);
fclose(file);
return 0;
}
