#include "imagenes_p.h"
#include <iostream>
#include <fstream>
#include <iostream>

using namespace std;

//DEFINICIONES DE PARAMETRICAS
#define PGM_MAXMAXVAL 255
#define EPSILON 0.000000001
#define RADIX 2.0
#define SIGN(x,y) ((y)<0 ? -fabs(x) : fabs(x))
#define SWAP(a,b) {y=(a);(a)=(b);(b)=y;}
int tonoColor_p = 0;

imagenes_p::imagenes_p(){}
//-----------------------------CALCULOS-----------------------------
// LOCACIONES DE MATRIZ CON RANGO
double **allocate_matrix_p (int nrl, int nrh, int ncl, int nch)
{
    int i;
    double **m;
    m = (double **) malloc ((unsigned) (nrh - nrl + 1) * sizeof (double *));
    if (!m) fprintf (stderr, "memoria local no encontrada "), exit (1);
    m -= ncl;
    for (i = nrl; i <= nrh; i++) {
        m[i] = (double *) malloc ((unsigned) (nch - ncl + 1) * sizeof (double));
        if (!m[i]) fprintf (stderr, "memory allocation failure (allocate_matrix_p 2) "), exit (2);
        m[i] -= ncl;
    }
    return m;
}
//VECTOR DE LOACION
double *allocate_vector_p (int nl, int nh) {
    double *v;

    v = (double *) calloc (1, (unsigned) (nh - nl + 1) * sizeof (double));
    if (!v) fprintf (stderr, "memory allocation failure (allocate_vector_p) "), exit (1);

    return v - nl;
}
//MATRIZ DE CONCURRENCIA CON ANGULO 0
double** CoOcMat_Angle_0_p (int distance, u_int8_t **grays, int rows, int cols, int* tone_LUT, int tone_count)
{
    int d = distance;
    int x, y;
    int row, col, itone, jtone;
    double count=0.0;
    double** matrix = allocate_matrix_p (0, tone_count, 0, tone_count);

    for (itone = 0; itone < tone_count; ++itone)
        for (jtone = 0; jtone < tone_count; ++jtone)
            matrix[itone][jtone] = 0.0;

    for (row = 0; row < rows; ++row)
        for (col = 0; col < cols; ++col) {
            if (col + d < cols) {
                x = tone_LUT[grays[row][col]];
                y = tone_LUT[grays[row][col + d]];
                matrix[x][y]++;
                matrix[y][x]++;
                count += 2.0 ;
            }
        }

    for (itone = 0; itone < tone_count; ++itone){
          for (jtone = 0; jtone < tone_count; ++jtone){
            if (count==0.0)   /* protect from error */
               matrix[itone][jtone]=0.0;
               else matrix[itone][jtone] /= count;
          }
    }

    return matrix;
}
//INICIALIZAR FUNCIONES
double f1_asm (double **P, int Ng);

//RECURSOS DE LOS METODOS
double *allocate_vector_p (int nl, int nh);
double **allocate_matrix_p (int nrl, int nrh, int ncl, int nch);
void free_matrix(double **matrix,int nrh);


// CREAR ARRAY 2D CON LAS DIMENSIONES DEL DEGRADADO A GRISES
unsigned char** generarEscala_p(vector<vector<int>>  imagen, int rows, int cols){
    unsigned char **pGray;
       pGray = new unsigned char *[rows];
       for(int i = 0; i < rows; i++){
           pGray[i] = new unsigned char[cols];
       }
       for (int y = 0; y < rows; y++)
       {
           for (int x = 0; x < cols; x++)
           {
              if(imagen.data()[x][y] > 125){
                     pGray[y][x] = (u_int16_t)255;
              }
              else{
                    pGray[y][x] = (u_int16_t)0;
              }
           }
       }
    return pGray;
}



//0 ESCALA DE GRISES
double ** imagenes_p::ESCALAGRISES(vector<vector<int>>  imagen, int min, int max, int hilos) const{
    int row, col, rows, cols;
    cols = max; //weigth - col - max
    rows = min; //heigth - fil - min
    // CREAR ARRAY 2D CON LAS DIMENSIONES DEL DEGRADADO A GRISES
    unsigned char **pGray = generarEscala_p(imagen, rows,cols);
    int toneLUT[PGM_MAXMAXVAL + 1];		// toneLUT is an array that can hold 256 values
    int toneCount = 0;
    int iTone;
    //RELLENAR CON -1
    for(row = PGM_MAXMAXVAL; row >= 0; --row)
          toneLUT[row] = -1;
    for(row = rows - 1; row >= 0; --row){
          for(col = 0; col < cols; ++col){
              std::vector<int, std::allocator<int>> const *aux = imagen.data();
              toneLUT[(u_int8_t)aux[row][imagen.size() * row + col * 1]] = (u_int8_t)aux[row][imagen.size() * row + col * 1];
          }
    }
    for (row = PGM_MAXMAXVAL, toneCount = 0; row >= 0; --row){
          if (toneLUT[row] != -1){
              toneCount++;
          }
      }
    for (row = 0, iTone = 0; row <= PGM_MAXMAXVAL; row++){
          if (toneLUT[row] != -1)
            toneLUT[row] = iTone++;
      }
    double **pMatriz_p;
    int distancia = 1;
    pMatriz_p = CoOcMat_Angle_0_p(distancia, pGray, rows, col, toneLUT, toneCount);
    tonoColor_p = toneCount;
    return pMatriz_p;
}

//0 CONTADOR MATRIZ
int imagenes_p::ObtenertoneCount() const{
    return tonoColor_p;
}


void imagenes_p::generarExcel(double m_asm,
                            double m_contrast,
                            double m_corr,
                            double m_var,
                            double m_idm,
                            double m_savg,
                            double m_svar,
                            double m_sentropy,
                            double m_entropy,
                            double m_dvar,
                            double m_dentropy,
                            double m_icorr1,
                            double m_icorr2,
                            double m_maxcorr,
                            int hilos,
                            string path) const
{

    // file pointer
    fstream fout;
    // opens an existing csv file or creates a new file.
    fout.open(path, ios::out | ios::app);
    string name;
    // Insert the data to file
    fout << "SECOND ANGULAR MOMENT" << ", " << m_asm  << "\n";
    fout << "CORRELACION" << ", " << m_contrast  << "\n";
    fout << "DIFERENCIA ENTROPIA" << ", " << m_corr  << "\n";
    fout << "DIFERENCIA VARIANZA" << ", " << m_var  << "\n";
    fout << "ENTROPIA" << ", " << m_idm  << "\n";
    fout << "INVERSE DIFERENCE MOEMNT" << ", " << m_savg  << "\n";
    fout << "CONTRASTE" << ", " << m_svar  << "\n";
    fout << "INFORMATION MESURE CORRELATION 1" << ", " << m_sentropy << "\n";
    fout << "INFORMATION MESURE CORRELATION 2" << ", " << m_entropy  << "\n";
    fout << "MAXIMO CORRELATION COEFICIENT" << ", " << m_dvar  << "\n";
    fout << "SUM AVEREGE" << ", " << m_dentropy  << "\n";
    fout << "SUMA ENTROPIA" << ", " << m_icorr1  << "\n";
    fout << "SUM OF SQUARE VARIANCE" << ", " << m_icorr2  << "\n";
    fout << "SUM VARIANCE" << ", " << m_maxcorr  << "\n";
}



void imagenes_p::mensaje(string data) const
{
    cout << "\n" << data <<"\n";
}



