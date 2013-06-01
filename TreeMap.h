/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"
#include <cstdio>

/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */

template<class K, class V>
class TreeMap
{

public:
    class Entry
    {
        friend class TreeMap<K, V>;
        K key;
        V value;
    public:
        Entry(){}
        ~Entry(){}
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
         Entry keyword;
         Node *father,*left,*right;
         Node():father(NULL),left(NULL),right(NULL){}
         Node(K key,V value)
         {
             keyword.key=key;
             keyword.value=value;
             father=NULL;
             left=NULL;
             right=NULL;
         }
         ~Node(){}
      };
    int Size;
   public:
    mutable Node *root;
    class Iterator
    {
    private:
        const TreeMap<K,V> *tree;
        int nowsize;
        Node *now,*tmp;
    public:
        Iterator(const TreeMap<K,V> * x);
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
     * TODO Constructs an empty tree map.
     */
    TreeMap();

    /**
     * TODO Destructor
     */
    ~TreeMap();

    /**
     * TODO Assignment operator
     */
    TreeMap &operator=(const TreeMap &x);

    /**
     * TODO Copy-constructor
     */
    TreeMap(const TreeMap &x);

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
    void Copy(Node *a,Node *b);
    static Node * Splay(Node *x);
    static void Zig(Node *x);
    static void Zag(Node *x);
    bool Findvalue(Node *s,const V &value)const;
    Node * findmax(Node *s1);
    Node *join(Node *s1,Node *s2);
};

template <class K,class V>
TreeMap<K,V>::Iterator::Iterator(const TreeMap<K,V> * x)
{
    tree = x;
    now = x->root;
    if (now != NULL)
        while (now->left) now= now->left;
    nowsize=0;
}
    template <class K,class V>
bool TreeMap<K,V>::Iterator::hasNext()
{
    if (nowsize<tree->Size) return true;
    else return false;
}//TODO Returns true if the iteration has more elements.


    template <class K,class V>
const typename TreeMap<K,V>::Entry & TreeMap<K,V>::Iterator::next()
{
    if (!hasNext()) throw ElementNotExist();
    ++nowsize;
    tree->root = TreeMap::Splay(now);
    now=tree->root;
    tmp=now;
    if (now->right==NULL) now=NULL;
    else
    {
        now=now->right;
        while (now->left!=NULL)
            now=now->left;
    }
    return tmp->keyword;
}/**
  * TODO Returns the next element in the iteration.
  * @throw ElementNotExist exception when hasNext() == false
  */

    template <class K,class V>
void TreeMap<K,V>::Zig(Node *x)
{
    Node *p=x->father;
    p->left=x->right;
    if (x->right!=NULL) x->right->father=p;
    x->right=p;
    x->father=p->father;
    p->father=x;
    if (x->father!=NULL)
    {
        if ((x->father->keyword).key<(x->keyword).key) x->father->right=x;
        else x->father->left=x;
    }
}
    template <class K,class V>
void TreeMap<K,V>::Zag(Node *x)
{
    Node *p=x->father;
    p->right=x->left;
    if (x->left!=NULL) x->left->father=p;
    x->left=p;
    x->father=p->father;
    p->father=x;
    if (x->father!=NULL)
    {
        if ((x->father->keyword).key<(x->keyword).key) x->father->right=x;
        else x->father->left=x;
    }
}
    template <class K,class V>
typename TreeMap<K,V>::Node * TreeMap<K,V>::Splay(Node *x)
{

    Node *p;
    while (x->father!=NULL)
    {
        p=x->father;
        if (p->father==NULL)
        {
            if (x==p->left) Zig(x);
            if (x==p->right) Zag(x);
        }
        else
        {
            Node *g=p->father;
            if (g->left==p && p->left==x)
            {
                Zig(p);
                Zig(x);
            }
            else if (g->left==p &&p->right==x)
            {
                Zag(x);
                Zig(x);
            }
            else if (g->right==p &&p->right==x)
            {
                Zag(p);
                Zag(x);
            }
            else if (g->right==p&&p->left==x)
            {
                Zig(x);
                Zag(x);
            }
        }
    }
    return x;
}
template <class K,class V>
TreeMap<K,V>::TreeMap()
{
    Size=0;
    root=NULL;
}//TODO Constructs an empty tree map.


template <class K,class V>
TreeMap<K,V>::~TreeMap()
{
    while (Size>0)
        remove((root->keyword).getKey());
}//TODO Destructor

template <class K,class V>
void TreeMap<K,V>::Copy(Node *a,Node *b)
{
    b->keyword=a->keyword;
    if (a->left!=NULL)
    {
        b->left=new Node;
        b->left->father=b;
        Copy(a->left,b->left);
    }
    if (a->right!=NULL)
    {
        b->right=new Node;
        b->right->father=b;
        Copy(a->right,b->right);
    }
}
    template <class K,class V>
TreeMap<K,V> & TreeMap<K,V>::operator=(const TreeMap<K,V> &x)
{
    if (this==&x) return *this;
    clear();
    if (x.Size==0) return *this;
    Size=x.Size;
    root = new Node;
    Copy(x.root,root);
    return *this;
}

    template <class K,class V>
TreeMap<K,V>::TreeMap(const TreeMap<K,V> &x)
{
    Size=x.Size;
    if (x.Size==0) return;
    root = new Node;
    Copy(x.root,root);
}


template <class K,class V>
typename TreeMap<K,V>::Iterator TreeMap<K,V>::iterator() const
{
    return Iterator(this);
}

    template <class K,class V>
void TreeMap<K,V>::clear()
{
    while (Size>0)
        remove((root->keyword).key);
}//TODO Removes all of the mappings from this map.

template <class K,class V>
bool TreeMap<K,V>::containsKey(const K &key) const
{
    Node *now;
    now=root;
    while (now!=NULL)
    {
        if ((now->keyword).getKey()==key) break;
        else if ((now->keyword).getKey()<key) now=now->right;
        else now=now->left;
    }
    if (now==NULL) return false;
    root=Splay(now);
    return true;
} //TODO Returns true if this map contains a mapping for the specified key.

template <class K,class V>
bool TreeMap<K,V>::Findvalue(Node *s,const V &value)const
{
    bool Flag=false;
    if (s==NULL) return false;
    if ((s->keyword).value==value) return true;
    if (s->left!=NULL) Flag=Findvalue(s->left,value);
    if ((!Flag)&&(s->right!=NULL)) Flag=Findvalue(s->right,value);
    return Flag;
}


template <class K,class V>
bool TreeMap<K,V>::containsValue(const V &value) const
{
    return Findvalue(root,value);
}

template <class K,class V>
const V & TreeMap<K,V>::get(const K &key) const
{
    if (!containsKey(key)) throw ElementNotExist();
    return (root->keyword).value;
}
/**
 * TODO Returns a const reference to the value to which the specified key is mapped.
 * If the key is not present in this map, this function should throw ElementNotExist exception.
 * @throw ElementNotExist
 */

template <class K,class V>
bool TreeMap<K,V>::isEmpty() const
{
    if (Size==0) return true;
    else return false;
}

    template <class K,class V>
void TreeMap<K,V>::put(const K &key, const V &value)
{
    if (containsKey(key))
    {
        (root->keyword).value=value;
        return;
    }
    ++Size;
    if (root==NULL)
    {
        root=new Node(key,value);
        return;
    }
    Node *now,*tmp;
    now=root;
    tmp=new Node;
    while (now!=NULL)
    {
        if ((now->keyword).key<key)
        {
            if (now->right!=NULL) now=now->right;
            else {
                now->right=tmp;
                break;
            }
        }
        else
        {
            if (now->left!=NULL)  now=now->left;
            else {
                now->left=tmp;
                break;
            }
        }
    }
    tmp->father=now;
    (tmp->keyword).key = key;
    (tmp->keyword).value = value;
    root=Splay(tmp);
}//TODO Associates the specified value with the specified key in this map.

    template <class K,class V>
typename TreeMap<K,V>::Node * TreeMap<K,V>::findmax(Node *s1)
{
    Node *tmp;
    tmp=s1;
    while (tmp->right!=NULL)
        tmp=tmp->right;

    return Splay(tmp);
}
    template <class K,class V>
typename TreeMap<K,V>::Node * TreeMap<K,V>::join(Node *s1,Node *s2)
{
    if (s1!=NULL) s1->father=NULL;
    if (s2!=NULL) s2->father=NULL;
    if (s1==NULL) return s2;
    if (s2==NULL) return s1;

    s1=findmax(s1);
    s1->right=s2;
    s2->father=s1;
    return s1;
}

    template <class K,class V>
void TreeMap<K,V>::remove(const K &key)
{
    Node *s1,*s2,*tmp;
    if (!containsKey(key)) throw ElementNotExist();
    tmp=root;
    s1=root->left;
    s2=root->right;
    root=join(s1,s2);
    delete tmp;
    --Size;
}/**
  * TODO Removes the mapping for the specified key from this map if present.
  * If there is no mapping for the specified key, throws ElementNotExist exception.
  * @throw ElementNotExist
  */

template <class K,class V>
int TreeMap<K,V>::size() const
{
    return Size;
}
//TODO Returns the number of key-value mappings in this map.

#endif
