#include "libreriaGeometria.h"
#include<iostream>
#include<cmath>
using namespace std;

void gauss_jordan(double M[20][20],int n){
    double may;//variable para almacenar el mayor de la columna k
    int ind;//indice del mayor-->indice de may
    double aux;
    double pivote;
    
    for(int k=0;k<n;k++){//recorrer columnas de la matriz reducida
        may=abs(M[k][k]);
        ind=k;
        //recorrer filas de la columna k para buscar el indice del mayor
        for(int l=k+1;l<n;l++){
            if(may<abs(M[l][k])){
                may=abs(M[l][k]);
                ind=l;
            }
            
        }

        //cambiar filas
        if(k!=ind){
            for(int i=0;i<n+1;i++){
                aux=M[k][i];
                M[k][i]=M[ind][i];
                M[ind][i]=aux;
            }
            
        }
        if(M[k][k]==0){
            cout<<"no tiene solucion";
            break;
        }
        else{
            
            for(int i=0;i<n;i++){//recorrer fila
                if(i!=k){
                    pivote=-M[i][k];
                    for(int j=k;j<n+1;j++){//recorrer elementos de una fila

                        M[i][j]=M[i][j]+pivote*M[k][j]/M[k][k];
                    }
                }
                else{
                    pivote=M[k][k];
                    for(int j=k;j<n+1;j++){
                        M[i][j]=M[i][j]/pivote;
                    }
                }
            }
        }
        
    
}
} 
void ingresar_coeficientes(double M[20][20],int n){
    cout<<"ingrese ecuaciones:"<<endl;
    for(int i=0;i<n;i++){
        cout<<"\t"<<"fila "<<i+1<<" : "<<endl;
        for(int j=0;j<n+1;j++){
            cin>>M[i][j];
        }
    }
}