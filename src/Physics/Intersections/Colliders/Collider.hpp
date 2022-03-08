#ifndef COLLIDER_CLASS_H
#define COLLIDER_CLASS_H

enum class ColliderType {
    AABB=0,
    OBB=1,
    PLANE=2,
    SPHERE=3,
    TRIANGLE=4,
    MESH=5,
    NONE=-1
};

class Collider {
public:
    ColliderType type = ColliderType::NONE;
    virtual ColliderType getType() {
        return type;
    }
};

#endif