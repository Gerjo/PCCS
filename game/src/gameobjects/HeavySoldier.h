#ifndef HEAVYSOLDIER_H
#define	HEAVYSOLDIER_H

#include <sharedlib/gameobjects/LightSoldier.h>

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
    bool isSelected(void);
    bool isMe(void);
    void attack(GameObject* victim);
    void walk(Vector3 location);
    void update(const float& elapsed);

private:
    bool _isSelected;
    GameObject* _victim;
    vector<Vector3> _path; // For debugging only.

    void handleAi(void);
    bool seekRoute(Vector3 location);
};

#endif	/* HEAVYSOLDIER_H */
