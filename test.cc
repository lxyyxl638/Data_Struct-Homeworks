#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "ArrayList.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "TreeMap.h"

using namespace std;
#define foreach(itr,c) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr)

void print_arrayList(ArrayList<int> &ai)
{
    for (ArrayList<int>::Iterator iter = ai.iterator();
            iter.hasNext(); )
        cout << iter.next() << " ";
    cout << endl;
    for (int i = 0; i < ai.size(); ++i)
        cout << ai.get(i) << " ";
    cout << endl;
}
void print_linkedList(LinkedList<int> &ai)
{
    for (LinkedList<int>::Iterator iter = ai.iterator();
            iter.hasNext(); )
        cout << iter.next() << " ";
    cout << endl;
    for (int i = 0; i < ai.size(); ++i)
        cout << ai.get(i) << " ";
    cout << endl;
}


void test_array_list()
{
    ArrayList<int> ai;
    for (int i = 0; i < 10; ++i)
        ai.add(i);
    ArrayList<int> bi = ai;
    print_arrayList(ai);
    print_arrayList(bi);
    for (int i = 0; i < 20; ++i)
    {
        if (ai.contains(i))
            cout << 1 << " ";
        else
            cout << 0 << " ";
    }
    cout << endl;
    for (int i = -10; i < 0; ++i)
        ai.add(0, i);
    print_arrayList(ai);
    for (int i = 0; i < 10; ++i)
        ai.set(i, i);
    print_arrayList(ai);
    for (int i = 0; i < 5; ++i)
        ai.removeIndex(i);
    print_arrayList(ai);
    for (int i = 5; i < 10; ++i)
        ai.remove(i);
    print_arrayList(ai);

    for (ArrayList<int>::Iterator iter = bi.iterator();
            iter.hasNext(); )
    {
        iter.next();
        iter.remove();
        if (iter.hasNext())
            iter.next();
        else
            break;
    }
    print_arrayList(bi);
}

void test_linked_list()
{
    LinkedList<int> ai;
    for (int i = 0; i < 10; ++i)
        ai.add(i);
    LinkedList<int> bi = ai;
    print_linkedList(ai);
    print_linkedList(bi);
    for (int i = 0; i < 20; ++i)
    {
        if (ai.contains(i))
            cout << 1 << " ";
        else
            cout << 0 << " ";
    }
    cout << endl;
    for (int i = -10; i < 0; ++i)
        ai.add(0, i);
    print_linkedList(ai);
    for (int i = 0; i < 10; ++i)
        ai.set(i, i);
    print_linkedList(ai);
    for (int i = 0; i < 5; ++i)
        ai.removeIndex(i);
    print_linkedList(ai);
    for (int i = 5; i < 10; ++i)
        ai.remove(i);
    print_linkedList(ai);

    for (LinkedList<int>::Iterator iter = bi.iterator();
            iter.hasNext(); )
    {
        iter.next();
        iter.remove();
        if (iter.hasNext())
            iter.next();
        else
            break;
    }
    print_linkedList(bi);

    for (int i = 0; i < 5; ++i) {
        ai.addFirst(i);
        ai.addLast(i);
        cout << ai.getFirst() << " " << ai.getLast() <<  endl;
    }
}
class HashInt {
public:
    static int hashCode(int obj) {
        return obj;
    }
};

void print_hashMap(HashMap<int, int, HashInt> his)
{
    std::vector<int> vi;
    for (HashMap<int, int, HashInt>::Iterator iter = his.iterator();
            iter.hasNext(); )
    {
        vi.push_back(iter.next().getKey());
    }
    sort(vi.begin(), vi.end());
    foreach(it,vi)
    {
        cout << *it << " " << his.get(*it) << endl;
    }
}

void test_hash_map()
{
    HashMap<int, int, HashInt> hii;
    for (int i = 9; i >= 0; --i) hii.put(i, i);
    print_hashMap(hii);
    HashMap<int, int, HashInt> hij = hii;
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i) hii.put(i, i+1);
    for (int i = 0; i < 20; ++i)
    {
        if (hii.containsKey(i)) cout << 1 << " ";
        else cout << 0 << " ";
        if (hii.containsValue(i)) cout << 1 << " ";
        else cout << 0 << " ";
    }
    cout << endl;
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i)
    {
        hii.remove(i);
        print_hashMap(hii);
        cout << hii.size() << endl;
    }
    if (hii.isEmpty()) cout << 1 << endl;
    else cout << 0 << endl;
    hij.clear();
    if (hij.isEmpty()) cout << 1 << endl;
    else cout << 0 << endl;
}

void print_treeMap(TreeMap<int, int> his)
{
    for (TreeMap<int, int>::Iterator iter = his.iterator();
            iter.hasNext(); )
    {
        TreeMap<int, int>::Entry he = iter.next();
        cout << he.getKey() << " " << he.getValue() << endl;
    }
}

void test_tree_map()
{
    TreeMap<int, int> hii;
    for (int i = 9; i >= 0; --i) hii.put(i, i);
    print_treeMap(hii);
    TreeMap<int, int> hij = hii;
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i) hii.put(i, i+1);
    for (int i = 0; i < 20; ++i)
    {
        if (hii.containsKey(i)) cout << 1 << " ";
        else cout << 0 << " ";
        if (hii.containsValue(i)) cout << 1 << " ";
        else cout << 0 << " ";
    }
    cout << endl;
    for (int i = 0; i < 10; ++i)
        cout << hii.get(i) << " ";
    cout << endl;
    for (int i = 0; i < 10; ++i)
    {
        hii.remove(i);
        print_treeMap(hii);
        cout << hii.size() << endl;
    }
    if (hii.isEmpty()) cout << 1 << endl;
    else cout << 0 << endl;
    hij.clear();
    if (hij.isEmpty()) cout << 1 << endl;
    else cout << 0 << endl;
}

int main()
{
    freopen("out.txt", "w", stdout);
    test_array_list();
    test_linked_list();
    test_hash_map();
    test_tree_map();
    return 0;
}
