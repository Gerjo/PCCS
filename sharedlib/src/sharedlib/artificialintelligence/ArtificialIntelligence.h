#ifndef ARTIFICIALINTELLIGENCE_H_
#define ARTIFICIALINTELLIGENCE_H_

#include <phantom.h>
#include "AIState.h"
#include "../gameobjects/GameObject.h"
#include "CompileConfig.h"

class LIBEXPORT ArtificialIntelligence : public phantom::Composite
{
public:
    static vector<GameObject*> soldiers;
    
    deque<AIState*> states;

    ArtificialIntelligence();
    void update(const phantom::PhantomTime& time);
    MessageState handleMessage(AbstractMessage* message);
    void insertState(AIState *state);

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

};

#endif