#include <random>
#include "AntActions.h"

namespace AntActions
{
float m_getRandomUniformly(float min, float max)
{
    static std::random_device rd;  // Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> distrib(min, max);

    return distrib(gen);
}

float m_dotProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y;
}
float m_norm(const sf::Vector2f &vector)
{
    return sqrtf(m_dotProduct(vector, vector));
}

/// \brief
/// \param r_vector Non-zero vector
/// \param newNorm
void m_changeNorm(sf::Vector2f &r_vector, float newNorm)
{
    assert(newNorm >= 0);
    r_vector = newNorm / m_norm(r_vector) * r_vector;
}

void m_chooseDirection(Ant &r_ant, World &r_world)
{
    CornerBounds bounds = r_world.map().computeBoundarySubRegion(r_ant.body().getPosition(), r_ant.viewRadius());

    sf::Vector2f oldVelocity = r_ant.velocity();

    //We are searching in the area an ant can see for food pheromones.
    //We add all the direction towards any seen pheromones and the resultant will be our wanted direction
    bool foundValidPhero = false;
    sf::Vector2f sumVector = {0, 0};
    for (int y = bounds.upperLeft.y; y <= bounds.lowerRight.y; ++y)
    {
        for (int x = bounds.upperLeft.x; x <= bounds.lowerRight.x ; ++x)
        {
            auto &chunkPhero = r_world.map().at(x, y).ref_pheromoneChunk.objects;

            for (size_t i = 0; i < chunkPhero.size(); ++i)
            {
                const Pheromone &phero = r_world.pheromones()[chunkPhero[i].index];
                if (phero.type() == Pheromone::Type_e::Food)
                {
                    const sf::Vector2f displacementVector = phero.body().getPosition() - r_ant.body().getPosition();
                    const float distanceToFood = m_norm(displacementVector);

                    //if we found such phero, we need to see if we can actually see it (the searched region is a square
                    //instead of a circle)
                    if (distanceToFood < r_ant.viewRadius())
                    {

                        // In order to not create death circles, we will want to get see only in front of our ant
                        sf::Vector2f normalized1 = displacementVector, normalized2 = oldVelocity;
                        m_changeNorm(normalized1, 1.0f);
                        m_changeNorm(normalized2, 1.0f);
                        if (m_dotProduct(normalized1, normalized2) > 0.0f)
                        {
                            //see for more details https://www.desmos.com/calculator/dxvsuhsabu

                            foundValidPhero = true;
                            //TODO: Take into account the potency of the pheromone too

                            //if the phero is close, we consider it more important in order not to lose details of the
                            //trail (and cutting across curves)
                            if (distanceToFood < r_ant.interactRadius())
                                sumVector += 5.0f * normalized1;
                            else
                                sumVector += 1.0f * normalized1;
                        }
                    }
                }
            }
        }
    }


    m_changeNorm(sumVector, r_ant.maxVelocity());
    sf::Vector2f newVelocity;
    if (foundValidPhero)
    {
        r_ant.followingFoodTrail() = true;

        sf::Vector2f wantedDirection = sumVector;

        const sf::Vector2f boundsOfChange = {0.25, 0.25};
        sf::Vector2f randomDirection = {m_getRandomUniformly(r_ant.velocity().x - boundsOfChange.x, r_ant.velocity().x + boundsOfChange.x),
                                        m_getRandomUniformly(r_ant.velocity().y - boundsOfChange.y, r_ant.velocity().y + boundsOfChange.y)};
        m_changeNorm(randomDirection, r_ant.maxVelocity());

        newVelocity = wantedDirection + 1.25f * randomDirection;

    }
    else
    {
        r_ant.followingFoodTrail() = false;
        sf::Vector2f wantedDirection = oldVelocity;
        const sf::Vector2f boundsOfChange = {0.25, 0.25};
        sf::Vector2f randomDirection = {m_getRandomUniformly(wantedDirection.x - boundsOfChange.x, wantedDirection.x + boundsOfChange.x),
                                        m_getRandomUniformly(wantedDirection.y - boundsOfChange.y, wantedDirection.y + boundsOfChange.y)};
        m_changeNorm(randomDirection, r_ant.maxVelocity());

        newVelocity = wantedDirection + 1.5f * randomDirection;
        // if the dot product is negative, it means that the new direction would go backwards. As such
        // we won't allow the ant to make turns greater than +- 90 degrees
        if (m_dotProduct(newVelocity, oldVelocity) < 0)
            newVelocity *= -1.0f;
    }


    m_changeNorm(newVelocity, r_ant.maxVelocity());
    r_ant.velocity() = newVelocity;
}



void m_findClosestFood(Ant &r_ant, World &r_world)
{
    CornerBounds bounds = r_world.map().computeBoundarySubRegion(r_ant.body().getPosition(), r_ant.viewRadius());

    // we iterate through all chunk zone that would be contained inside the interact radius
    // we go through a rectangular zone, if needed, this could be sped up by going through
    // a circular zone
    //TODO: Change the traversal order, start from center and go in a Breadth first traversal instead

    //We check the distance between all food particles in the interact region, and choose the closest one
    float closestFoodDistance = MAXFLOAT;
    sf::Vector2i closestFoodChunk = {-1, -1};
    size_t closestFoodIndexInWorld = -1;
    for (int y = bounds.upperLeft.y; y <= bounds.lowerRight.y; ++y)
    {
        for (int x = bounds.upperLeft.x; x <= bounds.lowerRight.x ; ++x)
        {
            auto &chunkFood = r_world.map().at(x,y).ref_foodChunk.objects;

            for (size_t i = 0; i < chunkFood.size(); ++i)
            {
                const Food &food = r_world.food()[chunkFood[i].index];
                const sf::Vector2f distanceVector = food.body().getPosition() - r_ant.body().getPosition();
                const float distanceToFood = m_norm(distanceVector);
                if (distanceToFood < r_ant.viewRadius())
                {
                    if (distanceToFood < closestFoodDistance and not food.isLocked())
                    {
                        closestFoodDistance = distanceToFood;
                        closestFoodChunk = {x, y};
                        closestFoodIndexInWorld = chunkFood[i].index;

                        r_ant.action() = Ant::Action_e::GrabbingFood;
                    }
                }
            }
        }
    }

    //if we did find a valid food particle, init r_ant.foundFoodPosition() with its position
    //this way we will go toward that location in the next Action, i.e Ant::Action_e::GrabbingFood
    //We also copy the food into the ant's "inventory" but we will keep this hidden until we actually
    //get to the food (by hidden, I mean that we will not render it to the screen)
    //when we do get to the food position, TODO: search for it again in the chunk and remove it???
    if (r_ant.action() == Ant::Action_e::GrabbingFood)
    {
        //lock into the found food
        Food &r_food = r_world.food()[closestFoodIndexInWorld];
        r_food.isLocked() = true;
        r_ant.hasFoundFood() = true;
        r_ant.foundFoodPosition() = r_food.body().getPosition();
    }



}
/// \brief SeachFood is the first action done for getting food. An ant is made to go in
/// random directions until it sees food. At that moment, we move on to the next action
/// step: GrabbingFood
/// \param r_ant
/// \param r_world
/// \param currentFrame
void searchFood(Ant &r_ant, World &r_world, unsigned currentFrame)
{
    assert(r_ant.action() == Ant::Action_e::SearchingFood);
    ///TODO: Make an ant seek food pheromone trails
    ///TODO: Maybe count how many different types of pheromones are in any chunk. This way an ant would be prefer to move
    /// towards a chunk with more food pheromones or less simple trail pheromones
    m_chooseDirection(r_ant, r_world);
    m_findClosestFood(r_ant, r_world);

    //we usually leave a pheromone once every 15 frames, but if we are in a food trail, path pheromones are
    //useless, so we leave less of them.
    //not that we won't leave food pheromone in case the food source disappears
    if (r_ant.followingFoodTrail())
    {
        if (currentFrame % 30 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);
    }
    else if (currentFrame % 5 == 0)
    {
        r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);
    }

    r_world.moveBy(r_ant.genericObject(), r_ant.velocity());
}

void m_getFoodParticle(Ant &r_ant, World &r_world)
{
    //due to the way we constructed the world, we unfortunately have to find the food
    //particle again.

    //we already know the position of the food, so we only search in a very small area;
    sf::Vector2i chunkIndexes = r_world.map().computeChunkIndex(r_ant.foundFoodPosition());

    auto &chunkFood = r_world.map().at(chunkIndexes).ref_foodChunk.objects;

    for (size_t i = 0; i < chunkFood.size(); ++i)
    {
        Food &r_food = r_world.food()[chunkFood[i].index];
        //if we found an r_food particle at the same position that was marked as locked, we can assume that
        //it's the right particle (2 particles might live at exactly the same spot)
        if (r_food.body().getPosition() == r_ant.foundFoodPosition() and r_food.isLocked())
        {
            //copy the r_food into the ant.
            //so we actually move the r_food on the ant, implying that the ant grabbed such r_food
            r_ant.grabbedFood() = r_food;

            //reset the status
            r_ant.hasFoundFood() = false;
            r_ant.hasGrabbedFood() = true;

            //unlock the food so that it can be removed
            r_food.isLocked() = false;
            chunkFood.toBeRemoved(r_food.knowledge().indexInHomeChunk());
            r_world.food().toBeRemoved(r_food.knowledge().indexInWorld());


            return;
        }
    }
}
/// \brief GrabFood happens right after SearchingFood action. The ant has seen the food and
/// and is going towards it
/// \param r_ant
/// \param r_world
/// \param currentFrame
void grabFood(Ant &r_ant, World &r_world, unsigned currentFrame)
{
    assert(r_ant.action() == Ant::Action_e::GrabbingFood);
    sf::Vector2f displacementVector = r_ant.foundFoodPosition() - r_ant.body().getPosition();
    //if we are close enough to interact with the food
    if (m_norm(displacementVector) <= r_ant.interactRadius())
    {
        m_getFoodParticle(r_ant, r_world);

        //we got the food, so go back
        r_ant.velocity() = -r_ant.velocity();
        r_ant.action() = Ant::Action_e::BringingFood;
    }
    else //we are too far to interact with it, so we just walk toward it
    {
        m_changeNorm(displacementVector, r_ant.maxVelocity());
        r_ant.velocity() = displacementVector;

        //if (currentFrame % 7 == 0)
        //    r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.FOOD_PHEROMONE);
        if (currentFrame % 5 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);

        r_world.moveBy(r_ant.genericObject(), r_ant.velocity());
    }

}
void bringFood(Ant &r_ant, World &r_world, unsigned currentFrame)
{
    assert(r_ant.action() == Ant::Action_e::BringingFood);

    sf::Vector2f distance = r_ant.home() - r_ant.body().getPosition();

    //if we are close to home, reset ant behavior
    if (m_norm(distance) <= r_ant.viewRadius())
    {
        r_ant.hasFoundFood() = false;
        r_ant.hasGrabbedFood() = false;
        r_ant.grabbedFood() = {};

        r_ant.followingFoodTrail() = false;
        r_ant.action() = Ant::Action_e::SearchingFood;
    }
    else //try to follow trail back
    {

        CornerBounds bounds = r_world.map().computeBoundarySubRegion(r_ant.body().getPosition(), r_ant.viewRadius());

        sf::Vector2f oldVelocity = r_ant.velocity();

        //We are searching in the area an ant can see for trails pheromones.
        //We add all the direction towards any seen pheromones and the resultant will be our wanted direction
        bool foundValidPhero = false;
        sf::Vector2f homeDirection = r_ant.home() - r_ant.body().getPosition();
        m_changeNorm(homeDirection, 1.0f);
        sf::Vector2f sumVector = homeDirection;
        for (int y = bounds.upperLeft.y; y <= bounds.lowerRight.y; ++y)
        {
            for (int x = bounds.upperLeft.x; x <= bounds.lowerRight.x ; ++x)
            {
                auto &chunkPhero = r_world.map().at(x, y).ref_pheromoneChunk.objects;

                for (size_t i = 0; i < chunkPhero.size(); ++i)
                {
                    const Pheromone &phero = r_world.pheromones()[chunkPhero[i].index];
                    if (phero.type() == Pheromone::Type_e::Trail)
                    {
                        const sf::Vector2f displacementVector = phero.body().getPosition() - r_ant.body().getPosition();
                        const float distanceToPhero = m_norm(displacementVector);

                        //if we found such phero, we need to see if we can actually see it (the searched region is a square
                        //instead of a circle)
                        if (4.0f * distanceToPhero < r_ant.viewRadius())
                        {

                            // In order to not create death circles, we will want to get see only in front of our ant
                            sf::Vector2f normalized1 = displacementVector, normalized2 = oldVelocity;
                            m_changeNorm(normalized1, 1.0f);
                            m_changeNorm(normalized2, 1.0f);
                            if (m_dotProduct(normalized1, normalized2) > 0.0f)
                            {
                                //see for more details https://www.desmos.com/calculator/dxvsuhsabu

                                foundValidPhero = true;
                                //TODO: Take into account the potency of the pheromone too

                                //if the phero is close, we consider it more important in order not to lose details of the
                                //trail (and cutting across curves)
                                if (distanceToPhero <= r_ant.interactRadius())
                                    sumVector += 7.0f * normalized1;
                                else
                                    sumVector += 1.0f * normalized1;
                            }
                        }
                    }
                }
            }
        }

        sf::Vector2f newVelocity;
        //if we did not wander away from the trail path
        if (foundValidPhero)
        {
            sf::Vector2f wantedDirection = sumVector;
            m_changeNorm(wantedDirection, r_ant.maxVelocity());


            newVelocity = wantedDirection;
            m_changeNorm(newVelocity, r_ant.maxVelocity());
        }
        else //if we lost the trail, go back
        {
            /*
            const sf::Vector2f boundsOfChange = {0.75, 0.75};
            sf::Vector2f randomDirection = {m_getRandomUniformly(r_ant.velocity().x - boundsOfChange.x, r_ant.velocity().x + boundsOfChange.x),
                                            m_getRandomUniformly(r_ant.velocity().y - boundsOfChange.y, r_ant.velocity().y + boundsOfChange.y)};
            m_changeNorm(randomDirection, r_ant.maxVelocity());
            //sum vector represents only the direction towards home, amplified by some constant
            newVelocity = r_ant.velocity() + 1.25f * randomDirection;
             */
            newVelocity = -sumVector;
        }



        r_ant.velocity() = newVelocity;
        r_world.moveBy(r_ant.genericObject(), r_ant.velocity());

        if (currentFrame % 7 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.FOOD_PHEROMONE);
        if (currentFrame % 45 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);

    }


}

} //end AntActions namespace