#ifndef LIBRERIAGEOMETRIA_H_INCLUDED
#define LIBRERIAGEOMETRIA_H_INCLUDED

void llenarMatriz(int matriz[FILAS][COLUMNAS], int filas, int columnas);
void mostrarMatriz(int matriz[FILAS][COLUMNAS], int filas, int columnas);
int sumarElementosMatriz(int matriz[FILAS][COLUMNAS], int filas, int columnas);
int sumarParesMatriz(int matriz[FILAS][COLUMNAS], int filas, int columnas);
int sumarImparesMatriz(int matriz[FILAS][COLUMNAS], int filas, int columnas);
void mostrarSumaColumnas(int matriz[FILAS][COLUMNAS], int filas, int columnas);
void mostrarSumaFilas(int matriz[FILAS][COLUMNAS], int filas, int columnas);
void mostrarMatrizTranspuesta(int matriz[FILAS][COLUMNAS], int filas, int columnas);
#include  "libreriaGeometria.cpp"

#endif // LIBRERIAGEOMETRIA_H_INCLUDED

