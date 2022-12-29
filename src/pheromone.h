//
// Created by mihai on 11/19/22.
//

#ifndef PHEROMONE_H
#define PHEROMONE_H

#include "genericObject.h"

class Pheromone : public GenericObject
{
private:
    void m_updateTime(float timePassed);
    void m_updatePower(float modifyWith);

    static constexpr float epsilon_zero_power = 0.001;
public:
    static constexpr int FOOD_TYPE = 0;
    static constexpr int REPELLENT_TYPE = 1;
    static constexpr int PATH_TYPE = 2;
    static constexpr int HOME_TYPE = 3;
    static constexpr float DEFAULT_POWER_REDUCING_FACTOR = 1.25;
    /*
     * a sort of power half life, pretty much every frame we divide power by a certain value, this value being
     * power_reducing_factor which must be > 1 or = 1 if you want it to last forever
     * so, newPower = (oldPower / powerReducingFactor)
     * Greater values make the pheromone last less
     */
    float powerReducingFactor;

    float power;

    int type;

    Pheromone();
    Pheromone(sf::CircleShape &aShape, int aType, float aPower, float aPowerReducingFactor);




    /*
     * Should be called each frame, to update Pheromone power Level
     * After an update, power will decrease (it is divided each time by powerReducingFactor)
    */
    void update();

    /*
     * This needs to be called after each update to see if the object should be deleted
     * TODO: think how to delete the object, it probably should be done external
     */
    bool isThisPheromoneDepleted();
};


#endif //PHEROMONE_H
