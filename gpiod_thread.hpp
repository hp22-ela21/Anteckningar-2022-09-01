/********************************************************************************
* gpiod_thread.hpp: Innehåller funktionalitet för implementering av GPIO-trådar,
*                   som möjliggör styrning av utsignalerna på GPIO-linjer via
*                   var sin tråd.
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
* gpiod_thread: Strukt för implementering av GPIO-trådar, där utsignalen på
*               given GPIO-linje togglas mellan att blinka med angiven
*               blinkhastighet samt vara avstängd.
********************************************************************************/
struct gpiod_thread
{
   /* Medlemmar: */
   gpiod_line* line = nullptr;     /* GPIO-linjepekare. */
   bool enabled = false;           /* Indikerar GPIO-linjens tillstånd (på/av). */
   std::size_t blink_speed_ms = 0; /* Blinkhastighet mätt i millisekunder. */

   /* Medlemsfunktioner: */
   gpiod_thread(void) { }
   gpiod_thread(const std::uint8_t pin,
                const char* alias,
                const std::size_t blink_speed_ms);
   void run(void);
};

#endif /* GPIOD_THREAD_HPP_ */