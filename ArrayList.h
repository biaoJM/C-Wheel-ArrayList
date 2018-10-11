// ArrayList.h
// java中的ArrayList是引用的数组，连续的存储空间中存放的是对象的引用
#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H

#define DEFAULT_CAPACITY (100)
#define INCREASE_CAPACITY_PER (10)

#define FALSE (0)
#define TRUE  (1)

typedef struct ArrayList ArrayList;
struct ArrayList
{
    void** item_list;
    int capacity;
    int my_size;
    
    // Appends the specified element to the end of this list.
    int (*add_last)(ArrayList* al,void* e);
    // Inserts the specified element at the specified position in this list.
    int (*add_index)(ArrayList* al,int index, void* element);
    // Appends all of the elements in the specified collection to the end of this list, in the order that they are returned by the specified collection's Iterator.    
    int	(*addAll_last)(ArrayList* al,void** c,int length);
    // Inserts all of the elements in the specified collection into this list, starting at the specified position.
    int	(*addAll_index)(ArrayList* al,int index, void** c,int length);
    // Removes all of the elements from this list.
    void (*clear)(ArrayList* al);
    // Returns a shallow copy of this ArrayList instance.
    int (*clone)(ArrayList* al,ArrayList* al_clone);
    // Returns true if this list contains the specified element.
    int	(*contains)(ArrayList* al,void* o);
    // Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
    int (*ensureCapacity)(ArrayList* al,int minCapacity);
    // Returns the element at the specified position in this list.
    void* (*get)(ArrayList* al,int index);
    // Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
    int	(*indexOf)(ArrayList* al,void* o);
    // Returns true if this list contains no elements.
    int	(*isEmpty)(ArrayList* al);
    // Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
    int	(*lastIndexOf)(ArrayList* al,void* o);
    // Removes the element at the specified position in this list.
    void* (*remove_index)(ArrayList* al,int index);
    // Removes the first occurrence of the specified element from this list, if it is present.
    int	(*remove_obj)(ArrayList* al,void* o);
    // Removes from this list all of its elements that are contained in the specified collection.
    int	(*removeAll)(ArrayList* al,void** c,int length);
    // Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
    void (*removeRange)(ArrayList* al,int fromIndex, int toIndex);
    // Retains only the elements in this list that are contained in the specified collection.
    int	(*retainAll)(ArrayList* al,void** c,int length);
    // Replaces the element at the specified position in this list with the specified element.
    void* (*set)(ArrayList* al,int index, void* element);
    // Returns the number of elements in this list.
    int	(*size)(ArrayList* al);
    // Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
    ArrayList* (*subArrayList)(ArrayList* al,int fromIndex, int toIndex);
    // Trims the capacity of this ArrayList instance to be the list's current size.
    int (*trimToSize)(ArrayList* al);
};

int init_ArrayList(ArrayList*);
// create a new ArrayList
int init_ArrayList_capacity(ArrayList*,int capacity);
// create a new ArrayList with specified capacity

#endif