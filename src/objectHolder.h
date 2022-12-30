#ifndef OBJECT_HOLDER_H
#define OBJECT_HOLDER_H

#include <vector>
#include "genericObject.h"

/*
 * Holder can only store pheromons and its derivatives
 */
template<class T>
class ObjectHolder
{
    static_assert(std::is_base_of<GenericObject, T>::value, "T must inherit from GenericObject");

public:

    //all initialized objects are in here
    std::vector<T> inUseObjects;

    //is a temporal holding place where new objects are waiting to be initialized, after they were initialized call moveAllNewObjectsIntoHolder()
    //so that all new objects are sent to inUseObjects
    std::vector<T> newObjects;

    ObjectHolder() = default;


    //creates new objects which have to be manually initialized by user right after.
    void createNewObjects(unsigned int noOfObjects)
    {
        newObjects.resize(newObjects.size() + noOfObjects);
    }

    //don't forget to manually init objects before;
    //Note: this doesn't actually insert the objects into map
    void moveAllNewObjectsIntoHolder()
    {
        //inUseObjects.insert(inUseObjects.end(), newObjects.begin(), newObjects.end());
        unsigned int index = inUseObjects.size();
        for (auto &genericObject : newObjects)
        {
            genericObject.setIndexInHolder(index++);
            inUseObjects.push_back(genericObject);
        }
        newObjects.clear();
    }

    void insertGivenObjectIntoHolder(T &givenObject)
    {
        createNewObjects(1);

        unsigned int index = inUseObjects.size();
        givenObject.setIndexInHolder(index);
        newObjects.back() = givenObject;

        inUseObjects.push_back(newObjects.back());


        newObjects.pop_back();
    }


};


#endif