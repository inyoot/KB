#include <stdio.h>
#include <conio.h>

int map[7][5] =	  {	{ 1, 4, 2, 5,-1 },
					{ 0, 4, 6, 5,-1 },
            		{ 0, 4, 3, 6, 5 },
               		{ 2, 4, 6,-1,-1 },
               		{ 0, 1, 6, 3, 2 },
               		{ 2, 6, 1, 0,-1 },
               		{ 2, 3, 4, 1, 5 }};


int mapColors[7] = { 0, 0, 0, 0, 0, 0, 0 };

bool explore(int, int);
bool okToColor(int , int);
void printMap();

void main() 
{	bool result = explore(0, 1);
   	if(result)
		printf("Berhasil!!!\n");
   	else
   		printf("Gagal!!!\n");
	printMap();
}

bool explore(int country, int color) 
{		if (country >= 7) 
			return true;
		
	if (okToColor(country, color)) {
		mapColors[country] = color;
		
			for (int i = 1; i <= 4; i++) {
				if (explore(country + 1, i))
         				return true;
			}
		}
		return false;
}

bool okToColor(int country, int color) 
{	int ithAdjCountry;	

	for (int i = 0; i < 5; i++) {
   		if(map[country][i] != -1)
      		ithAdjCountry = map[country][i];
		
		if (mapColors[ithAdjCountry] == color)
			return false;
   	}
	return true;
}

void printMap() {
	for (int i = 0; i < 7; i++) {   			
		//cout << "map[" << i << "] berwarna ";    
		printf("map[%i] berwarna ", i);
		switch (mapColors[i]) {
  			case 0: printf("Putih"); break;
         	case 1: printf("Merah"); break;
         	case 2: printf("Kuning"); break;
         	case 3: printf("Hijau"); break;
       		case 4: printf("Biru"); break;     	
		}   				
		printf("\n");
	}
	while(!_kbhit());
}