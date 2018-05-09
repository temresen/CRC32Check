#include "stdafx.h"

using namespace std;

bool crc32(char *message, std::string crctocheck) 
{
   int i, j;

   unsigned int byte, crc;

   // crc hex to rcr decimal
   unsigned int crc2 = 0;
   unsigned int digit = 1;
   
   for (int f = crctocheck.length()-1; f >= 0; f--)
   {
       if (crctocheck[f]<='9')
       {
           crc2 += (crctocheck[f] - '0') * digit;
       }
       
       else
       {
           crc2 += (crctocheck[f]- 'a' + 10) * digit;
       }
       
       digit *= 16;
   }

   // get buffer crc
   i = 0;
   crc = 0xFFFFFFFF;
   while (message[i] != 0) 
   {
       byte = (unsigned char)message[i];    // Get next byte.
       crc = crc ^ byte;
       
       for(j = 7; j >= 0; j--)
       {
           crc = (crc >> 1) ^ (crc & 1 ? 0xEDB88320 : 0);
       }
       
       i = i + 1;
   }

return (~crc == crc2);
}
