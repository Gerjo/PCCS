#ifndef VCIRCLE_h
#define VCIRCLE_h

#include <phantom.h>
#include <CompileConfig.h> 

using phantom::Vector3;

namespace vor{
    namespace geom{
        class LIBEXPORT VCircle{
        public:
            VCircle(Vector3 position, float radius);
            Vector3 position;
            float radius;
        };
    }
}


#endif /* VCIRCLE_h */
