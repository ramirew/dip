#ifndef IMAGENES_P_H
#define IMAGENES_P_H

#include <iostream>
#include <vector>

using namespace std;

class IMAGENES_P;

class IMAGENES_P
{
public:
    IMAGENES_P();
    void mensaje(string data) const;
    double ** ESCALAGRISES(vector<vector<int>>  imagen, int min, int max, int hilos) const;
    int ObtenertoneCount(vector<vector<int>>  imagen, int min, int max, int hilos) const;
    void generarExcel(double m_asm,
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
                      double m_maxcorr, int hilos) const;
};

#endif // IMAGENES_H
