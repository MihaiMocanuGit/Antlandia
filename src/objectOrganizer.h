#ifndef OBJECT_ORGANIZER_H
#define OBJECT_ORGANIZER_H

#include <array>

#include "chunk.h"
#include "genericObject.h"


template<class T, std::size_t MAX_NO_OBJECTS_IN_GROUP>
class ObjectHolder
{
private:
        //all initialized objects are in here
        std::array<T, MAX_NO_OBJECTS_IN_GROUP> m_initObjects;

        //is a temporal holding place where new objects are waiting to be initialized, after init they are sent to m_initObjects
        std::array<T, MAX_NO_OBJECTS_IN_GROUP> m_newObjects;

public:
        ObjectHolder();
        
        //creates new objects which have to be manually initialized by user right after.
        void createNewObjects(unsigned int noOfObjects);

        //don't forget to manually init objects before;
        void placeNewObjectsIntoChunk();

        //getter, primarly used to init newly created objects
        std::array<T, MAX_NO_OBJECTS_IN_GROUP> &getNewObjects();

        //getter, only gets already init objects which are in chunks
        std::array<T, MAX_NO_OBJECTS_IN_GROUP> &getObjects();
};

///create chunkMap, it controls the structure logic further calls
template<std::size_t MAP_SIZE_X, std::size_t MAP_SIZE_Y, std::size_t MAX_NO_OBJECTS_IN_GROUP>
class ObjectOrganizer
{
private:

        std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> m_chunkMap;

        //create chunk map and inits all chunks
        void m_initChunkMap();


public:

        ObjectOrganizer()

        ObjectHolder<Ant, MAX_NO_OBJECTS_IN_GROUP> ants;
        ObjectHolder<GenericObject, MAX_NO_OBJECTS_IN_GROUP> GenericObject;

        const std::array<std::array<Chunk, MAP_SIZE_X>, MAP_SIZE_Y> & getChunkMap() const;
};






#endif