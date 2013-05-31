/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList
{
private:
    T *data;
    int currentLength;
    int maxSize;
    void DoubleArray();
public:
    class Iterator
    {
    private:
        int x;
        ArrayList *point;
        bool Flag;
    public:
        Iterator(ArrayList *s);
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext();

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next();

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove();
    };

    /**
     * TODO Constructs an empty array list.
     */
    ArrayList();

    /**
     * TODO Destructor
     */
    ~ArrayList();

    /**
     * TODO Assignment operator
     */
    ArrayList& operator=(const ArrayList& x);

    /**
     * TODO Copy-constructor
     */
    ArrayList(const ArrayList& x);

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e);

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element);

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear();

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const;

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const;

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const;

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index);

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e);

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element);

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const;

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    Iterator iterator();
};

template <class T>
ArrayList<T>::ArrayList()
{
   data=new T[10];
   maxSize=10;
   currentLength=0;
}//TODO Constructs an empty array list.

template <class T>
ArrayList<T>::~ArrayList()
{
    delete []data;
    maxSize=currentLength=0;
}//TODO Destructor

template<class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& x)
{
    if (this==&x) return *this;
    delete []data;
    data= new T[x.maxSize];
    maxSize=x.maxSize;
    currentLength=x.currentLength;
    for (int i=0;i<maxSize;++i)
       data[i]=x.data[i];

   return *this;
}//TODO Assignment operator
template<class T>
ArrayList<T>::ArrayList(const ArrayList& x)
{
     data=new T[x.maxSize];
     maxSize=x.maxSize;
     currentLength=x.currentLength;
     for (int i=0;i<maxSize;++i)
        data[i]=x.data[i];
}//TODO Copy-constructor

template<class T>
void ArrayList<T>::DoubleArray()
{
    T *tmp=data;
    maxSize*=2;
    data=new T[maxSize];
    for (int i=0;i<currentLength;++i)
        data[i]=tmp[i];

    delete []tmp;
}//expand array;

template<class T>
bool ArrayList<T>::add(const T& e)
{
    add(currentLength,e);
    return true;
}/**
 * TODO Appends the specified element to the end of this list.
 * Always returns true.
 */

template<class T>
void ArrayList<T>::add(int index, const T& element)
{
    if ((index<0)||(index>currentLength)) throw IndexOutOfBound();
    ++currentLength;
    if (currentLength==maxSize) DoubleArray();
    for (int i=currentLength;i>index;--i)
        data[i]=data[i-1];
    data[index]=element;
}
/**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index#include "array_list.h"=size means appending to the end.
     * @throw IndexOutOfBound
     */

template <class T>
void ArrayList<T>::clear()
{
    currentLength=0;
}//TODO Removes all of the elements from this list.

template <class T>
bool ArrayList<T>::contains(const T& e) const
{
    for (int i=0;i<currentLength;++i)
        if (e==data[i]) return true;
    return false;
}//TODO Returns true if this list contains the specified element.

template <class T>
const T& ArrayList<T>::get(int index) const
{
   if ((index<0)||(index>=currentLength)) throw IndexOutOfBound();
   return data[index];
}/**
  * TODO Returns a const reference to the element at the specified position in this list.
  * The index is zero-based, with range [0, size).
  * @throw IndexOutOfBound
  */

template <class T>
bool ArrayList<T>::isEmpty()const
{
    if (currentLength==0) return true;
    else return false;
} //TODO Returns true if this list contains no elements.

template <class T>
void ArrayList<T>::removeIndex(int index)
{
    if ((index<0)||(index>=currentLength)) throw IndexOutOfBound();
    --currentLength;
    for (int i=index;i<currentLength;++i)
        data[i]=data[i+1];
}/**
  * TODO Removes the element at the specified position in this list.
  * The index is zero-based, with range [0, size).
  * @throw IndexOutOfBound
  */

template <class T>
bool ArrayList<T>::remove(const T &e)
{
    for (int i=0;i<currentLength;++i)
      if (data[i]==e)
       {
          removeIndex(i);
          return true;
       }
    return false;
}/**
  * TODO Removes the first occurrence of the specified element from this list, if it is present.
  * Returns true if it was present in the list, otherwise false.
  */

template <class T>
void ArrayList<T>::set(int index, const T &element)
{
    if ((index<0)||(index>=currentLength)) throw IndexOutOfBound();
    data[index]=element;
} /**
   * TODO Replaces the element at the specified position in this list with the specified element.
   * The index is zero-based, with range [0, size).
   * @throw IndexOutOfBound
   */

template <class T>
int ArrayList<T>::size() const
{
   return currentLength;
}//TODO Returns the number of elements in this list.

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::iterator()
{
    return Iterator(this);
}//TODO Returns an iterator over the elements in this list.

template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList *s)
{
      point=s;
      x=-1;
      Flag=true;
}

template <class T>
bool ArrayList<T>::Iterator::hasNext()
{
    if ((point->currentLength>0)&&(x<((point->currentLength)-1))) return true;
    else return false;
}//TODO Returns true if the iteration has more elements.


template <class T>
const T &ArrayList<T>::Iterator::next()
{
     if (!hasNext()) throw ElementNotExist();
     ++x;
     Flag=false;
     return point->data[x];
}/**
   * TODO Returns the next element in the iteration.
   * @throw ElementNotExist exception when hasNext() == false
   */

template <class T>
void ArrayList<T>::Iterator::remove()
{
   if (Flag) throw ElementNotExist();
   Flag=true;
   point->removeIndex(x);
   --x;
}/**
 * TODO Removes from the underlying collection the last element
 * returned by the iterator
 * The behavior of an iterator is unspecified if the underlying
 * collection is modified while the iteration is in progress in
 * any way other than by calling this method.
 * @throw ElementNotExist
 */


#endif
