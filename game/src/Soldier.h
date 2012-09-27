#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>

using namespace phantom;

class Soldier : public Composite {
public:
    Soldier();
    Soldier(const Soldier& orig);
    virtual ~Soldier();
private:

};

#endif	/* SOLDIER_H */

