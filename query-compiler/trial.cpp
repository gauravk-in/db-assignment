#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class mystring {
public:
   char *str;

   mystring operator=(char *name);
   mystring operator=(uint64_t val);
   int operator==(uint64_t val);
};

mystring mystring::operator=(char *name )
{
   if(!name) {
      str=NULL;
   }
   else {
      str=(char*)malloc(sizeof(char)*strlen(name));
      strcpy(str, name);
   }
   return *this;
}

mystring mystring::operator=(uint64_t val)
{
   str=(char*)malloc(sizeof(char)*20);
   sprintf(str, "%llu", val);
   return *this;
}

int mystring::operator==(uint64_t val)
{
   char temp_str[20];
   sprintf(temp_str, "%llu", val);
   return !strcmp(str, temp_str);
}

int main()
{
   mystring t;
   char p[50]="Gaurav";

   t=p;
   printf("%s\n",t.str);

   t=(uint64_t)200;
   printf("%s\n",t.str);

   if(t==200)
      printf("Equal\n");
   else
      printf("Not Equal\n");

   return 0;
}