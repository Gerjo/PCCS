#include "VLineSegment.h"

namespace vor{
    namespace geom{
        VLineSegment::VLineSegment(Vector3 start, Vector3 end){
            this->start = start;
            this->end = end;
        }
        int VLineSegment::compareLengths(VLineSegment* seg0, VLineSegment* seg1, bool max){
                float length0 = seg0->start.distanceTo(seg0->end);
                float length1 = seg1->start.distanceTo(seg1->end);
                int retval =0;
                if(length0 < length1){
                    retval = (max)? 1 : -1;
                }else if (length0 > length1){
                    retval = (max)? -1 : 1;

                }
                return retval;
            }
    }
}