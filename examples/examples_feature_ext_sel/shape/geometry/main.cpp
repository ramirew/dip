#include "libreriaGeometria.h"
#include "dicom/DicomReader.h"
#include <iostream>
#include <vector>

int main() {
	DicomReader dicomObj("20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
	cout<<"Ingrese profundidad de la imagen: "<<prof<<endl;
	std::vector<Pixel> pixels = dicomObj.getIntImageMatrix(prof);
    int width = dicomObj.getHeight();
    int height = dicomObj.getWidth();
	
    ImageAsymmetry imageAsymmetry;
	imageAsymmetry.find(pixels, width, height);
	
	ConvexHull convexHull;
	convexHull.find(pixels);
	
	ImageCircularity imageCircularity;
	imageCircularity.find(pixels);


}