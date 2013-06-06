/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T>
class LinkedList
{
private:
     struct node
     {
         T data;
         node *prev,*next;
         node(const T &x,node *p=NULL,node *n=NULL):data(x), prev(p), next(n){}
         node():prev(NULL), next(NULL){}
         ~node(){}
     };
     node *head,*tail;
     int currentLength;
     node * move(int i)const;
public:
    class Iterator
    {
    private:
        node *now;
        LinkedList *point;
        bool Flag;
    public:
        Iterator(LinkedList *s);
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() ;

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() ;

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove() ;
    };

    /**
     * TODO Constructs an empty linked list
     */
    LinkedList() ;

    /**
     * TODO Copy constructor
     */
    LinkedList(const LinkedList<T> &c) ;

    /**
     * TODO Assignment operator
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) ;

    /**
     * TODO Desturctor
     */
    ~LinkedList() ;

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) ;

    /**
     * TODO Inserts the specified element to the beginning of this list.
     */
    void addFirst(const T& elem) ;

    /**
     * TODO Insert the specified element to the end of this list.
     * Equivalent to add.
     */
    void addLast(const T &elem) ;

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element) ;

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear() ;

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const ;

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const ;

    /**
     * TODO Returns a const reference to the first element.
     * @throw ElementNotExist
     */
    const T& getFirst() const ;

    /**
     * TODO Returns a const reference to the last element.
     * @throw ElementNotExist
     */
    const T& getLast() const ;

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const ;

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index) ;

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e) ;

    /**
     * TODO Removes the first element from this list.
     * @throw ElementNotExist
     */
    void removeFirst() ;

    /**
     * TODO Removes the last element from this list.
     * @throw ElementNotExist
     */
    void removeLast() ;

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element) ;

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const ;

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    Iterator iterator() ;
};

template <class T>
LinkedList<T>::Iterator::Iterator(LinkedList *s)
{
   point=s;
   now=point->head;
   Flag=false;
}
template <class T>
bool LinkedList<T>::Iterator::hasNext()
{
    if ((point->currentLength>0)&&((now->next!=point->tail)||(now==point->head))) return true;
    else return false;
}//TODO Returns true if the iteration has more elements.

template <class T>
const T & LinkedList<T>::Iterator::next()
{
    if (!hasNext()) throw ElementNotExist();
    now=now->next;
    Flag=true;
    return now->data;
}/**
   TODO Returns the next element in the iteration.
   @throw ElementNotExist exception when hasNext() == false
  */

template <class T>
void LinkedList<T>::Iterator::remove()
{
    if (!Flag||now==point->head) throw ElementNotExist();
    Flag=false;
    node *p=now;
    now=now->prev;
    now->next=p->next;
    now->next->prev=now;
    delete p;
    --point->currentLength;
}/**
 * TODO Removes from the underlying collection the last element
 * returned by the iterator
 * The behavior of an iterator is unspecified if the underlying
 * collection is modified while the iteration is in progress in
 * any way other than by calling this method.
 * @throw ElementNotExist
 */

template <class T>
LinkedList<T>::LinkedList()
{
   currentLength=0;
   head=new node;
   tail=head;
   head->next=tail;
   tail->prev=head;
}//TODO Constructs an empty linked list


template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &c)
{
    node *tmp1,*tmp2,*tmp;
    currentLength=c.size();
    head=new node;
    tail=head;
    head->next=tail;
    tail->prev=head;
    tmp2=c.head;
    tmp1=head;
    for (int i=0;i<currentLength;++i)
    {
        tmp2=tmp2->next;
        tmp=new node;
        tmp->data=tmp2->data;
        tmp->prev=tmp1;
        tmp->next=tail;
        tmp1->next=tmp;
        tmp1=tmp;
    }
}//TODO Copy constructor

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &c)
{
    node *tmp1,*tmp2,*tmp;
    if (this==&c) return *this;
    clear();
    currentLength=c.size();
   // head=new node;
   // tail=head;
    head->next=tail;
    tail->prev=head;
    tmp2=c.head;
    tmp1=head;
    for (int i=0;i<currentLength;++i)
    {
        tmp2=tmp2->next;
        tmp=new node;
        tmp->data=tmp2->data;
        tmp->prev=tmp1;
        tmp->next=tail;
        tmp1->next=tmp;
        tmp1=tmp;
    }
    return *this;
}//TODO Assignment operator


template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete head;
}

template <class T>
typename LinkedList<T>::node * LinkedList<T>::move(int index)const
{
   node *tmp=head;
   if (index+index<currentLength)
    for (int i=0;i<index;++i)
      tmp=tmp->next;
    else
     for (int i=0;i<currentLength-index+1;++i)
       tmp=tmp->prev;
    return tmp;
}

template <class T>
bool LinkedList<T>::add(const T& e)
{
   add(currentLength,e);
   return true;
}/**
  * TODO Appends the specified element to the end of this list.
  * Always returns true.
  */

template <class T>
void LinkedList<T>::addFirst(const T& elem)
{
    add(0,elem);
}//TODO Inserts the specified element to the beginning of this list.


template <class T>
void LinkedList<T>::addLast(const T &elem)
{
   add(elem);
}/**
 * TODO Insert the specified element to the end of this list.
 * Equivalent to add.
 */

template <class T>
void LinkedList<T>::add(int index, const T& element)
{
   if (index<0||index>currentLength) throw IndexOutOfBound();
   node *tmp=move(index);
   node *newnode= new node;
   newnode->data=element;
   newnode->prev=tmp;
   newnode->next=tmp->next;
   tmp->next=newnode;
   tmp=newnode->next;
   tmp->prev=newnode;
   ++currentLength;
}/**
 * TODO Inserts the specified element to the specified position in this list.
 * The range of index parameter is [0, size], where index=0 means inserting to the head,
 * and index=size means appending to the end.
 * @throw IndexOutOfBound
 */

template <class T>
void LinkedList<T>::clear()
{
    node *p=head->next,*q;
    head->next=tail;
    tail->prev=head;
    while (p!=tail)
    {
        q=p->next;
        delete p;
        p=q;
    }
    currentLength=0;
}//TODO Removes all of the elements from this list.

template <class T>
bool LinkedList<T>::contains(const T& e) const
{
   node *p=head->next;
   while (p!=tail)
   {
       if (p->data==e) return true;
       p=p->next;
   }
   return false;
}

template <class T>
const T& LinkedList<T>::get(int index) const
{
    if (index<0||index>=currentLength) throw IndexOutOfBound();
    node *p=move(index);
    p=p->next;
    return p->data;
}/**
 * TODO Returns a const reference to the element at the specified position in this list.
 * The index is zero-based, with range [0, size).
 * @throw IndexOutOfBound
 */
template <class T>
const T& LinkedList<T>::getFirst() const
{
   if (currentLength==0) throw ElementNotExist();
   else return get(0);
}/**
   * TODO Returns a const reference to the first element.
   * @throw ElementNotExist
   */

template <class T>
const T& LinkedList<T>::getLast() const
{
    if (currentLength==0) throw ElementNotExist();
    else return get(currentLength-1);
}/**
 * TODO Returns a const reference to the last element.
 * @throw ElementNotExist
 */

template <class T>
bool LinkedList<T>::isEmpty() const
{
   if (currentLength==0) return true;
   else return false;
}//TODO Returns true if this list contains no elements.

template <class T>
void LinkedList<T>::removeIndex(int index)
{
   if (index<0||index>=currentLength) throw IndexOutOfBound();
   node *p=move(index),*q;
   q=p->next;
   p->next=q->next;
   q->next->prev=p;
   delete q;
   --currentLength;
}/**
 * TODO Removes the element at the specified position in this list.
 * The index is zero-based, with range [0, size).
 * @throw IndexOutOfBound
 */

template <class T>
bool LinkedList<T>::remove(const T &e)
{
   node *p=head->next;
   int num=0;
   while (p!=tail)
   {
       if (p->data==e)
       {
           removeIndex(num);
           return true;
       }
       ++num;
       p=p->next;
   }
   return false;
}/**
 * TODO Removes the first occurrence of the specified element from this list, if it is present.
 * Returns true if it was present in the list, otherwise false.
 */
template <class T>
void LinkedList<T>::removeFirst()
{
    if (currentLength==0) throw ElementNotExist();
    removeIndex(0);
}/**
 * TODO Removes the first element from this list.
 * @throw ElementNotExist
 */
template <class T>
void LinkedList<T>::removeLast()
{
    if (currentLength==0) throw ElementNotExist();
    removeIndex(currentLength-1);
}/**
 * TODO Removes the last element from this list.
 * @throw ElementNotExist
 */

template <class T>
void LinkedList<T>::set(int index, const T &element)
{
    if (index<0||index>=currentLength) throw IndexOutOfBound();
    node *p=move(index+1);
    p->data=element;
}/**
 * TODO Replaces the element at the specified position in this list with the specified element.
 * The index is zero-based, with range [0, size).
 * @throw IndexOutOfBound
 */

template <class T>
int LinkedList<T>::size() const
{
    return currentLength;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::iterator()
{
    return Iterator(this);
}//TODO Returns an iterator over the elements in this list.
#endif
