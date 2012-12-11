#ifndef ARTIFICIALINTELLIGENCE_H_
#define ARTIFICIALINTELLIGENCE_H_

#include <phantom.h>
#include "AIState.h"
#include "../gameobjects/GameObject.h"
#include "CompileConfig.h"

class LIBEXPORT ArtificialIntelligence : public phantom::Composite
{
public:
    GameObject::ResidenceState runat;

    static vector<GameObject*> soldiers;

    deque<AIState*> states;

    ArtificialIntelligence();
    virtual void update(const phantom::PhantomTime& time);
    virtual MessageState handleMessage(AbstractMessage* message);
    void insertState(AIState *state);

    void disableAll(void);

    template<class T> T* getState() {

        for(auto iterator = states.begin(); iterator != states.end(); ++iterator) {
            T* state = dynamic_cast<T*>(*iterator);
            if(state) {
                return state;
            }
        }

        return nullptr;
    }

    template<class T> T* setActive() {
        T* state = nullptr;

        for(auto iterator = states.begin(); iterator != states.end(); ++iterator) {
            state = dynamic_cast<T*>(*iterator);
            if(state != nullptr) {
                (*iterator)->construct();
                break;
            }
        }

        return state;
    }

    template<class T> T* setNonActive() {
        T* state = nullptr;

        for(auto iterator = states.begin(); iterator != states.end(); ++iterator) {
            state = dynamic_cast<T*>(*iterator);
            if(state != nullptr) {
                (*iterator)->destruct();
                break;
            }
        }

        return state;
    }

    GameObject* getOwner(void) {
        return static_cast<GameObject*>(_parent);
    }

    template<class T>
    T getOwner(void) {
        return static_cast<T>(_parent);
    }
};

#endif