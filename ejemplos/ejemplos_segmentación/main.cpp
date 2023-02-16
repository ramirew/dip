#include <iostream>
#include "watershedP.h"
#include "dicom/DicomReader.h"
#include <iostream>
#include <vector>

using namespace std;

int main()

	DicomReader dicomObj("20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
	std::vector<Pixel> pixels = dicomObj.getIntImageMatrix(prof);
    int width = dicomObj.getHeight();
    int height = dicomObj.getWidth();
    
    cout << "La segmentacion de la imagen es:" << gvWatershed(pixels,width,height) << endl;
}
