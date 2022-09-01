/*************************************************************************************
* main.cpp: Implementerar flertrådning för styrning av tre GPIO-linjer via var sin 
*           tråd. Via inmatning av heltal 1 - 3 kan användaren toggla tillståndet på
*           respektive GPIO-linje mellan att blinka samt vara släckta.
*
*           Kompilera programmet och skapa en körbar fil main via följande kommando:
*           $ g++ main.cpp gpiod_thread.cpp -o main -Wall -l gpiod -l pthread
*
*           Kör sedan programmet via följande kommando:
*           $ ./main
**************************************************************************************/
#include "gpiod_thread.hpp"
#include <string>

/*************************************************************************************
* readline: Läser in text från tangenbordet och lagrar i angiven sträng.
* 
*           - s: Strängen där inmatat innehåll skall lagras.
**************************************************************************************/
static void readline(std::string& s)
{
   std::getline(std::cin, s);
   std::cout << "\n";
   return;
}

/*************************************************************************************
* main: Deklarerar tre GPIO-trådar, som initieras via angivna PIN-nummer, alias samt
*       blinkhastigheter. De tre trådarna initieras och exekverar sedan kontinuerligt.
*       Trådarna synkroniseras, så att om en given tråd mot förmodan avslutas så
*       väntar denna in övriga trådar innan programmet fortsätter.
**************************************************************************************/
int main(void)
{
   gpiod_thread t1(17, "Line1", 500);
   gpiod_thread t2(22, "Line2", 100);
   gpiod_thread t3(23, "Line3", 50);

   std::thread thread1(&gpiod_thread::run, &t1);
   std::thread thread2(&gpiod_thread::run, &t2);
   std::thread thread3(&gpiod_thread::run, &t3);

   while (1)
   {
      std::string s;

      std::cout << "Enter number 1 - 3 to toggle the GPIO lines:\n";
      readline(s);

      if (s == "1")
      {
         t1.enabled = !t1.enabled;
         std::cout << "Toggling " << gpiod_line_consumer(t1.line) << "!\n\n";
      }
      else if (s == "2")
      {
         t2.enabled = !t2.enabled;
         std::cout << "Toggling " << gpiod_line_consumer(t2.line) << "!\n\n";
      }
      else if (s == "3")
      {
         t3.enabled = !t3.enabled;
         std::cout << "Toggling " << gpiod_line_consumer(t3.line) << "!\n\n";
      }
   }

   thread1.join();
   thread2.join();
   thread3.join();

   return 0;
}