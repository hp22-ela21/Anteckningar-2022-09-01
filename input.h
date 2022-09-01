/********************************************************************************
* input.h: Innehåller funktionalitet för inläsning av text och tal från
*          tangentbordet.
********************************************************************************/
#ifndef INPUT_H_
#define INPUT_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/* Externa funktioner: */
void readline(char* s, 
              const size_t size);
int get_integer(void);
double get_double(void);
size_t get_unsigned(void);

#endif /* INPUT_H_ */