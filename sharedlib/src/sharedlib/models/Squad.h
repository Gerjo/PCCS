#ifndef SQUAD_H
#define	SQUAD_H

#include "../CompileConfig.h"
#include <phantom.h>
#include <vector>
#include <iostream>
#include "../gameobjects/GameObject.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/squad/SquadMove.h"
#include "../artificialintelligence/squad/SquadFlocking.h"
#include "../artificialintelligence/squad/SquadAttack.h"

using std::cout;
using std::endl;
using std::vector;

using namespace phantom;

class LIBEXPORT Squad : public Composite {
public:

    static vector<Squad*> createSquads(vector<GameObject*> gameobjects, const Vector3& target, const float& distanceToLeader);

    Squad(GameObject* leader) : Composite(), _leader(leader) {

        //cout << "Squad constructor." << endl;

        // Remove the leader from his old squad, if applicable.
        if(leader->squad) {
            //cout << "   removing new leader from his old squad." << endl;
            leader->squad->removeMember(leader);
        }

        leader->addComponent(this);
        leader->squad = this;
    }

    Squad(const Squad& original) {
        _leader  = original._leader; // Pointer copy is OK here. -- Gerjo
        _members = original._members;
    }

    void attack(GameObject* victim) {
        // Squad march to the victim:
        march(victim->getBoundingBox().getCenter());

        _leader->ai->setActive<SquadAttack>()->setVictim(victim);

        for(GameObject* gameobject : _members) {
            gameobject->ai->setActive<SquadAttack>()->setVictim(victim);
        }
    }

    void march(Vector3 where) {
        _leader->ai->disableAll();
        _leader->ai->setActive<SquadMove>()->setTarget(where);

        for(GameObject* gameobject : _members) {
            gameobject->ai->disableAll();
            gameobject->ai->setActive<SquadFlocking>()->setLeader(_leader);
        }

        //cout << "Simon says: " << _members.size() << " soldier(s) march to " << where.toString() << endl;
    }

    void removeLeader() {
        //cout << "Removing leader from squad." << endl;

        Vector3 target = _leader->getComponentByType<Mover>(0)->getTarget();
        this->removeFromParent();
        _leader        = nullptr;

        // There are still members, so one of them will become the new leader.
        if(!_members.empty()) {
            _leader = _members.back();
            _leader->addComponent(this);
            _members.pop_back();

            // Re-issue the orders:
            march(target);

        } else {
            //cout << "Deleting squad component, no more members." << endl;
            destroy();
        }
    }

    void removeMember(GameObject* member) {
        //cout << "Removing member from squad." << endl;

        if(member == _leader) {
            //cout << "Squad::removeMember(): Squad changed leadership." << endl;
            removeLeader();
        }

        _members.erase(
            std::remove(_members.begin(), _members.end(), member),
            _members.end()
        );
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

    unsigned size() const {
        return static_cast<unsigned>(_members.size()) + 1;
    }

private:
    GameObject* _leader;
    vector<GameObject*> _members;
};

#endif	/* SQUAD_H */

