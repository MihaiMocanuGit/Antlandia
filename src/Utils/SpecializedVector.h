#pragma once
#include <vector>
#include <stdexcept>

/// \brief The type of the swap function used by SpecializedVector
template <class T>
using SwapFct_t = void (*)(T&, ptrdiff_t , T&, ptrdiff_t);

/// \brief The type of the initAdd function used by SpecializedVector
template <class T>
using InitToBeAddedFct_t = void (*)(T&, ptrdiff_t);

/// \brief The type of the initRemove function used by SpecializedVector
template <class T>
using InitToBeRemovedFct_t = void (*)(T&, ptrdiff_t);

/// \brief /// \brief The type of the initFinal function used by SpecializedVector
template <class T>
using InitForFinaliseFct_t = void (*)(T&, ptrdiff_t);

/// \brief The type of the destruct function used by SpecializedVector
template <class T>
using DestructFct_t = void (*)(T&, ptrdiff_t);

/// \brief Data structure representing a specialization of dynamic vector that is optimized for random insertions and
/// removals of arbitrary elements that do not need to take effect immediately. The order of stored elements is not
/// important.
/// \n\n
/// Furthermore, this data structure has the ability to update the information know by the stored elements about themselves,
/// such as their position in this container.
/// \note As this container is built upon std::vector its behavior will be similar, such as suffering from reference,
/// iterator and pointer invalidation. This is why I recommend the usage of simple indexes that will be updated
/// through the given custom functions.
/// \tparam T copy-constructable and copy-assignable element
template <typename T>
class SpecializedVector
{
private:
    std::vector<T> m_data = {};

    /// \brief additional vector where we temporally store the elements that will later be added
    std::vector<T> m_addBuffer = {};

    size_t m_startOfRemoveBuffer = 0;

    InitToBeAddedFct_t<T> m_initAdd;
    InitToBeRemovedFct_t<T> m_initRemove;

    InitForFinaliseFct_t<T> m_initFinal;
    SwapFct_t<T> m_swap;
    DestructFct_t<T> m_destruct;


public:
    /// \brief The default number of elements that the container can hold at the start without resorting to
    // a vector reallocation to increase the capacity
    static constexpr size_t DEFAULT_RESERVE = 128;

    /// \brief Function used to replace initAdd, initRemove, initFinal or destruct if you do not need their
    /// usage
    static void emptyUnaryFunction(T &, size_t) {}

    /// \brief Creates a new container.
    /// \param reserve  Optional parameter representing how many element can the container hold at the start
    /// without resorting to a vector reallocation to increase the capacity.
    explicit SpecializedVector(size_t reserve = DEFAULT_RESERVE);

    /// \brief Initializes the Container with the given custom functions.
    /// \details The main role of these functions is to be used in "self-aware objects". They are objects
    /// that are aware of their own state in the next layers of the app.
    /// \n\n
    /// For example, we have a game that stores its entities in a vector. These entities need to know their
    /// position in the vector and to do that they must remember their own index. The main problem is that
    /// you want to keep these indexes updated after every operation on the parent vector.
    /// \n\n
    /// As such, you must resort to these custom functions to help you with that.
    /// \param initAdd It is used for initialising the state of your stored information when you mark an
    /// object for insertion.
    /// \param initRemove It is used for initialising the state of your stored information when you mark an
    /// object for removal.
    /// \param initFinal It is used for initialising the state of your information when an object is inserted
    /// into the section of current elements. That is, it is called when an object that was marked for insertion
    /// is finally added into the container.
    /// \param swap It is used to update the state of 2 elements that are internally swapped inside the container.
    /// You are also responsible for the swap logic of these elements.
    /// \param destruct It is used to update the state when an object is completely removed from the container.
    /// \param reserve Optional parameter representing how many element can the container hold at the start without
    /// resorting to a vector reallocation to increase the capacity.
    /// \note If you do not need to use some of these functions for your particular scenario, you can use std::swap
    /// to replace the swap logic, or SpecializedVector::emptyUnaryFunction for any of the inits or destruct.
    SpecializedVector(InitToBeAddedFct_t<T> initAdd, InitToBeRemovedFct_t<T> initRemove,
                      InitForFinaliseFct_t<T> initFinal, SwapFct_t<T> swap, DestructFct_t<T> destruct,
                      size_t reserve = DEFAULT_RESERVE);

    /// \brief The given element will later be added into the container
    /// \param element The element that will later be added. It is temporally stored in an add buffer until then.
    /// \return Returns a negative valued index that starts at -1 and points to the element in the temporal
    /// add buffer
    /// \note The given element is copied into the container, changes of the element after the insertion will
    /// not be reflected in the copied element inside the container
    ptrdiff_t toBeAdded(T &&element);

    /// \brief The given element will later be added into the container
    /// \param element The element that will later be added. It is temporally stored in an add buffer until then.
    /// \return Returns a negative valued index that starts at -1 and points to the element in the temporal
    /// add buffer
    /// \note The given element is copied into the container, changes of the element after the insertion will
    /// not be reflected in the copied element inside the container
    ptrdiff_t toBeAdded(const T &element);

    /// \brief Complete the changes that were made. Meaning that all elements that were marked for
    /// removal will be remove. The elements marked for insertion will also be inserted.
    /// \note References to the elements that were marked for removal/insertion will be invalidated.
    /// \note References to the rest of the elements might be invalidated if the underlying std::vector
    /// will be reallocated.
    void finishChanges();
    //TODO: Maybe add separate option to just remove or just add


    /// \brief Mark the given element for removal
    /// \param index The index of a current element. Cannot remove elements that are marked
    /// for insertion
    /// \note Reference to this element will be invalidated after a call to finalizeChanges()
    /// \note Previous references to this element and the last element not marked for removal will be
    /// invalidated after a call to this function
    /// \return Reference to the given element
    T& toBeRemoved(std::size_t index);

    //TODO: Add new function to remove elements from the addBuffer too; I think it should just
    // instantly delete them, no need for a finalize.

    /// \brief Gets an element only from the section of current elements.
    /// \param index
    /// \return Reference to the element at the given index
    /// \note Bounds are not checked.
    T& operator[](size_t index);

    /// \brief Gets an element only from the section of current elements.
    /// \param index
    /// \return Const reference to the element at the given index
    /// \note Bounds are not checked.
    const T& operator[](size_t index) const;

    /// \brief Gets an element from the vector. If the given index is negative it will access the elements that
    /// were marked for insertion. The indexing for these elements starts at -1
    /// \param index The index of the element you want to access, can be negative
    /// \return Reference to the given object
    /// \note Bounds are checked
    /// \throws std::out_of_range if out of bounds
    T& at(ptrdiff_t index);

    /// \brief Gets an element from the vector. If the given index is negative it will access the elements that
    /// were marked for insertion. The indexing for these elements starts at -1
    /// \param index The index of the element you want to access, can be negative
    /// \return const reference to the given object
    /// \note Bounds are checked
    /// \throws std::out_of_range if out of bounds
    const T& at(ptrdiff_t index) const;


    /// \brief Gets the size of the section of current elements. The ones marked for removal are counted but
    /// the ones that will be inserted are not
    /// \return The no of elements.
    size_t size() const;

    /// \brief Gets an element from the temporal buffer used for adding elements
    /// \param index The index of the element in the add buffer, it must be negative and indexing starts at -1
    /// \return Reference to the element
    /// \note All references will be invalidated after a call to finishChanges();
    /// \note Bounds are checked.
    /// \throws std::out_of_range if out of bounds
    T& atAddBuffer(ptrdiff_t index);

    /// \brief The number of elements that will be added
    /// \return
    size_t sizeAddBuffer() const;

    /// \brief The number of elements that will be removed
    /// \return
    size_t sizeRemoveBuffer() const;

};

template <typename T>
SpecializedVector<T>::SpecializedVector(size_t reserve)
    :SpecializedVector(emptyUnaryFunction, emptyUnaryFunction, emptyUnaryFunction, std::swap,
                       emptyUnaryFunction, reserve)
{

}

template <typename T>
SpecializedVector<T>::SpecializedVector(InitToBeAddedFct_t<T> initAdd, InitToBeRemovedFct_t<T> initRemove,
                                        InitForFinaliseFct_t<T> initFinal, SwapFct_t<T> swap, DestructFct_t<T> destruct,
                                        size_t reserve)
        : m_initAdd{initAdd}, m_initRemove{initRemove}, m_initFinal{initFinal}, m_swap{swap}, m_destruct{destruct}
{
    m_data.reserve(reserve);
    m_addBuffer.reserve(reserve/2);
}


template <typename T>
ptrdiff_t SpecializedVector<T>::toBeAdded(const T &element)
{
    m_addBuffer.push_back(element);

    ptrdiff_t index = -1 * m_addBuffer.size();
    m_initAdd(m_addBuffer.back(), index);
    return index;
}

template <typename T>
ptrdiff_t SpecializedVector<T>::toBeAdded(T &&element)
{
    return toBeAdded(element);
}

template <typename T>
T &SpecializedVector<T>::toBeRemoved(std::size_t index)
{
    if (index >= m_data.size())
        throw std::out_of_range("Invalid index, check bounds!");
    //if the given element was already marked for removal, do nothing
    if (index >= m_startOfRemoveBuffer)
        return m_data[index];

    //we move the element to the back of the vector, right before the first element that needs to be removed;
    m_startOfRemoveBuffer--;
    m_swap(m_data[index], index, m_data[m_startOfRemoveBuffer], m_startOfRemoveBuffer);

    m_initRemove(m_data[m_startOfRemoveBuffer], m_startOfRemoveBuffer);


    return m_data[m_startOfRemoveBuffer];
}

template <typename T>
void SpecializedVector<T>::finishChanges()
{

    size_t i;

    //TODO: can size be negative?
    size_t sizeRemoveBuffer = m_data.size() - m_startOfRemoveBuffer;
    //we fill the spaces marked for deletion with elements that are marked for insertion
    for ( i = 0; i < m_addBuffer.size() and i < sizeRemoveBuffer; ++i)
    {
        int indexRemove = m_startOfRemoveBuffer;
        m_destruct(m_data[indexRemove], indexRemove);
        m_startOfRemoveBuffer++;

        m_data[indexRemove] = m_addBuffer[i];
        m_initFinal(m_data[indexRemove], indexRemove);
    }

    int noNewElements = m_addBuffer.size() - i;
    m_data.reserve(m_data.size() + noNewElements);

    //if we have more elements that need to be added than removed, add them to the back of the data vector
    for (; i < m_addBuffer.size(); ++i)
    {
        //we know that there are no more elements in the remove region situated at the back of the data
        m_data.push_back(m_addBuffer[i]);
        m_startOfRemoveBuffer++;
        m_initFinal(m_data.back(), m_data.size() - 1);
    }

    //else, if we need to remove more elements than we have to add, pop all of them out as they are already
    //at the back of the vector
    for (; i < sizeRemoveBuffer; ++i)
    {
        m_destruct(m_data.back(), m_data.size() - 1);

        m_data.pop_back();
    }

    // we could shrink the add buffer as we move the elements in the previous steps, although it would be a bit
    // more tedious to write the conditional branches
    m_addBuffer.clear();
}


template <typename T>
const T &SpecializedVector<T>::at(ptrdiff_t index) const
{
    //positive index starting from 0 with correct bound
    if (0 <= index and (size_t)index < m_data.size())
        return m_data[index];
        //negative index starting from 1 with correct bound
    else if (-1 * (ptrdiff_t)m_addBuffer.size() <= index and index < 0)
        return  m_addBuffer[-1 * index - 1];
        // we got an invalid index
    else
        throw std::out_of_range("Invalid index, check bounds!");

}

template <typename T>
T &SpecializedVector<T>::at(ptrdiff_t index)
{
    //positive index starting from 0 with correct bound
    if (0 <= index and (size_t)index < m_data.size())
        return m_data[index];
    //negative index starting from 1 with correct bound
    else if (-1 * (ptrdiff_t)m_addBuffer.size() <= index and index < 0)
        return  m_addBuffer[-1 * index - 1];
    // we got an invalid index
    else
        throw std::out_of_range("Invalid index, check bounds!");
}

template <typename T>
const T &SpecializedVector<T>::operator[](size_t index) const
{
    return m_data[index];
}

template <typename T>
T & SpecializedVector<T>::operator[](size_t index)
{
    return m_data[index];
}


template <typename T>
T &SpecializedVector<T>::atAddBuffer(ptrdiff_t index)
{
    //index is negative, so we need to convert it back to a positive having the origin in 0 instead of 1
    ptrdiff_t positiveIndex = -1 * index - 1;
    if (0 <= positiveIndex and (size_t)positiveIndex < m_addBuffer.size())
        return m_addBuffer[positiveIndex];
    else
        throw std::out_of_range("Invalid index, check bounds!");
}

template <typename T>
size_t SpecializedVector<T>::sizeAddBuffer() const
{
    return m_addBuffer.size();
}
template <typename T>
size_t SpecializedVector<T>::sizeRemoveBuffer() const
{
    return m_data.size() - m_startOfRemoveBuffer;
}


template <typename T>
size_t SpecializedVector<T>::size() const
{
    return m_data.size();
}


