/********************************************************************************
* gpiod_thread.hpp: Inneh�ller funktionalitet f�r implementering av GPIO-tr�dar,
*                   som m�jligg�r styrning av utsignalerna p� GPIO-linjer via
*                   var sin tr�d.
********************************************************************************/
#ifndef GPIOD_THREAD_HPP_
#define GPIOD_THREAD_HPP_

/* Inkluderingsdirektiv: */
#include <iostream>
#include <thread>
#include <cstdint>

#include <gpiod.h>
#include <unistd.h>

/********************************************************************************
* gpiod_thread: Strukt f�r implementering av GPIO-tr�dar, d�r utsignalen p�
*               given GPIO-linje togglas mellan att blinka med angiven
*               blinkhastighet samt vara avst�ngd.
********************************************************************************/
struct gpiod_thread
{
   /* Medlemmar: */
   gpiod_line* line = nullptr;     /* GPIO-linjepekare. */
   bool enabled = false;           /* Indikerar GPIO-linjens tillst�nd (p�/av). */
   std::size_t blink_speed_ms = 0; /* Blinkhastighet m�tt i millisekunder. */

   /* Medlemsfunktioner: */
   gpiod_thread(void) { }
   gpiod_thread(const std::uint8_t pin,
                const char* alias,
                const std::size_t blink_speed_ms);
   void run(void);
};

#endif /* GPIOD_THREAD_HPP_ */