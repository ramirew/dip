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

typedef void              GVVoid;
typedef bool              GVBoolean;
typedef char              GVChar;
typedef Uint16          GVByte;
typedef short              GVInt16;
typedef unsigned short         GVUInt16;
typedef int               GVInt32;
typedef unsigned int          GVUInt32;
typedef long long            GVInt64;
typedef unsigned long long       GVUInt64;
typedef float              GVFloat32;
typedef double             GVFloat64;

const GVBoolean GV_TRUE         = true;
const GVBoolean GV_FALSE        = false;
const GVByte              GV_BYTE_MAX = SHRT_MAX;
const GVInt32              GV_INT32_MAX = INT_MAX;
const GVInt32              GV_INT32_MIX = INT_MIN;
const GVInt64              GV_INT64_MAX = LLONG_MAX;
const GVInt64              GV_INT64_MIN = LLONG_MIN;
const GVFloat32 GV_FLOAT32_MAX     = FLT_MAX;
const GVFloat32 GV_FLOAT32_MIN     = FLT_MIN;
const GVFloat64 GV_FLOAT64_MAX     = DBL_MAX;
const GVFloat64 GV_FLOAT64_MIN     = DBL_MIN;


Uint16 gvWatershed(const Uint16 *image,GVInt32 width,GVInt32 height,Uint16 *label);

#endif // WATERSHEDP_H_INCLUDED
