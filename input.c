/********************************************************************************
* input.c: Definition av externa funktioner för inläsning av text och tal
*          från tangentbordet.
********************************************************************************/
#include "input.h"

/********************************************************************************
* readline: Läser in text från tangentbordet och lagrar i en sträng av angiven
*           storlek. Det nyradstecken som uppstår vid nedtryckning av ENTER-
*           tangenten tas bort genom att ersättas med ett nolltecken.
* 
*           - s   : Pekare till strängen där inläst innehåll skall lagras.
*           - size: Strängens storlek, dvs. antalet tecken denna rymmer.          
********************************************************************************/
void readline(char* s,
              const size_t size)
{
   fgets(s, (int)size, stdin);
   printf("\n");

   for (char* i = s; *i; ++i)
   {
      if (*i == '\n')
      {
         *i = '\0';
      }
   }

   return;
}

/********************************************************************************
* get_integer: Returnerar ett signerat heltal inläst från tangentbordet.
********************************************************************************/
int get_integer(void)
{
   char s[20] = { '\0' };
   readline(s, sizeof(s));
   return atoi(s);
}

/********************************************************************************
* get_double: Returnerar ett flyttal inläst från tangentbordet. Eventuella
*             kommatecken ersätts med punkter för att möjliggöra inmatning
*             både med punkt och kommatecken som decimaltecken.
********************************************************************************/
double get_double(void)
{
   char s[20] = { '\0' };
   readline(s, sizeof(s));

   for (char* i = s; *i; ++i)
   {
      if (*i == ',')
      {
         *i = '.';
      }
   }

   return atof(s);
}

/********************************************************************************
* get_integer: Returnerar ett osignerat heltal inläst från tangentbordet.
********************************************************************************/
size_t get_unsigned(void)
{
   return (size_t)get_integer();
}