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
    virtual void attack(GameObject* victim);

    bool isSelected(void);
    bool isMe(void);

    void update(const PhantomTime& time);
    void setDirection(Vector3 position);

    virtual void walk(Vector3 location);
    virtual void onBulletFired(LightBullet* bullet);

private:
    bool _isSelected;
    Vector3 _direction;

    virtual void handleAi(void);
};

#endif	/* HEAVYSOLDIER_H */
