#ifndef IMAGEDIRECTIONS_H_
#define IMAGEDIRECTIONS_H_

#include <sstream>

class ImageDirections {
public:
    static void to8Directions(std::stringstream &str, float rotation) {
        if(rotation > -22.5f && rotation < 22.5f)
            str << "1";
        else if(rotation > 22.5f && rotation < 67.5f)
            str << "2";
        else if(rotation > 67.5f && rotation < 112.5f)
            str << "3";
        else if(rotation > 112.5f && rotation < 157.5f)
            str << "4";
        else if(rotation > 157.5f && rotation < -157.5f)
            str << "5";
        else if(rotation > -157.5f && rotation < -112.5f)
            str << "6";
        else if(rotation > -112.5f && rotation < -67.5f)
            str << "7";
        else if(rotation > -67.5f && rotation < -22.5f)
            str << "8";
        else
            str << "1";
    }
};

#endif