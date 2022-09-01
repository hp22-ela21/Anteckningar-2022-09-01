/********************************************************************************
* gpiod_thread.h: Definition av externa funktioner för implementering av
*                 GPIO-trådar via strukten gpiod_thread.
********************************************************************************/
#include "gpiod_thread.h"

/* Statiska funktioner: */
static struct gpiod_line* gpiod_line_new(const uint8_t pin);

/********************************************************************************
* gpiod_thread_new: Initierar en ny GPIO-tråd, där GPIO-linjen på angivet 
*                   pin-nummer används. GPIO-linjen sätts till utport samt
*                   inaktiverad vid start, vilket medför låg utsignal när
*                   en ny GPIO-tråd startas (via funktionen gpiod_thread_run):
* 
*                   - self          : Pekare till GPIO-tråden.
*                   - pin           : GPIO-linjens PIN-nummer.
*                   - alias         : Alias/namn för GPIO-linjen.
*                   - blink_speed_ms: GPIO-linjens blinkhastighet i aktiverat
*                                     tillstånd, då utsignalen togglas.
********************************************************************************/
void gpiod_thread_new(struct gpiod_thread* self,
                      const uint8_t pin,
                      const char* alias,
                      const size_t blink_speed_ms)
{
   self->line = gpiod_line_new(pin);
   self->enabled = false;
   self->blink_speed_ms = blink_speed_ms;
   gpiod_line_request_output(self->line, alias, 0);
   return;
}

/********************************************************************************
* gpiod_thread_run: Kör tråd för GPIO-linje, där utsignalen antingen togglas
*                   med angiven blinkhastighet för att generera en blinkning
*                   eller hållas avstängd.
* 
*                   - arg: Generisk pekare till angiven GPIO-tråd, som måste
*                          typomvandlas till korrekt pekartyp innan användning.
********************************************************************************/
void* gpiod_thread_run(void* arg)
{
   struct gpiod_thread* self = (struct gpiod_thread*)arg;

   while (1)
   {
      if (self->enabled)
      {
         gpiod_line_set_value(self->line, 1);
         usleep(self->blink_speed_ms * 1000);
         gpiod_line_set_value(self->line, 0);
         usleep(self->blink_speed_ms * 1000);
      }
      else
      {
         gpiod_line_set_value(self->line, 0);
      }
   }

   return 0;
}

/********************************************************************************
* gpiod_line_new: Returnerar en pekare till en GPIO-linjen på angivet pin-nummer.
*
*                 - pin: GPIO-linjens PIN-nummer.
********************************************************************************/
static struct gpiod_line* gpiod_line_new(const uint8_t pin)
{
   static struct gpiod_chip* chip0 = 0;
   if (!chip0) chip0 = gpiod_chip_open("/dev/gpiochip0");
   struct gpiod_line* self = gpiod_chip_get_line(chip0, pin);
   return self;
}