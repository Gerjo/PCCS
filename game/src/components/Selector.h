#ifndef SELECTOR_H_GT
#define	SELECTOR_H_GT

#include <phantom.h>
#include <deque>
#include <algorithm>
#include "../gameobjects/HeavySoldier.h"

using namespace phantom;

using std::string;
using std::cout;
using std::endl;
using std::deque;

class BSPTree;

class Selector : public Composite {
public:
    Selector();
    virtual ~Selector();
    virtual void update(const float& elapsed);
    virtual MessageState handleMessage(AbstractMessage* message);

    void setTrackingLayer(BSPTree* layer);
    void setCamera(Camera* camera);


private:
    deque<HeavySoldier*> _soldiers;

    Box3 _selectionBox;
    bool _hasSelectionStart;
    bool _hasFinalizedSelection;
    bool _doRedraw;

    BSPTree* _trackingLayer;
    Camera* _camera;

    void start(void);
    void finalize();
    void update(void);
    void deSelect(void);
    void drawSelection(void);
    void click(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
    void handleHover(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
    void handleSelection(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
};

#endif	/* SELECTOR_H_GT */
