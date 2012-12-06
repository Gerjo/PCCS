#ifndef SQUAD_H
#define	SQUAD_H

#include "../CompileConfig.h"
#include <phantom.h>
#include <iostream>
#include <sharedlib/gameobjects/GameObject.h>

using std::cout;
using std::endl;

using namespace phantom;

class LIBEXPORT Squad : public Composite {
public:

    Squad(GameObject* leader) : Composite(), _leader(leader) {
        // subscribe to leader destroy?
        leader->addComponent(this);
    }

    Squad(const Squad& original) {
        _leader  = original._leader; // Pointer copy is OK here. -- Gerjo
        _members = original._members;
    }

    void march(Vector3 where) {
        // TODO:
        // call methods of each type.
        //
        // To consider: some stack?
        //
        //_leader.push(new Walkto(location, squad));

        cout << "Simon says: " << _members.size() << " to " << where.toString() << endl;
    }

    void removeMember(GameObject* member) {
        if(member == _leader) {
            cout << "Squad::removeMember(): Fudge just hit the fan. *insert code*" << endl;
        }

        // TODO: std::remove?
        for(auto it = _members.begin(); it != _members.end(); ++it) {
            if(*it == member) {
                _members.erase(it);
                break;
            }
        }

        // Automatically dispose if there are no more squad members:
        if(_members.empty()) {
            cout << "Deleting squad component, no more members." << endl;
            destroy();
        }
    }

    void addMember(GameObject* member) {
        // There may be no squad to begin with:
        if(member->squad != nullptr) {
            // Can only subscribe once:
            if(member->squad == this) {
                return;
            }

            // This will automatically delete the old squad if
            // there are no more members left therein.
            member->squad->removeMember(member);
        }

        _members.push_back(member);
        member->squad = this;
    }

    GameObject* getLeader() {
        return _leader;
    }

    bool isLeader(GameObject* who) const {
        return _leader == who;
    }

private:
    GameObject* _leader;
    vector<GameObject*> _members;
};

#endif	/* SQUAD_H */

