#ifndef WATERSHEDP_H_INCLUDED
#define WATERSHEDP_H_INCLUDED

#include <iostream>
#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <ctime>
#include <cmath>
#include <cstdlib>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmimgle/didispfn.h"
#include "dcmtk/dcmimgle/dipixel.h"
#include "dcmtk/dcmdata/dcpxitem.h"
#include "dcmtk/dcmimage/diregist.h"
#include "dcmtk/dcmjpeg/djencode.h"
#include "dcmtk/dcmjpeg/djdecode.h"

Uint16 gvWatershed(const Uint16 *image,GVInt32 width,GVInt32 height,Uint16 *label);

#endif // WATERSHEDP_H_INCLUDED
