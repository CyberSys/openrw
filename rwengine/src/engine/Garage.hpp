#ifndef _RWENGINE_Garage_HPP_
#define _RWENGINE_Garage_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <rw/defines.hpp>

class PlayerController;

class GameWorld;

class CharacterObject;
class InstanceObject;
class GameObject;

class Garage {
private:
    InstanceObject* doorObject = nullptr;
    InstanceObject* secondDoorObject = nullptr;

    bool active = true;

    float garageTimer = 0.f;

    bool swingType = false;

    glm::vec3 startPosition;
    glm::vec3 startPositionSecondDoor;

    bool needsToUpdate = false;

    float fraction = 0.f;
    float step = 3.f;  // this should be adjusted somehow
                       // to look similar to original game
    float doorHeight = 4.f;

    float getDistanceToGarage(glm::vec3 point);

    bool shouldOpen();
    bool shouldClose();
    bool shouldStopOpening();
    bool shouldStopClosing();

    void doOnOpenEvent();
    void doOnCloseEvent();
    void doOnStartOpeningEvent();
    void doOnStartClosingEvent();

    void updateDoor();

public:
    // Garage types are from original game
    enum class Type {
        Mission = 1,
        BombShop1 = 2,
        BombShop2 = 3,
        BombShop3 = 4,
        Respray = 5,
        CollectCars1 = 8,
        CollectCars2 = 9,
        MissionForCarToComeOut = 11,
        Crusher = 13,
        MissionKeepCar = 14,
        Hideout1 = 16,
        Hideout2 = 17,
        Hideout3 = 18,
        MissionToOpenAndClose = 19,
        MissionForSpecificCar = 20,
        MissionKeepCarAndRemainClosed = 21,
    };

    enum class State { Closed, Closing, Opening, Opened };

    GameWorld* engine;
    int id;

    int getScriptObjectID() const {
        return id;
    }

    glm::vec3 min;
    glm::vec3 max;

    Type type;

    GameObject* target = nullptr;
    // @todo use model type
    int targetModel = 0;

    State state = State::Closed;

    bool resprayDone = false;

    Garage(GameWorld* engine_, const int id_, const glm::vec3 coord0,
               const glm::vec3 coord1, const Type type_);
    ~Garage() = default;

    void makeDoorSwing();

    bool isObjectInsideGarage(GameObject* object) const;
    bool isTargetInsideGarage() const;

    void activate();
    void deactivate();

    void open();
    void close();

    void tick(float dt);
};

#endif