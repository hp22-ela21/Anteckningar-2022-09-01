/********************************************************************************
* gpiod_thread.h: Innehåller funktionalitet för implementering av GPIO-trådar,
*                 som möjliggör styrning av utsignalerna på GPIO-linjer via
*                 var sin tråd.
********************************************************************************/
#ifndef GPIOD_THREAD_H_
#define GPIOD_THREAD_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <gpiod.h>
#include <unistd.h>
#include <pthread.h>

/********************************************************************************
* gpiod_thread: Strukt för implementering av GPIO-trådar, där utsignalen på 
*               given GPIO-linje togglas mellan att blinka med angiven 
*               blinkhastighet samt vara avstängd.
********************************************************************************/
struct gpiod_thread
{
   struct gpiod_line* line; /* GPIO-linjepekare. */
   bool enabled;            /* Indikerar GPIO-linjens tillstånd (på/av). */
   size_t blink_speed_ms;   /* Blinkhastighet mätt i millisekunder. */
};

/* Externa funktioner: */
void gpiod_thread_new(struct gpiod_thread* self,
                      const uint8_t pin,
                      const char* alias,
                      const size_t blink_speed_ms);
void* gpiod_thread_run(void* arg);

#endif /* GPIOD_THREAD_H_ */