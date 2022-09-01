/*************************************************************************************
* main.c: Implementerar flertrådning för styrning av tre GPIO-linjer via var sin tråd.
*         Via inmatning av heltal 1 - 3 kan användaren toggla tillståndet på
*         respektive GPIO-linje mellan att blinka samt vara släckta.
* 
*         Kompilera programmet och skapa en körbar fil main via följande kommando:
*         $ gcc main.c gpiod_thread.c input.c -o main -Wall -l gpiod -l pthread
* 
*         Kör sedan programmet via följande kommando:
*         $ ./main
**************************************************************************************/
#include "gpiod_thread.h"
#include "input.h"

/*************************************************************************************
* main: Deklarerar tre GPIO-trådar, som initieras via angivna PIN-nummer, alias samt
*       blinkhastigheter. De tre trådarna initieras och exekverar sedan kontinuerligt.
*       Trådarna synkroniseras, så att om en given tråd mot förmodan avslutas så 
*       väntar denna in övriga trådar innan programmet fortsätter.
**************************************************************************************/
int main(void)
{
   struct gpiod_thread t1, t2, t3;
   pthread_t pthread1, pthread2, pthread3;

   gpiod_thread_new(&t1, 17, "Line1", 500);
   gpiod_thread_new(&t2, 22, "Line2", 100);
   gpiod_thread_new(&t3, 23, "Line3", 50);

   pthread_create(&pthread1, 0, &gpiod_thread_run, &t1);
   pthread_create(&pthread2, 0, &gpiod_thread_run, &t2);
   pthread_create(&pthread3, 0, &gpiod_thread_run, &t3);

   while (1)
   {
      printf("Enter number 1 - 3 to toggle the GPIO lines:\n");
      const size_t val = get_unsigned();

      if (val == 1)
      {
         t1.enabled = !t1.enabled;
         printf("Toggling %s!\n\n", gpiod_line_consumer(t1.line));
      }
      else if (val == 2)
      {
         t2.enabled = !t2.enabled;
         printf("Toggling %s!\n\n", gpiod_line_consumer(t2.line));
      }
      else if (val == 3)
      {
         t3.enabled = !t3.enabled;
         printf("Toggling %s!\n\n", gpiod_line_consumer(t3.line));
      }
   }

   pthread_join(pthread1, 0);
   pthread_join(pthread2, 0);
   pthread_join(pthread3, 0);

   return 0;
}