#include <random>
#include "AntActions.h"

namespace AntActions
{
float m_getRandomUniformly(float min, float max)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(min, max);

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
/// \param clampNorm
void m_clampVectorByNorm(sf::Vector2f &r_vector, float clampNorm)
{
    r_vector = clampNorm / m_norm(r_vector) * r_vector;
}

void m_chooseDirection(Ant &r_ant, World &r_world)
{
    CornerBounds bounds = r_world.map().computeBoundarySubRegion(r_ant.body().getPosition(), r_ant.viewRadius());

    sf::Vector2f oldVelocity = r_ant.velocity();

    //We are searching in the area an ant can see for food pheromones
    float closestFoodPheroDistance = MAXFLOAT;
    bool foundValidPhero = false;
    sf::Vector2f velocityTowardsPhero = {-1.0f, -1.0f};
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
                    const sf::Vector2f distanceVector = phero.body().getPosition() - r_ant.body().getPosition();
                    const float distanceToFood = m_norm(distanceVector);

                    //if we found such phero, we need to see if we can actually see it (the searched region is a square
                    //instead of a circle)
                    if (distanceToFood < r_ant.viewRadius() and distanceToFood < closestFoodPheroDistance)
                    {
                        //We now will only remember the closest pheromone that is in front of our ant.
                        //the food pheromone is in front of the ant if the dot product is positive
                        //(we consider that it has a FOV of 180)
                        if (m_dotProduct(distanceVector, oldVelocity) > 0)
                        {
                            closestFoodPheroDistance = distanceToFood;

                            foundValidPhero = true;
                            velocityTowardsPhero = distanceVector;
                        }
                    }
                }
            }
        }
    }

    sf::Vector2f newVelocity;
    if (foundValidPhero)
    {
        r_ant.followingFoodTrail() = true;
        const sf::Vector2f boundsOfChange = {0.05f, 0.05f};
        newVelocity = {m_getRandomUniformly(velocityTowardsPhero.x - boundsOfChange.x, oldVelocity.x + boundsOfChange.x),
                       m_getRandomUniformly(velocityTowardsPhero.y - boundsOfChange.y, velocityTowardsPhero.y + boundsOfChange.y)};
    }
    else
    {
        const sf::Vector2f boundsOfChange = {0.15f, 0.15f};
        newVelocity = {m_getRandomUniformly(oldVelocity.x - boundsOfChange.x, oldVelocity.x + boundsOfChange.x),
                       m_getRandomUniformly(oldVelocity.y - boundsOfChange.y, oldVelocity.y + boundsOfChange.y)};

        // if the dot product is negative, it means that the new direction would go backwards. As such
        // we won't allow the ant to make turns greater than +- 90 degrees
        if (m_dotProduct(newVelocity, oldVelocity) < 0)
            newVelocity *= -1.0f;
    }

    if (m_norm(newVelocity) > r_ant.maxVelocity())
        m_clampVectorByNorm(newVelocity, r_ant.maxVelocity());


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
    if (r_ant.followingFoodTrail() and currentFrame % 180 == 0)
        r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);
    else if (currentFrame % 15 == 0)
        r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);

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

            //we got the food, so go back
            r_ant.velocity() = -r_ant.velocity();
            r_ant.action() = Ant::Action_e::BringingFood;
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
    }
    else //we are too far to interact with it, so we just walk toward it
    {
        m_clampVectorByNorm(displacementVector, r_ant.maxVelocity());
        r_ant.velocity() = displacementVector;

        if (currentFrame % 10 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.FOOD_PHEROMONE);
        if (currentFrame % 15 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.TRAIL_PHEROMONE);

        r_world.moveBy(r_ant.genericObject(), r_ant.velocity());
    }

}
void bringFood(Ant &r_ant, World &r_world, unsigned currentFrame)
{
    assert(r_ant.action() == Ant::Action_e::BringingFood);

    sf::Vector2f distance = r_ant.home() - r_ant.body().getPosition();

    //if we are close to home, reset ant behavior
    if (m_norm(distance) <= r_ant.interactRadius())
    {
        r_ant.hasFoundFood() = false;
        r_ant.hasGrabbedFood() = false;
        r_ant.grabbedFood() = {};

        r_ant.followingFoodTrail() = false;
        r_ant.action() = Ant::Action_e::SearchingFood;
    }
    else
    {
        sf::Vector2f wantedDirection = distance;
        m_clampVectorByNorm(wantedDirection, r_ant.maxVelocity());

        const sf::Vector2f boundsOfChange = {1, 1};
        sf::Vector2f randomDirection = {m_getRandomUniformly(r_ant.velocity().x - boundsOfChange.x, r_ant.velocity().x + boundsOfChange.x),
                                        m_getRandomUniformly(r_ant.velocity().y - boundsOfChange.y, r_ant.velocity().y + boundsOfChange.y)};
        m_clampVectorByNorm(randomDirection, r_ant.maxVelocity());

        sf::Vector2f newVelocity = wantedDirection + 1.5f * randomDirection;


        m_clampVectorByNorm(newVelocity, r_ant.maxVelocity());


        r_ant.velocity() = newVelocity;
        r_world.moveBy(r_ant.genericObject(), r_ant.velocity());

        if (currentFrame % 10 == 0)
            r_world.makeAntSpawnPheromone(r_ant, r_world.pheromoneTypes.FOOD_PHEROMONE);
    }


}

} //end AntActions namespace