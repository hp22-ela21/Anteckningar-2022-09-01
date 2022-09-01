/********************************************************************************
* gpiod_thread.cpp: Definition av externa funktioner f�r implementering av
*                   GPIO-tr�dar via strukten gpiod_thread.
********************************************************************************/
#include "gpiod_thread.hpp"

/* Statiska funktioner: */
static gpiod_line* gpiod_line_new(const std::uint8_t pin);

/********************************************************************************
* gpiod_thread: Initierar en ny GPIO-tr�d, d�r GPIO-linjen p� angivet pin-nummer
*               anv�nds. GPIO-linjen s�tts till utport samt inaktiverad vid
*               start, vilket medf�r l�g utsignal n�r en ny GPIO-tr�d startas.
*
*                   - pin           : GPIO-linjens PIN-nummer.
*                   - alias         : Alias/namn f�r GPIO-linjen.
*                   - blink_speed_ms: GPIO-linjens blinkhastighet i aktiverat
*                                     tillst�nd, d� utsignalen togglas.
********************************************************************************/
gpiod_thread::gpiod_thread(const std::uint8_t pin,
                           const char* alias,
                           const std::size_t blink_speed_ms)
{
   this->line = gpiod_line_new(pin);
   this->blink_speed_ms = blink_speed_ms;
   gpiod_line_request_output(this->line, alias, 0);
   return;
}

/********************************************************************************
* run: K�r tr�d f�r GPIO-linje, d�r utsignalen antingen togglas med angiven 
*      blinkhastighet f�r att generera en blinkning eller h�llas avst�ngd.
********************************************************************************/
void gpiod_thread::run(void)
{
   while (1)
   {
      if (this->enabled)
      {
         gpiod_line_set_value(this->line, 1);
         usleep(this->blink_speed_ms * 1000);
         gpiod_line_set_value(this->line, 0);
         usleep(this->blink_speed_ms * 1000);
      }
      else
      {
         gpiod_line_set_value(this->line, 0);
      }
   }

   return;
}

/********************************************************************************
* gpiod_line_new: Returnerar en pekare till en GPIO-linjen p� angivet pin-nummer.
*
*                   - pin: GPIO-linjens PIN-nummer.
********************************************************************************/
static gpiod_line* gpiod_line_new(const std::uint8_t pin)
{
   static gpiod_chip* chip0 = nullptr;
   if (!chip0) chip0 = gpiod_chip_open("/dev/gpiochip0");
   gpiod_line* self = gpiod_chip_get_line(chip0, pin);
   return self;
}