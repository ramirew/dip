#include "libreriaGeometria.h"
#include<iostream>
#include<cmath>
using namespace std;

int convex(int dato)
{
int res; 
int coc,resto; 
res = 0;
do
{
cociente = dato / 10;
resto = dato % 10; 

res = res * 10 + resto;
dato = cociente

}while (dato != 0);
return res 
}