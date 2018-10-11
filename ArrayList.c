#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// declare functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enlarge struct's capacity
int realloc_capacity(ArrayList* al);
// Appends the specified element to the end of this list.
static int add_last(ArrayList* al,void* e);
// Inserts the specified element at the specified position in this list.
static int add_index(ArrayList* al,int index, void* element);
// Appends all of the elements in the specified collection to the end of this list, in the order that they are returned by the specified collection's Iterator.    
static int	addAll_last(ArrayList* al,void** c,int length);
// Inserts all of the elements in the specified collection into this list, starting at the specified position.
static int	addAll_index(ArrayList* al,int index, void** c,int length);
// Removes all of the elements from this list.
static void clear(ArrayList* al);
// Returns a shallow copy of this ArrayList instance.
static int clone(ArrayList* al,ArrayList* al_clone);
// Returns true if this list contains the specified element.
static int	contains(ArrayList* al,void* o);
// Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
static int ensureCapacity(ArrayList* al,int minCapacity);
// Returns the element at the specified position in this list.
static void* get(ArrayList* al,int index);
// Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
static int	indexOf(ArrayList* al,void* o);
// Returns true if this list contains no elements.
static int	isEmpty(ArrayList* al);
// Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
static int	lastIndexOf(ArrayList* al,void* o);
// Removes the element at the specified position in this list.
static void* remove_index(ArrayList* al,int index);
// Removes the first occurrence of the specified element from this list, if it is present.
static int	remove_obj(ArrayList* al,void* o);
// Removes from this list all of its elements that are contained in the specified collection.
static int	removeAll(ArrayList* al,void** c,int length);
// Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
static void removeRange(ArrayList* al,int fromIndex, int toIndex);
// Retains only the elements in this list that are contained in the specified collection.
static int	retainAll(ArrayList* al,void** c,int length);
// Replaces the element at the specified position in this list with the specified element.
static void* set(ArrayList* al,int index, void* element);
// Returns the number of elements in this list.
static int	size(ArrayList* al);
// Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
static ArrayList* subArrayList(ArrayList* al,int fromIndex, int toIndex);
// Trims the capacity of this ArrayList instance to be the list's current size.
static int trimToSize(ArrayList* al);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// define functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * enlarge struct's capacity
 * param:   al:the ArrayList to be enlarge
 * return:  true if succeed / false if failed
 */
int realloc_capacity(ArrayList* al)
{
    void* new_list = (void**)realloc(al->item_list,sizeof(void*)*(al->capacity+INCREASE_CAPACITY_PER));
    if(!new_list)
        return FALSE;
    al->item_list = new_list;
    al->capacity+=INCREASE_CAPACITY_PER;
    return TRUE;
}
/*
 * create a new ArrayList
 * param:   al:the ArrayList to be initialized.
 * return:  void
 */
int init_ArrayList(ArrayList* al)
{
    al->item_list = (void**)malloc(sizeof(void*)*DEFAULT_CAPACITY);
    if(!al->item_list)
        return FALSE;
    al->my_size = 0;
    al->capacity = DEFAULT_CAPACITY;
    
    // functions
    al->add_last = &add_last;
    al->add_index = &add_index ;
    al->addAll_last = &addAll_last ;
    al->addAll_index = &addAll_index ;
    al->clear = &clear ;
    al->clone = &clone ;
    al->contains = &contains ;
    al->ensureCapacity = &ensureCapacity ;
    al->get = &get ;
    al->indexOf = &indexOf ;
    al->isEmpty = &isEmpty ;
    al->lastIndexOf = &lastIndexOf ;
    al->remove_index = &remove_index ;
    al->remove_obj = &remove_obj ;
    al->removeAll = &removeAll ;
    al->removeRange = &removeRange ;
    al->retainAll = &retainAll ;
    al->set = &set ;
    al->size = &size ;
    al->subArrayList = &subArrayList ;
    al->trimToSize = &trimToSize ;
    
    return TRUE;
}
/*
 * create a new ArrayList with specified capacity
 * param:   al:the ArrayList to be initialized.
 *          capacity:specified capacity to initialize with.
 * return:  void
 */
int init_ArrayList_capacity(ArrayList* al,int capacity)
{
    if(capacity<0)
        al->item_list = (void**)malloc(sizeof(void*)*DEFAULT_CAPACITY);
    else
        al->item_list = (void**)malloc(sizeof(void*)*capacity);
    if(!al->item_list)
        return FALSE;
    al->capacity = capacity<0?DEFAULT_CAPACITY:capacity;
    al->my_size = 0;
    
    // functions
    al->add_last = &add_last;
    al->add_index = &add_index ;
    al->addAll_last = &addAll_last ;
    al->addAll_index = &addAll_index ;
    al->clear = &clear ;
    al->clone = &clone ;
    al->contains = &contains ;
    al->ensureCapacity = &ensureCapacity ;
    al->get = &get ;
    al->indexOf = &indexOf ;
    al->isEmpty = &isEmpty ;
    al->lastIndexOf = &lastIndexOf ;
    al->remove_index = &remove_index ;
    al->remove_obj = &remove_obj ;
    al->removeAll = &removeAll ;
    al->removeRange = &removeRange ;
    al->retainAll = &retainAll ;
    al->set = &set ;
    al->size = &size ;
    al->subArrayList = &subArrayList ;
    al->trimToSize = &trimToSize ;
    
    return TRUE;
}
/*
 * Appends the specified element to the end of this list,even the element already in.
 * param:   al:the ArrayList to be added to.
 *          e:the element to be added.
 * return:  true if succeed / false if failed
 */
static int add_last(ArrayList* al,void* e)
{
    if(al->my_size>=al->capacity)
        if(!realloc_capacity(al))
            return FALSE;
    al->item_list[al->my_size] = e;
    al->my_size++;
    return TRUE;
}
/*
 * Inserts the specified element at the specified position in this list.
 * param:   al:the ArrayList to be added to.
 *          index:pos to insert.
 *          element:the element to be added
 * return:  true if succeed / false if failed
 */
static int add_index(ArrayList* al,int index, void* element)
{
    // if index is minus then insert into the begining.
    index = index<0?0:index;
    // if index out of size then append to the end.
    index = index>al->my_size?al->my_size:index;
    
    if(al->my_size>=al->capacity)
        if(!realloc_capacity(al))
            return FALSE;
    for(int i=al->my_size;i>index;i--)
        al->item_list[i] = al->item_list[i-1];
    al->item_list[index]=element;
    al->my_size++;
    return TRUE;
}
/*
 * Appends all of the elements in the specified collection to the end of this list, in the order that they are returned by the specified collection's Iterator.    
 * param:   al:the ArrayList to be added to.
 *          c:the list to add.
 *          length:length of parameter c
 * return:  true if succeed / false if failed
 */
static int	addAll_last(ArrayList* al,void** c,int length)
{
    for(int i=0;i<(al->my_size + length - al->capacity)/INCREASE_CAPACITY_PER+1;i++)
        if(!realloc_capacity(al))
            return FALSE;
    
    al->my_size+=length;
    for(int i=0;i<length;i++)
        al->item_list[al->my_size+i]=c[i];
    return TRUE;
}
/*
 * Inserts all of the elements in the specified collection into this list, starting at the specified position.
 * param:   al:the ArrayList to be added to.
 *          index:pos to insert. 
 *          c:the list to add.
 *          length:length of parameter c
 * return:  true if succeed / false if failed
 */
static int	addAll_index(ArrayList* al,int index, void** c,int length)
{
    for(int i=0;i<(al->my_size + length - al->capacity)/INCREASE_CAPACITY_PER+1;i++)
        if(!realloc_capacity(al))
            return FALSE;
        
    for(int i=al->my_size-1;i>=index;i--)
        al->item_list[i+length] = al->item_list[i];
    
    for(int i=index;i<index+length;i++)
        al->item_list[i]=c[i];
    return TRUE;
}
/*
 * Removes all of the elements from this list,but remain the capacity.
 * param:   al:the ArrayList to be cleard.
 * return:  void
 */
static void clear(ArrayList* al)
{
    al->my_size=0;
}
/*
 * Returns a shallow copy of this ArrayList instance.
 * param:   al:original ArrayList
 *          al_clone:destination ArrayList
 * return:  true if succeed / false if failed
 */
static int clone(ArrayList* al,ArrayList* al_clone)
{
    if(!init_ArrayList_capacity(al_clone,al->capacity))
        return FALSE;
    al_clone->my_size = al->my_size;
    al_clone->capacity = al->capacity;
    
    for(int i=0;i<al->my_size;i++)
        al_clone->item_list[i] = al->item_list[i];
    return TRUE;
}
/*
 * Returns true if this list contains the specified element.
 * param:   al:ArrayList
 *          o:object to identify
 * return:  true if found / false if failed to find
 */
static int contains(ArrayList* al,void* o)
{
    for(int i=0;i<al->my_size;i++)
        if(al->item_list[i]==o)
            return TRUE;
    return FALSE;
}
/*
 * Increases the capacity of this ArrayList instance, if necessary, to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
 * param:   al:ArrayList to be ensured
 *          minCapacity:the minimum capacity
 * return:  true if it can be ensured / false if cannot be ensured 
 */
static int ensureCapacity(ArrayList* al,int minCapacity)
{
    if(al->capacity>=minCapacity)
        return TRUE;
    for(int i=0;i<(minCapacity - al->capacity)/INCREASE_CAPACITY_PER+1;i++)
        if(!realloc_capacity(al))
            return FALSE;
    return TRUE;
}
/*
 * Returns the element at the specified position in this list.
 * param:   al:ArrayList to get from
 *          index:where you want to get
 * return:  null if index out of range / element if found  
 */
static void* get(ArrayList* al,int index)
{
    if(index<0 || index>=al->my_size)
        return NULL;
    return al->item_list[index];
}
/*
 * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
 * param:   al:ArrayList to search
 *          o:the object you want to find
 * return:  -1 if it is not here / index if found 
 */
static int indexOf(ArrayList* al,void* o)
{
    for(int i=0;i<al->my_size;i++)
        if(al->item_list[i]==o)
            return i;
    return -1;
}
/*
 * Returns true if this list contains no elements.
 * param:   the ArrayList you want to judge
 * return:  true if it is empty / false if it is not
 */
static int isEmpty(ArrayList* al)
{
    if(al->my_size<=0)return TRUE;
    else return FALSE;
}
/*
 * Returns the index of the last occurrence of the specified element in this list, or -1 if this list does not contain the element.
 * param:   al:the ArrayList you want to search from 
 *          o:the object you want to find
 * return:  -1 if it is not here / the last index if found 
 */
static int	lastIndexOf(ArrayList* al,void* o)
{
    for(int i=al->my_size-1;i>=0;i--)
        if(al->item_list[i]==o)
            return i;
    return -1;
}
/*
 * Removes the element at the specified position in this list,but the element is not freed.
 * param:   al:the ArrayList you want to search from 
 *          index:pos of the object you want to remove
 * return:  the element being removed / null if index out of bound
 */
static void* remove_index(ArrayList* al,int index)
{
    if(index<0 || index>=al->my_size)
        return NULL;
    void* removed = al->item_list[index];
    for(int i=index;i<al->my_size-1;i++)
        al->item_list[i]=al->item_list[i+1];
    al->my_size--;
    return removed;
}
/*
 * Removes the first occurrence of the specified element from this list, if it is present.but the element is not freed.
 * param:   al:the ArrayList you want to search from 
 *          o:the object you want to remove
 * return:  index of the element being removed / -1 if not found
 */
static int remove_obj(ArrayList* al,void* o)
{
    int index=0;
    for(index=0;index<al->my_size;index++)
        if(al->item_list[index]==o)
            break;
    if(index==al->my_size)return -1;
    for(int i=index;i<al->my_size-1;i++)
        al->item_list[i]=al->item_list[i+1];
    al->my_size--;
    return index;
}
/*
 * Removes from this list all of its elements that are contained in the specified collection.
 * param:   al:the ArrayList you want to remove from
 *          c:the list of elements to remove.
 *          length:length of parameter c
 * return:  number of elements being removed
 */
static int removeAll(ArrayList* al,void** c,int length)
{
    // find indexs of elements that have to be removed
    int index[al->my_size];
    int index_length=0;
    for(int i=0;i<al->my_size;i++)
        for(int j=0;j<length;j++)
            if(c[j]==al->item_list[i])
            {
                index[index_length++]=i;
                break;
            }
    // remove elements in the indexs
    if(index_length<=0)return 0;
    int i=index[0],k=1;
    for(int j=i+1;j<al->my_size;j++)
    {
        if(k<index_length && (index[k]==j)?k++:0)
            continue;
        al->item_list[i++]=al->item_list[j];
    }
    al->my_size-=index_length;
    return index_length;
}
/*
 * Removes from this list all of the elements whose index is between fromIndex, inclusive, and toIndex, exclusive.
 * param:   al:the ArrayList
 *          fromIndex:from where to remove
 *          toIndex:where to end removing
 * return:  size of the ArrayList
 */
static void removeRange(ArrayList* al,int fromIndex, int toIndex)
{
    fromIndex=fromIndex<0?0:fromIndex;
    toIndex=toIndex>=al->my_size?al->my_size-1:toIndex;
    
    if(fromIndex>toIndex)return;
    
    for(int i=fromIndex;i<=toIndex;i++)
        al->item_list[i]=al->item_list[i+toIndex-fromIndex];
    
    al->my_size-=toIndex-fromIndex+1;
}
/*
 * Retains only the elements in this list that are contained in the specified collection.
 * param:   al:the ArrayList you want to manipulate
 *          c:the list of elements to retain.
 *          length:length of parameter c
 * return:  number of elements being retained
 */
static int	retainAll(ArrayList* al,void** c,int length)
{
    // find indexs of elements that have to be removed
    int index[al->my_size];
    int index_length=0;
    int j=0;
    for(int i=0;i<al->my_size;i++)
    {
        for(j=0;j<length;j++)
            if(c[j]==al->item_list[i])
                break;
        if(j>=length)
            index[index_length++]=i;
    }

    // remove elements in the indexs
    if(index_length<=0)return 0;
    int i=index[0],k=1;
    for(int j=i+1;j<al->my_size;j++)
    {
        if(k<index_length && (index[k]==j)?k++:0)
            continue;
        al->item_list[i++]=al->item_list[j];
    }
    al->my_size-=index_length;
    return index_length;
}
/*
 * Replaces the element at the specified position in this list with the specified element.
 * param:   al:the ArrayList
 *          index - index of the element to replace
 *          element - element to be stored at the specified position
 * return:  the element previously at the specified position / null if index out of bound
 */
static void* set(ArrayList* al,int index, void* element)
{
    if(index<0 || index>=al->my_size)return NULL;
    
    void* pre = al->item_list[index];
    al->item_list[index] = element;
    return pre;
}
/*
 * Returns the number of elements in this list.
 * param:   al:the ArrayList
 * return:  size of the ArrayList
 */
static int size(ArrayList* al)
{
    return al->my_size;
}
/*
 * Returns a view of the portion of this list between the specified fromIndex, inclusive, and toIndex, exclusive.
 * param:   al:the ArrayList
 *          fromIndex - low endpoint (inclusive) of the subList
 *          toIndex - high endpoint (exclusive) of the subList
 * return:  the pointer of new ArrayList / new ArrayList with nothing if fromIndex lower than toIndex / NULL if failed
 */
static ArrayList* subArrayList(ArrayList* al,int fromIndex, int toIndex)
{
    // range judge
    fromIndex=fromIndex<0?0:fromIndex;
    toIndex=toIndex>=al->my_size?al->my_size-1:toIndex;
    // init new ArrayList
    ArrayList* new_one=(ArrayList*)malloc(sizeof(ArrayList));
    if(!new_one)return NULL;
    if( !init_ArrayList_capacity(
            new_one
            ,DEFAULT_CAPACITY<(toIndex-fromIndex+1)
                ?
                ((toIndex-fromIndex+1)/INCREASE_CAPACITY_PER+1)*INCREASE_CAPACITY_PER
                :
                DEFAULT_CAPACITY
        )
    )return NULL;
    // copy elements
    new_one->my_size = toIndex-fromIndex+1;
    for(int i=0;i<=toIndex-fromIndex;i++)
        new_one->item_list[i]=al->item_list[fromIndex+i];
    return new_one;
}
/*
 * Trims the capacity of this ArrayList instance to be the list's current size.
 * param:   al:the ArrayList
 * return:  true if succeed / false if failed
 */
static int trimToSize(ArrayList* al)
{
    void* new_list = (void**)realloc(al->item_list,sizeof(void*)*(al->my_size));
    if(!new_list)return FALSE;
    al->capacity = al->my_size;
    al->item_list = new_list;
    return TRUE;
}