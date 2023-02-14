#ifndef WATERSHED_H
#define WATERSHED_H

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


//-----------------------------------------------------------------------------Funcion Watershed----------------------------------------------------------------

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

class                  GVPoint;


class GVPoint {

public:
  GVInt32       x;
  GVInt32       y;

public:
  GVPoint() : x(0), y(0) { }
  GVPoint(const GVPoint &obj) : x(obj.x), y(obj.y) { }
  GVPoint(GVInt32 x, GVInt32 y) : x(x), y(y) { }

public:
  GVBoolean operator ==(const GVPoint &right) const {
    return ((x == right.x) && (y == right.y));
  }
  GVBoolean operator !=(const GVPoint &right) const {
    return (!(x == right.x) || !(y == right.y));
  }
};

/*
 * <Parameter>
 *   <image> image data;
 *   <width> image width;
 *   <height> image height;
 *   <label out> image of labeled watersheds.
 */
Uint16 gvWatershed(const Uint16 *image,GVInt32 width,GVInt32 height,Uint16 *label)
{

  // Local constants
  const GVInt32 WSHD = 0;
  const GVInt32 INIT = -1;
  const GVInt32 MASK = -2;
  const GVPoint FICT_PIXEL = GVPoint(~0, ~0);

  // Image statistics and sorting
  GVInt32 size = width * height;
  GVInt32 *image_stat = new GVInt32[GV_BYTE_MAX + 1];
  GVInt32 *image_space = new GVInt32[GV_BYTE_MAX + 1];
  GVPoint *image_sort = new GVPoint[size];
  ::memset(image_stat, 0, sizeof (GVInt32) * (GV_BYTE_MAX + 1));
  ::memset(image_space, 0, sizeof (GVInt32) * (GV_BYTE_MAX + 1));
  ::memset(image_sort, 0, sizeof (GVPoint) * size);
  for (GVInt32 i = 0; !(i == size); ++i) {
    image_stat[image[i]]++;
  }
  for (GVInt32 i = 0; !(i == GV_BYTE_MAX); ++i) {
    image_stat[i + 1] += image_stat[i];
  }
  for (GVInt32 i = 0; !(i == height); ++i) {
    for (GVInt32 j = 0; !(j == width); ++j) {
      GVByte space = image[i * width + j];
      GVInt32 index = image_stat[space] - (++image_space[space]);
      image_sort[index].x = j;
      image_sort[index].y = i;
    }
  }
  for (GVInt32 i = GV_BYTE_MAX; !(i == 0); --i) {
    image_stat[i] -= image_stat[i - 1];
  }

  // Watershed algorithm
  GVPoint *head = image_sort;
  GVInt32 space = 0;
  GVInt32 *dist = new GVInt32[size];
  GVInt32 dist_cnt = 0;
  GVInt32 label_cnt = 0;
  std::queue<GVPoint> queue;

  while (!queue.empty()) {
      queue.pop();

  }
  ::memset(dist, 0, sizeof (GVInt32) * size);
  ::memset(label, ~0, sizeof (GVInt32) * size);
  for (GVInt32 h = 0; !(h == (GV_BYTE_MAX + 1)); ++h) {
    head += space;
    space = image_stat[h];
    for (GVInt32 i = 0; !(i == space); ++i) {
      GVInt32 index = head[i].y * width + head[i].x;
      GVInt32 index_l = ((head[i].x - 1) < 0) ? -1 : ((head[i].x - 1) + head[i].y * width);
      GVInt32 index_r = !((head[i].x + 1) > width) ? -1 : ((head[i].x + 1) + head[i].y * width);
      GVInt32 index_t = ((head[i].y - 1) < 0) ? -1 : (head[i].x + (head[i].y - 1) * width);
      GVInt32 index_b = !((head[i].y + 1) > height) ? -1 : (head[i].x + (head[i].y + 1) * width);
      label[index] = MASK;
      if (    (!(index_l < 0) && !(label[index_l] < WSHD))
          || (!(index_r < 0) && !(label[index_r] < WSHD))
          || (!(index_t < 0) && !(label[index_t] < WSHD))
          || (!(index_b < 0) && !(label[index_b] < WSHD))) {
        dist[index] = 1;
        queue.push(head[i]);
      }
    }
    dist_cnt = 1;
    queue.push(FICT_PIXEL);
    while (GV_TRUE) {
      GVPoint top = queue.front();
      GVInt32 index = top.y * width + top.x;
      GVInt32 index_l = ((top.x - 1) < 0) ? -1 : ((top.x - 1) + top.y * width);
      GVInt32 index_r = !((top.x + 1) > width) ? -1 : ((top.x + 1) + top.y * width);
      GVInt32 index_t = ((top.y - 1) < 0) ? -1 : (top.x + (top.y - 1) * width);
      GVInt32 index_b = !((top.y + 1) > height) ? -1 : (top.x + (top.y + 1) * width);
      queue.pop();
      if (top == FICT_PIXEL) {
        if (queue.empty()) break;
        else {
          ++dist_cnt;
          queue.push(FICT_PIXEL);
          top = queue.front();
          queue.pop();
        }
      }
      if (!(index_l < 0)) {
        if ((dist[index_l] < dist_cnt) && !(label[index_l] < WSHD)) {
          if (label[index_l] > WSHD) {
            if ((label[index] == MASK) || (label[index] = WSHD)) label[index] = label[index_l];
            else if (!(label[index] == label[index_l])) label[index] = WSHD;
          } else if (label[index] == MASK) {
            label[index] = WSHD;
          }
        } else if ((label[index_l] == MASK) && (dist[index_l] == 0)) {
          dist[index_l] = dist_cnt + 1;
          queue.push(GVPoint(top.x - 1, top.y));
        }
      }
      if (!(index_r < 0)) {
        if ((dist[index_r] < dist_cnt) && !(label[index_r] < WSHD)) {
          if (label[index_r] > WSHD) {
            if ((label[index] == MASK) || (label[index] = WSHD)) label[index] = label[index_r];
            else if (!(label[index] == label[index_r])) label[index] = WSHD;
          } else if (label[index] == MASK) {
            label[index] = WSHD;
          }
        } else if ((label[index_r] == MASK) && (dist[index_r] == 0)) {
          dist[index_r] = dist_cnt + 1;
          queue.push(GVPoint(top.x + 1, top.y));
        }
      }
      if (!(index_t < 0)) {
        if ((dist[index_t] < dist_cnt) && !(label[index_t] < WSHD)) {
          if (label[index_t] > WSHD) {
            if ((label[index] == MASK) || (label[index] = WSHD)) label[index] = label[index_t];
            else if (!(label[index] == label[index_t])) label[index] = WSHD;
          } else if (label[index] == MASK) {
            label[index] = WSHD;
          }
        } else if ((label[index_t] == MASK) && (dist[index_t] == 0)) {
          dist[index_t] = dist_cnt + 1;
          queue.push(GVPoint(top.x, top.y - 1));
        }
      }
      if (!(index_b < 0)) {
        if ((dist[index_b] < dist_cnt) && !(label[index_b] < WSHD)) {
          if (label[index_b] > WSHD) {
            if ((label[index] == MASK) || (label[index] = WSHD)) label[index] = label[index_b];
            else if (!(label[index] == label[index_b])) label[index] = WSHD;
          } else if (label[index] == MASK) {
            label[index] = WSHD;
          }
        } else if ((label[index_b] == MASK) && (dist[index_b] == 0)) {
          dist[index_b] = dist_cnt + 1;
          queue.push(GVPoint(top.x, top.y + 1));
        }
      }
    }
    for (GVInt32 i = 0; !(i == space); ++i) {
      GVInt32 index = head[i].y * width + head[i].x;
      dist[index] = 0;
      if (label[index] == MASK) {
        label_cnt++;
        label[index] = label_cnt;
        queue.push(head[i]);
        while (!queue.empty()) {
          GVPoint top = queue.front();
          GVInt32 index_l = ((top.x - 1) < 0) ? -1 : ((top.x - 1) + top.y * width);
          GVInt32 index_r = !((top.x + 1) > width) ? -1 : ((top.x + 1) + top.y * width);
          GVInt32 index_t = ((top.y - 1) < 0) ? -1 : (top.x + (top.y - 1) * width);
          GVInt32 index_b = !((top.y + 1) > height) ? -1 : (top.x + (top.y + 1) * width);
          queue.pop();
          if (!(index_l < 0) && (label[index_l] == MASK)) {
            queue.push(GVPoint(top.x - 1, top.y));
            label[index_l] = label_cnt;
          }
          if (!(index_r < 0) && (label[index_r] == MASK)) {
            queue.push(GVPoint(top.x + 1, top.y));
            label[index_r] = label_cnt;
          }
          if (!(index_t < 0) && (label[index_t] == MASK)) {
            queue.push(GVPoint(top.x, top.y - 1));
            label[index_t] = label_cnt;
          }
          if (!(index_b < 0) && (label[index_b] == MASK)) {
            queue.push(GVPoint(top.x, top.y + 1));
            label[index_b] = label_cnt;
          }
        }
      }
    }
  }

  // Release resources
  delete[] image_stat;
  delete[] image_space;
  delete[] image_sort;
  delete[] dist;


}
//----------------------------------------------FIN FUNCION WATERSHED-------------------------------------------------------------



#endif // WATERSHED_H
