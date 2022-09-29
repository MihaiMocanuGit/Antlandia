#ifndef OBJECT_HOLDER_H
#define OBJECT_HOLDER_H

#include <array>

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


#endif