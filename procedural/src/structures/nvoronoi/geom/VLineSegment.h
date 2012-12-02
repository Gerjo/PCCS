#ifndef VLINESEGMENT_H
#define VLINESEGMENT_H

#include <phantom.h>
#include <CompileConfig.h>

namespace vor{
    namespace geom{
        class LIBEXPORT VLineSegment{
        public:
            Vector3 start, end;
            VLineSegment(Vector3 start, Vector3 end);

            static int compareLengths(VLineSegment* seg0, VLineSegment* seg1, bool max);
        };
    }
}


#endif /* VLINESEGMENT_H */