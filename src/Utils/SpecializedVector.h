#pragma once
#include <vector>




template <typename T>
class SpecializedVector
{
private:
    //elements will
    std::vector<T> m_data = {};
    std::size_t m_eraseStart = 0;
    std::vector<T> m_addBuffer = {};

    InitFunction_t<T> m_init;
    SwapFunction_t<T> m_swap;


    [[nodiscard]] inline size_t m_actualDataSize() const;
    [[nodiscard]] inline size_t m_eraseSize() const;

    [[nodiscard]] inline bool m_emptyErase() const;

public:


    explicit SpecializedVector(InitFunction_t<T> init, SwapFunction_t<T> swap, size_t reserve = 128);

    T toBeRemoved(std::size_t index);
    void removeAll();

    void toBeAdded(T &&element);
    void toBeAdded(T &element);
    void addAll();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& at(size_t index);
    const T& at(size_t index) const;

    inline size_t size() const;

    /// \brief Gets an element from the temporal buffer used for adding elements
    /// \param index The index of the element in the add buffer
    /// \return Reference to the element
    /// \note All references will be invalidated after a call to addAll();
    /// \note No index validation
    T& atAddBuffer(size_t index);
    inline size_t sizeAddBuffer() const;

};


template <typename T>
const T &SpecializedVector<T>::at(size_t index) const
{
    return m_data[index];
}

template <typename T>
const T &SpecializedVector<T>::operator[](size_t index) const
{
    return m_data[index];
}

template <typename T>
T &SpecializedVector<T>::at(size_t index)
{
    return m_data[index];
}

template <typename T>
T &SpecializedVector<T>::atAddBuffer(size_t index)
{
    return m_addBuffer[index];
}

template <typename T>
size_t SpecializedVector<T>::sizeAddBuffer() const
{
    return m_addBuffer.size();
}


template <typename T>
T SpecializedVector<T>::toBeRemoved(std::size_t index)
{
    m_eraseStart--;

    m_swap(m_data[index], index, m_eraseStart, m_data[m_eraseStart]);

    return *m_data[m_eraseStart];
}


template <typename T>
SpecializedVector<T>::SpecializedVector(InitFunction_t<T> init, SwapFunction_t<T> swap, size_t reserve)
    : m_init{init}, m_swap{swap}
{
    m_data.reserve(reserve);
    m_addBuffer.reserve(reserve);
}


template <typename T>
size_t SpecializedVector<T>::m_actualDataSize() const
{
    return m_eraseStart;
}


template <typename T>
T & SpecializedVector<T>::operator[](size_t index)
{
    return m_data[index];
}



template <typename T>
bool SpecializedVector<T>::m_emptyErase() const
{
    return m_eraseStart == m_data.size();
}


template <typename T>
void SpecializedVector<T>::toBeAdded(T &element)
{
    m_addBuffer.push_back(element);
}

template <typename T>
void SpecializedVector<T>::toBeAdded(T &&element)
{
    toBeAdded(element);
}

template <typename T>
void SpecializedVector<T>::removeAll()
{
    for (size_t i = 0; i < m_eraseSize(); ++i)
        m_data.pop_back();
}


template <typename T>
size_t SpecializedVector<T>::m_eraseSize() const
{
    return m_data.size() - m_eraseStart;
}


template <typename T>
void SpecializedVector<T>::addAll()
{

    size_t noNewElements = m_addBuffer.size();
    for (size_t i = 0; i < noNewElements; ++i)
    {
        //pull out the last element and add it to the back of the data vector
        m_data.push_back(m_addBuffer.back());
        m_addBuffer.pop_back();

        //init the world knowledge with the vector indices
        m_init(m_data.back(), m_data.size() - 1);

        //move the newly added element from the back of the whole vector to the back
        //of the active elements region
        //the first element that is supposed to be deleted will be moved to the back o
        //of the whole vector
        size_t last = m_data.size() - 1;
        m_swap(m_data[m_eraseStart], m_eraseStart, m_data[last], last);

        //translate the region of erased element one unit to the right to make the start
        //region valid again
        m_eraseStart++;
    }

}

template <typename T>
size_t SpecializedVector<T>::size() const
{
    return m_actualDataSize();
}


