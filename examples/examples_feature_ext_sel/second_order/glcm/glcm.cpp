#include <iostream>
#include <vector>
#include <string>
#include "dicom_read/dicomutils.h"
#include "dicom_read/DicomReader.h"
#include "fcm/fcm.h"
//LIBRERIAS NO PARALELIZADAS
#include <glcm/imagenes.h>
#include <glcm/variance.h>
#include <glcm/squarevariance.h>
#include <glcm/entropia.h>
#include <glcm/averege.h>
#include <glcm/correlationcoeficient.h>
#include <glcm/mesure.h>
#include <glcm/contraste.h>
#include <glcm/moment.h>
#include <glcm/secondangular.h>
//LIBRERIAS PARALELIZADAS
#include <glcm_p/imagenes_p.h>
#include <glcm_p/variance_p.h>
#include <glcm_p/squarevariance_p.h>
#include <glcm_p/entropia_p.h>
#include <glcm_p/averege_p.h>
#include <glcm_p/correlationcoeficient_p.h>
#include <glcm_p/mesure_p.h>
#include <glcm_p/contraste_p.h>
#include <glcm_p/moment_p.h>
#include <glcm_p/secondangular_p.h>
#include <glcm/benchmark.h>
#include <svm/svm.h>

using namespace std;

void usarLibreria(vector<vector<int>> imageData,int rows,int cols){
    systemMetrics metrica("GLCM");
    metrica.resetCounters();
    imagenes img;
    variance variance;
    squarevariance sqvariance;
    entropia entropia;
    averege averege;
    correlationcoeficient coefi;
    mesure mesure;
    contraste contraste;
    moment moment;
    secondangular sang;
    double **pMatriz = img.ESCALAGRISES(imageData,rows,cols);
    int toneCount = img.ObtenertoneCount(imageData,rows,cols);
    double m_asm, m_contrast, m_corr, m_var, m_idm, m_savg, m_svar, m_sentropy, m_entropy, m_dvar, m_dentropy, m_icorr1, m_icorr2, m_maxcorr;
    //SECOND ANGULAR MOMENT
    m_asm = sang.f1_asm(pMatriz , toneCount);
    //CORRELACION
    m_corr = coefi.f3_corr(pMatriz, toneCount);
    //DIFERENCIA ENTROPIA
    m_dentropy = entropia.f11_dentropy(pMatriz, toneCount);
    // DIFERENCIA VARIANZA
    m_dvar = variance.f10_dvar(pMatriz, toneCount);
    //ENTROPIA
    m_entropy = entropia.f9_entropy(pMatriz, toneCount);
    //INVERSE DIFERENCE MOEMNT
    m_idm = moment.f5_idm(pMatriz, toneCount);
    //CONTRASTE
    m_contrast = contraste.f2_contrast(pMatriz , toneCount);
    //INFORMATION MESURE CORRELATION 1 Y 2
    m_icorr1 = mesure.f12_icorr(pMatriz, toneCount);
    m_icorr2 = mesure.f13_icorr(pMatriz, toneCount);
    //MAXIMO CORRELATION COEFICIENT
    m_maxcorr = coefi.f14_maxcorr(pMatriz, toneCount);
    //SUM AVEREGE
    m_savg = averege.f6_savg(pMatriz, toneCount);
    //SUMA ENTROPIA
    m_sentropy = entropia.f8_sentropy(pMatriz, toneCount);
    //SUM OF SQUARE VARIANCE
    m_var = sqvariance.f4_var(pMatriz, toneCount);
    //SUM VARIANCE
    m_svar = variance.f7_svar(pMatriz, toneCount, m_sentropy);
    img.generarExcel(m_asm,
                     m_contrast,
                     m_corr,
                     m_var,
                     m_idm,
                     m_savg,
                     m_svar,
                     m_sentropy,
                     m_entropy,
                     m_dvar,
                     m_dentropy,
                     m_icorr1,
                     m_icorr2,
                     m_maxcorr,
                     "/home/user/RESULTADOS/RESULTADOS0.csv");

    metrica.calculate();
    metrica.printMetrics();
    double a = metrica.getCpuPercent();//CPU
    double b = metrica.getDifMemoryKb();//MEMORIA
    double c = metrica.getDurationInMiliseconds();//TIEMPO EN MILISEGUNDOS
    double d = metrica.getDurationInSeconds();// TIEMPO EN SEGUNDOS
    cout << "Ram = " << getRamUsage() << " kb" << endl;
    img.generarExcelMetricas(a,b,c,d,getRamUsage(), "/home/user/RESULTADOS/metricas0.csv");

}

void usarLibreriaParalela(vector<vector<int>> imageData,int rows,int cols, int hilos){
    #pragma omp parallel num_threads(hilos)
    {
        systemMetrics metrica("GLCM");
        metrica.resetCounters();
        int hilo = omp_get_thread_num();
        imagenes_p img;
        imagenes img2;
        variance_p variance;
        squarevariance_p sqvariance;
        entropia_p entropia;
        averege_p  averege;
        correlationcoeficient_p coefi;
        mesure_p mesure;
        contraste_p contraste;
        moment_p moment;
        secondangular_p sang;
        double **pMatriz = img.ESCALAGRISES(imageData,rows,cols, hilos);
        int toneCount = img.ObtenertoneCount(imageData,rows,cols, hilos);
        double m_asm, m_contrast, m_corr, m_var, m_idm, m_savg, m_svar, m_sentropy, m_entropy, m_dvar, m_dentropy, m_icorr1, m_icorr2, m_maxcorr;
        //SECOND ANGULAR MOMENT
        m_asm = sang.f1_asm(pMatriz , toneCount, hilos);
        //CORRELACION
        m_corr = coefi.f3_corr(pMatriz, toneCount, hilos);
        //DIFERENCIA ENTROPIA
        m_dentropy = entropia.f11_dentropy(pMatriz, toneCount, hilos);
        // DIFERENCIA VARIANZA
        m_dvar = variance.f10_dvar(pMatriz, toneCount, hilos);
        //ENTROPIA
        m_entropy = entropia.f9_entropy(pMatriz, toneCount, hilos);
        //INVERSE DIFERENCE MOEMNT
        m_idm = moment.f5_idm(pMatriz, toneCount, hilos);
        //CONTRASTE
        m_contrast = contraste.f2_contrast(pMatriz , toneCount, hilos);
        //INFORMATION MESURE CORRELATION 1 Y 2
        m_icorr1 = mesure.f12_icorr(pMatriz, toneCount, hilos);
        m_icorr2 = mesure.f13_icorr(pMatriz, toneCount, hilos);
        //MAXIMO CORRELATION COEFICIENT
        m_maxcorr = coefi.f14_maxcorr(pMatriz, toneCount, hilos);
        //SUM AVEREGE
        m_savg = averege.f6_savg(pMatriz, toneCount, hilos);
        //SUMA ENTROPIA
        m_sentropy = entropia.f8_sentropy(pMatriz, toneCount, hilos);
        //SUM OF SQUARE VARIANCE
        m_var = sqvariance.f4_var(pMatriz, toneCount, hilos);
        //SUM VARIANCE
        m_svar = variance.f7_svar(pMatriz, toneCount, m_sentropy, hilos);
        img.generarExcel(m_asm,
                         m_contrast,
                         m_corr,
                         m_var,
                         m_idm,
                         m_savg,
                         m_svar,
                         m_sentropy,
                         m_entropy,
                         m_dvar,
                         m_dentropy,
                         m_icorr1,
                         m_icorr2,
                         m_maxcorr, hilos,
                         "/home/user/RESULTADOS/RESULTADOS1.csv");
        if(hilo == hilos-1){
            cout << "\nDATOS ALMACENADIOS hilos = " << hilo+1 << "\n";

            metrica.calculate();
            metrica.printMetrics();
            double a = metrica.getCpuPercent();//CPU
            double b = metrica.getDifMemoryKb();//MEMORIA
            double c = metrica.getDurationInMiliseconds();//TIEMPO EN MILISEGUNDOS
            double d = metrica.getDurationInSeconds();// TIEMPO EN SEGUNDOS
            cout << "Ram = " << getRamUsage() << " kb" << endl;
            img2.generarExcelMetricas(a,b,c,d,getRamUsage(), "/home/user/RESULTADOS/metrica1.csv");
        }
    }

}

int main()
{

    DicomReader dicomObj("/home/user/PARALELA/dataset/MasaMicro1.dcm");

    int rows = 20;//dicomObj.getHeight();
    int cols = 20;//dicomObj.getWidth();
    vector<vector<int>> imageData = dicomObj.getIntImageMatrix(12);
    //LIBRERIA NORMAL
    usarLibreria(imageData,rows,cols);
    //LIBRERIA PARALELIZADA - 2 hilos
    usarLibreriaParalela(imageData,rows,cols,2);
    //LIBRERIA PARALELIZADA - 4 hilos
    usarLibreriaParalela(imageData,rows,cols,4);
    //LIBRERIA PARALELIZADA - 8 hilos
    usarLibreriaParalela(imageData,rows,cols,8);
    //LIBRERIA PARALELIZADA - 16 hilos
    usarLibreriaParalela(imageData,rows,cols,16);
    //LIBRERIA PARALELIZADA - 32 hilos
    usarLibreriaParalela(imageData,rows,cols,32);

    return 0;
}


