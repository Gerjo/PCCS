#ifndef HEAVYSOLDIER_H
#define	HEAVYSOLDIER_H

#include <sharedlib/gameobjects/LightSoldier.h>
#include <sharedlib/services/Services.h>
#include <phantom.h>
using namespace phantom;

class HeavySoldier : public LightSoldier {
public:
    HeavySoldier();
    virtual ~HeavySoldier();
    virtual void paint();
    virtual void fromData(Data& data);
    virtual void toData(Data& data);
    virtual void onLayerChanged(Layer* layer);

    virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    virtual void onSelect(void);
    virtual void onDeselect(void);
    virtual MessageState handleMessage(AbstractMessage* message);

    bool isSelected(void);
    bool isMe(void);

    void setDirection(Vector3 position);

private:
    bool _isSelected;
    Vector3 _direction;
};

#endif	/* HEAVYSOLDIER_H */
