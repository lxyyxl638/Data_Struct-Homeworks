/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashCode'',
 * which takes a parameter of type K and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashCode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * Hash function passed to this class should observe the following rule: if two keys
 * are equal (which means key1 == key2), then the hash code of them should be the
 * same. However, it is not generally required that the hash function should work in
 * the other direction: if the hash code of two keys are equal, the two keys could be
 * different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash function.
 * This is to say that, even the given hash function always returns the same hash code
 * for all keys (thus causing a serious collision), methods of HashMap should still
 * function correctly, though the performance will be poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be guaranteed
 * that each (key, value) pair be iterated exactly once.
 */
template <class K, class V, class H>
class HashMap
{

 public:
    class Entry
    {
        K key;
        V value;
    public:
        friend class HashMap<K,V,H>;
        Entry(){}
        Entry(K k, V v)
        {
            key = k;
            value = v;
        }

        K getKey() const
        {
            return key;
        }

        V getValue() const
        {
            return value;
        }
    };
    private:
        struct Node
            {
               Entry data;
               Node *next;
               Node(const Entry &x):data(x),next(NULL){}
               Node():data(Entry()),next(NULL){}
            } ;
         static const int inf = 999983;
         Node **Hash;
         int Size;
         int Hashmod(int num)const
          {
              while (num < 0)
                num+=inf;
              return (num % inf);
          }
         static H HH;
   public:
    class Iterator
    {

     private:
         const HashMap<K,V,H> *Point;
         int currentsize;
         int num;
         Node *now;
     public:
         Iterator(const HashMap<K,V,H> *x);
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext();

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Entry &next();
    };

    /**
     * TODO Constructs an empty hash map.
     */
    HashMap();

    /**
     * TODO Destructor
     */
    ~HashMap();

    /**
     * TODO Assignment operator
     */
    HashMap &operator=(const HashMap &x);

    /**
     * TODO Copy-constructor
     */
    HashMap(const HashMap &x);

    /**
     * TODO Returns an iterator over the elements in this map.
     */
    Iterator iterator() const;

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear();

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const;

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const;

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const;

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const;

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    void put(const K &key, const V &value);

    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key);

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const;
};

template<class K, class V,class H>
HashMap<K,V,H>::HashMap()
{
    Hash=new Node*[inf];
    Size=0;
    for (int i=0;i<inf;++i)
      Hash[i]=new Node;
}
template <class K,class V,class H>
HashMap<K,V,H>::~HashMap()
{
    Node *p,*q;
    Size=0;
    for (int i=0;i<inf;++i)
    {
        p=Hash[i];
        do
        {
          q=p->next;
          delete p;
          p=q;
        }while (p!=NULL);
    }
    delete [] Hash;
}

template <class K,class V,class H>
HashMap<K,V,H> & HashMap<K,V,H>::operator=(const HashMap &x)
{
    if (this == &x) return *this;
    Node *p,*px;
    clear();
    Size=x.Size;
    for (int i=0;i<inf;++i)
    {
        p=Hash[i];
        px=x.Hash[i]->next;
        while (px!=NULL)
        {
            Node *tmp=new Node(px->data);
            p->next=tmp;
            p=p->next;
            px=px->next;
        }
    }
    return *this;
}

template<class K,class V,class H>
HashMap<K,V,H>::HashMap(const HashMap &x)
{
    Node *p,*px;
    Size=x.Size;
    Hash=new Node*[inf];
    for (int i=0;i<inf;++i)
    {
        Hash[i]=new Node;
        p=Hash[i];
        px=(x.Hash[i])->next;
        while (px!=NULL)
        {
            Node *tmp=new Node(px->data);
            p->next=tmp;
            p=p->next;
            px=px->next;
        }
    }
}

template<class K,class V,class H>
typename HashMap<K,V,H>::Iterator HashMap<K,V,H>::iterator() const
{
    return (Iterator(this));
}

template<class K, class V,class H>
void HashMap<K,V,H>::clear()
{
    Node *p,*q;
    Size=0;
    for (int i=0;i<inf;++i)
    {
        p=Hash[i]->next;
        while (p!=NULL)
        {
          q=p->next;
          delete p;
          p=q;
        }
        Hash[i]->next=NULL;
    }
}

template<class K, class V,class H>
bool HashMap<K,V,H>::containsKey(const K &key) const
{
    Node *p;
    int hashnum=Hashmod(HH.hashCode(key));
    p=Hash[hashnum]->next;
    while (p!=NULL)
    {
        if ((p->data).getKey()==key) return true;
        else p=p->next;
    }
    return false;
}

template<class K, class V,class H>
bool HashMap<K,V,H>::containsValue(const V &value) const
{
    Node *p;
    for (int i=0;i<inf;++i)
    {
        p=Hash[i]->next;
        while (p!=NULL)
        {
            if ((p->data).getValue()==value) return true;
            else p=p->next;
        }
    }
    return false;
}


template<class K, class V,class H>
const V & HashMap<K,V,H>::get(const K &key) const
{
    if (!containsKey(key)) throw ElementNotExist();
    Node *p;
    int hashnum=Hashmod(HH.hashCode(key));
    p=Hash[hashnum]->next;
    while (p!=NULL)
    {
        if ((p->data).getKey()==key) break;
        else p=p->next;
    }
  return (p->data).value;
}

template<class K, class V,class H>
bool HashMap<K,V,H>::isEmpty() const
{
    if (Size==0) return true;
    else return false;
}

template<class K, class V,class H>
void HashMap<K,V,H>::put(const K &key, const V &value)
{
    int hashnum=Hashmod(HH.hashCode(key));
    Node *p;
    p=Hash[hashnum]->next;
    while (p!=NULL)
    {
        if ((p->data).getKey()==key)
        {
            (p->data).value=value;
            return;
        }
        else p=p->next;
    }
    p=new Node(Entry(key,value));
    p->next=Hash[hashnum]->next;
    Hash[hashnum]->next=p;
    ++Size;
}


template<class K, class V,class H>
void HashMap<K,V,H>::remove(const K &key)
{
    if (!containsKey(key)) throw ElementNotExist();
    int hashnum=Hashmod(HH.hashCode(key));
    --Size;
    Node *pre=Hash[hashnum];
    while (pre->next!=NULL)
    {
        Node *q=pre->next;
        if ((q->data).getKey()==key)
        {
            pre->next=q->next;
            delete q;
            return;
        }
        pre=q;
    }
   return;
}
template<class K, class V,class H>
int HashMap<K,V,H>::size() const
{
    return Size;
}
template<class K, class V,class H>
HashMap<K,V,H>::Iterator::Iterator(const HashMap<K,V,H> *x)
{
    Point=x;
    currentsize=0;
    num=0;
    now=Point->Hash[0];
}
template<class K, class V,class H>
bool HashMap<K,V,H>::Iterator::hasNext()
{
    if (currentsize<Point->Size) return true;
    else return false;
}

template<class K, class V,class H>
const typename HashMap<K,V,H>::Entry & HashMap<K,V,H>::Iterator::next()
{
    if (!hasNext()) throw ElementNotExist();
    while (now->next==NULL)
    {
        ++num;
        now=Point->Hash[num];
    }
    now=now->next;
    ++currentsize;
    return now->data;
}
#endif
