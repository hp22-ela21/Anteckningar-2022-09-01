/********************************************************************************
* input.c: Definition av externa funktioner f�r inl�sning av text och tal
*          fr�n tangentbordet.
********************************************************************************/
#include "input.h"

/********************************************************************************
* readline: L�ser in text fr�n tangentbordet och lagrar i en str�ng av angiven
*           storlek. Det nyradstecken som uppst�r vid nedtryckning av ENTER-
*           tangenten tas bort genom att ers�ttas med ett nolltecken.
* 
*           - s   : Pekare till str�ngen d�r inl�st inneh�ll skall lagras.
*           - size: Str�ngens storlek, dvs. antalet tecken denna rymmer.          
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
* get_integer: Returnerar ett signerat heltal inl�st fr�n tangentbordet.
********************************************************************************/
int get_integer(void)
{
   char s[20] = { '\0' };
   readline(s, sizeof(s));
   return atoi(s);
}

/********************************************************************************
* get_double: Returnerar ett flyttal inl�st fr�n tangentbordet. Eventuella
*             kommatecken ers�tts med punkter f�r att m�jligg�ra inmatning
*             b�de med punkt och kommatecken som decimaltecken.
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
* get_integer: Returnerar ett osignerat heltal inl�st fr�n tangentbordet.
********************************************************************************/
size_t get_unsigned(void)
{
   return (size_t)get_integer();
}