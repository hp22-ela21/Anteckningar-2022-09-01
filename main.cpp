/*************************************************************************************
* main.cpp: Implementerar flertr�dning f�r styrning av tre GPIO-linjer via var sin 
*           tr�d. Via inmatning av heltal 1 - 3 kan anv�ndaren toggla tillst�ndet p�
*           respektive GPIO-linje mellan att blinka samt vara sl�ckta.
*
*           Kompilera programmet och skapa en k�rbar fil main via f�ljande kommando:
*           $ g++ main.cpp gpiod_thread.cpp -o main -Wall -l gpiod -l pthread
*
*           K�r sedan programmet via f�ljande kommando:
*           $ ./main
**************************************************************************************/
#include "gpiod_thread.hpp"
#include <string>

/*************************************************************************************
* readline: L�ser in text fr�n tangenbordet och lagrar i angiven str�ng.
* 
*           - s: Str�ngen d�r inmatat inneh�ll skall lagras.
**************************************************************************************/
static void readline(std::string& s)
{
   std::getline(std::cin, s);
   std::cout << "\n";
   return;
}

/*************************************************************************************
* main: Deklarerar tre GPIO-tr�dar, som initieras via angivna PIN-nummer, alias samt
*       blinkhastigheter. De tre tr�darna initieras och exekverar sedan kontinuerligt.
*       Tr�darna synkroniseras, s� att om en given tr�d mot f�rmodan avslutas s�
*       v�ntar denna in �vriga tr�dar innan programmet forts�tter.
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