#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

int main(void)
{
    ArrayList al;
    init_ArrayList(&al);
    printf("%d %d\n",al.my_size,al.capacity);
    int aa[20];
    void *aap[20];
    for(int i=0;i<20;i++)
    {
        aa[i]=i;
        // printf("%d %d\n",aa[i],(aa+i));
        al.add_index(&al,2,(aa+i));
        aap[i]=aa+i;
    }
    printf("%d %d\n",al.my_size,al.capacity);
    for(int i=0;i<al.size(&al);i++)
        printf("%d\t",*((int*)al.item_list[i]));
    
    al.retainAll(&al,aap+3,11);
    al.trimToSize(&al);
    
    printf("\n%d %d\n",al.my_size,al.capacity);
    for(int i=0;i<al.size(&al);i++)
        printf("%d\t",*((int*)al.item_list[i]));
    
    ArrayList* sub = al.subArrayList(&al,1,1000);
    int set=233;
    sub->set(sub,1,&set);
    printf("\n%d %d\n",sub->my_size,sub->capacity);
    for(int i=0;i<sub->size(sub);i++)
        printf("%d\t",*((int*)sub->item_list[i]));
}