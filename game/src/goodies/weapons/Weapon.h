#ifndef GUN_H
#define	GUN_H

#include <phantom.h>
#include <cmath>

using namespace std;
using namespace phantom;

class Weapon : public Composite {
public:
    Weapon(void);
    string getName(void);
    float getRange(void);
    float getRangeSq(void);

protected:
    float _range;
    string _name;
};

#endif	/* GUN_H */

