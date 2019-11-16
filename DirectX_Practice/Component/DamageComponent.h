#include "Component.h"

class Actor;

class DamageComponent : public Component {
public:
    DamageComponent(Actor* onwer, int damage);
    ~DamageComponent();
    virtual void update() override;
    int damage() const;
    void setDamage(int set);

private:
    int mDamage;
};