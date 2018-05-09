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

int main()
{
std::string crctocheck = "5e11b110";
int array_size = 1024; // define the size of character array
char * array = new char[array_size];
int position = 0; //this will be used incremently to fill characters in the array 
  
ifstream fin("test.txt", ios::in | ios::binary );

if(fin.is_open())//this loop run until end of file (eof) does not occur
{
    
    while(!fin.eof() && position < array_size)
    {
        fin.get(array[position]); //reading one character from file to array
        position++;
    }
    
    array[position-1] = '\0'; //placing character array terminating character
}

cout << " " << endl;

if (crc32(array,crctocheck))
{
cout << "true" << endl;
}
else
{
cout << "false" << endl;
}

//cout << std::hex << crc32(array,crc2) << endl;
//cout << crc2 << endl;


char x;
cin >> x;
return 0;
}