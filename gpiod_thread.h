/********************************************************************************
* gpiod_thread.h: Inneh�ller funktionalitet f�r implementering av GPIO-tr�dar,
*                 som m�jligg�r styrning av utsignalerna p� GPIO-linjer via
*                 var sin tr�d.
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
* gpiod_thread: Strukt f�r implementering av GPIO-tr�dar, d�r utsignalen p� 
*               given GPIO-linje togglas mellan att blinka med angiven 
*               blinkhastighet samt vara avst�ngd.
********************************************************************************/
struct gpiod_thread
{
   struct gpiod_line* line; /* GPIO-linjepekare. */
   bool enabled;            /* Indikerar GPIO-linjens tillst�nd (p�/av). */
   size_t blink_speed_ms;   /* Blinkhastighet m�tt i millisekunder. */
};

/* Externa funktioner: */
void gpiod_thread_new(struct gpiod_thread* self,
                      const uint8_t pin,
                      const char* alias,
                      const size_t blink_speed_ms);
void* gpiod_thread_run(void* arg);

#endif /* GPIOD_THREAD_H_ */