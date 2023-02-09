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
	
	
	ConvexHull convexHull;
	cout<< "Casco convexo es:" << convexHull.find(pixels)<<endl;
	
	ImageAsymmetry imageAsymmetry;
	cout<< "La asimetria es:" << imageAsymmetry.find(pixels, width, height);<<endl;
	
	ImageCircularity imageCircularity;
	cout<< "La circularidad es:" << imageCircularity.find(pixels)<<endl;
	
	ImageCompactness imageCompactness;
	cout<< "El compactness es:" << imageCompactness.find(pixels)<<endl;

	ImageElongation imageElongation;
	cout<< "La alargacion es:" <<  imageElongation.find(pixels)<<endl;
	
	Shape calculateShape;
	cout<< "La forma es:" <<  double calculateShape(width, height)<<endl;

}