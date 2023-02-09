#include "libreria.h"
#include "dicom/DicomReader.h"
void main(){
    DicomReader dicomObj("20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
    int width = dicomObj.getHeight();
    int height = dicomObj.getWidth();

    vector<vector<double>> imageData = dicomObj.getDoubleImageMatrix(12);
    vec_t flatImg = flatImage(imageData);
    int n = sizeof(vect_t)/sizeof(vect_t[0]);
    printf("Resultado: %d\n",geometry(points, n));
    return 0;
}
