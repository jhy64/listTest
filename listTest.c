#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listTest.h"

/* test */

static int maxNodes = 20;
static int variance = 10;

typedef enum { false, true } bool;

typedef struct node {
    struct node * next;
    int value;
} Node;

int array2d[100][100];

/* same as */
/*
struct node {
    struct node * next;
    int value;
} node;
typedef struct node Node;
*/

/* Utilities */

static Node * newNode( void ) {
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    node->next = 0;
    node->value = rand() % variance;
}

static Node * newList( int num ){
    Node * list = 0;
    Node * cur = 0;
    Node * head = 0;
    int val = 0;
    int i;

    if( num == 0 ) {
        return 0;
    }
    cur = newNode();
    cur->next = 0;
    head = cur;
    list = cur;
    for( i = 1; i < num; i++ ) {
        cur = newNode();
        list->next = cur;
        list = cur;
        
    }   
    return head;
}

static Node * newSortedList( int num ){
    Node * list = 0;
    Node * cur = 0;
    Node * head = 0;
    int val = 0;
    int i;

    if( num == 0 ) {
        return 0;
    }
    cur = newNode();
    head = cur;
    list = cur;

    for( i = 1; i < num; i++ ) {
        cur = newNode();
        cur->value = list->value + (rand() % variance);
        list->next = cur;
        list = cur;
        
    }   
    return head;
}

static void showList( Node *a ) {
    while( a ) {
        printf( "%d ", a->value );
        a = a->next;
    }
    printf("\n");
}

static void cleanList( Node *a ) {
    Node * b;
    while( a ) {
        b = a;
        a = a->next;
        free( b );
    }
}

/* Core Funcs */

Node * mergeList( Node *a, Node *b ) {
    Node *c;
    Node *head;

    if( !a ) return b;
    if( !b ) return a;
    if( a->value > b->value ) {
        head = b;
        b = b->next;
    } else {
        head = a;
        a = a->next;
    }

    c = head;
    
    while( a && b ) {
        if( a->value > b->value ) {
            c->next = b;
            b = b->next;
        } else {
            c->next = a;
            a = a->next;
        }
        c = c->next;
    }

    c->next = a ? a : b;
    return head;
}

Node * mergeList2( Node *a, Node *b ) {
    Node *c, *tail, *temp;
    Node *head;
    if( !a ) return b;
    if( !b ) return a;
    if( a->value > b->value ) {
        head = b;
        c = b;
        tail = a;
    } else {
        head = a;
        c = a;
        tail = b;
    }
    while( !c->next ) {
        if( c->next->value > tail->value ) {
            temp = c->next;
            c->next = tail;
            tail = tail->next;
            c = c->next;
            c->next = temp;
        }
    }
    if( tail ) {
        c->next = tail;
    }
}            

Node * reverseList( Node *a ) {
    Node *prev, *cur, *next;

    if( !a ) return a;
    if( !a->next ) return a;
    
    prev = 0;
    cur = a;
    next = cur->next;
    
    while( cur->next ) {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    cur->next = prev;
    return cur;

}

Node * nthToTheLast( Node *list, int n ) {
    Node *nth = list;
    int i;

    if( !list ) return 0;
    for( i = 0; i < n; i++ ) {
        if( !list->next ) {
            return 0;
        }
        list = list->next;
    }
    while( list->next ) {
        nth = nth->next;
        list = list->next;
    }
    return nth;
}

Node * bubbleSort( Node *list ) {

    Node dummy;
    Node *prev, *cur, *next;
    bool swapped = true;

    if( !list ) return list;

    dummy.next = list;
    dummy.value = 0;

    while( swapped ) {
        swapped = false;
        prev = &dummy;
        cur = dummy.next;
        next = cur->next;
        while( next ) {
            showList( &dummy );
            if( next->value < cur->value ) {
                prev->next = next;
                cur->next = next->next;
                next->next = cur;
                swapped = true;
            }
            prev = prev->next;
            cur = cur->next;
            next = next->next;
        }
    }
    return dummy.next;
}

Node * insertNode( Node *list, Node *node ) {
    Node *head = list;
    if( !node ) {
        return list;
    }
    node->next = 0;
    if( !list ) {
        return node;
    }
    if( node->value < list->value ) {
        node->next = list;
        list = node;
        return list;
    }
    while( list->next ) {
        if(  node->value < list->next->value ) {
            node->next = list->next;
            list->next = node;
            return head;
        }
        list = list->next;
    }
    list->next = node;
    return head;
}
Node * insertionSort( Node *list ){
    Node *sList = 0;
    Node *node;
    while( list ) {
        node = list;
        list = list->next;
        sList = insertNode( sList, node );
        showList( sList );
    }
    return sList;
}

/* Recursive Implementations */
Node * rNthNode( Node *list, int *count ) {
    Node *rlist;
    if( !list->next ) {
        return list;
    } else {
        rlist = rNthNode( list->next, count );
        if( *count ) {
            *count = *count -1;
            return list;
        } else {
            return rlist;
        }
    }

}


Node * nthNode( Node *list, int n ) {
    int count = n;
    
    return rNthNode( list, &count );
}


Node * rNthNode2( Node *list, int *count ) {
    Node *rList;
    if( !list->next ) {
        return list;
    } else {
        //printf("count = %d node.value=[%d]\n", *count, list->value);
        rList = rNthNode( list->next, count );
        if( *count ) {
            *count = *count - 1;
            return list;
        } else {
            return rList;
        }
    }
}
Node * nthToTheLast2( Node *list, int n ) {
    Node *node = 0;
    // recurse to the last node
    // than pop same node once count matches.
    int count = n;
    node = rNthNode( list, &count ); 
    return node;
}

Node * recurseList( Node *cur, Node *prev ){
    Node *head;
    if( !cur->next ) {
        cur->next = prev;
        return cur;
    } else {
        head = recurseList( cur->next, cur );
        cur->next = prev;
    }
    return head;
}

Node * reverseList2( Node *a ) {
    Node *head;
    if( !a ) {
        return a;
    }
    if( !a->next ) {
        return a;
    }
    head = recurseList( a->next, a );
    a->next = 0;
    return head;
}

Node *reverList3( Node *head ) {
    Node *cur, *prev, *next;

    cur = head;
    prev = 0;
    if( !cur ) return 0;
    next = cur->next;
    while( !cur->next ) {
        cur->next = prev;
        prev = cur; 
        cur = next;
        next = next->next;
    }
    cur->next = prev;
    return cur;
}


Node *recReverseList( Node* cur, Node *prev ) {
    Node *head;
    if( !cur->next ) {
        cur->next = prev;
        return cur;
    } else {
        head = recReverseList( cur->next, cur );
        cur->next = prev;
    }
    return head;
}



Node *reverseList4( Node *a ) {
    Node *head;
    if( !a ) return 0;
    if( !a->next ) return a;
    
    head = recReverseList( a, 0 );
    a->next = 0;
    return head;
}


int present( Node *a, int value ) {
    while( a ) {
        if( a->value == value ) {
            return 1;
        }
        a = a->next;
    }
    return 0;
}


Node *delDup( Node *a ) {

    Node *start, *head, *temp;

    if( !a ) return 0;
    if( !a->next ) return a;

    start = (Node *)malloc( sizeof(Node) );
    start->next = a;
    start->value = 0;
    head = start;

    while( start->next ) {
        if( present( start->next->next, start->next->value ) ) {
            temp = start->next;
            start->next = start->next->next;
            free( temp );           
        } else {
            start = start->next;
        }
        //printf("While:\n");
        //showList( head );
    }
    temp = head->next;
    free( head );
    return temp;
}



/* Test Funcs */

void listMergeTest() {
    Node *list1, *list2, *list3;
    printf("\n[List Merge Test]\n");
    list1 = newSortedList( rand() % maxNodes );
    list2 = newSortedList( rand() % maxNodes );
    printf("Before:\n");
    showList( list1 );
    showList( list2 );
    list3 = mergeList( list1, list2 );
    printf("After:\n");
    showList( list3 );
    cleanList( list3 );
}

void listReverseTest() {
    printf("\n[List Reverse Test]\n");
    Node *list1 = newList( rand() % (maxNodes) );
    printf("Before:\n");
    showList( list1 );
    Node *list3 = reverseList4( list1 );
    printf("After:\n");
    showList( list3 );
    cleanList( list3 );
}
void listReverse2Test() {
    printf("\n[List Reverse2 Test]\n");
    Node *list1 = newList( rand() % (maxNodes*2) );
    printf("Before:\n");
    showList( list1 );
    Node *list3 = reverseList2( list1 );
    printf("After:\n");
    showList( list3 );
    cleanList( list3 );
}

void listSortTest() {
    Node *list1, *list2;
    printf("\n[List Sort Test]\n");
    list1 = newList( maxNodes );
    printf("Before:\n");
    showList( list1 );
    list2 = insertionSort( list1 );
    printf("After InsertionSort:\n");
    showList( list2 );
    cleanList( list2 );

    list1 = newList( maxNodes );
    printf("Before:\n");
    showList( list1 );
    list2 = bubbleSort( list1 );
    printf("After BubbleSort:\n");
    showList( list2 );    
    cleanList( list2 );

}

void listNthElementTest() {
    int i;
    Node *list1, *node;
    printf("\n[List nth to the last element test.]\n");
    list1 = newList( maxNodes );
    showList( list1 );
    for( i = 0; i < 3; i++ ) {
        node = nthToTheLast( list1, i );
        printf("[%dth to the last] = %d\n",i , node->value);
    }
}
    
void listNthElement2Test() {
    int i;
    Node *list1, *node;
    printf("\n[List nth to the last element test2.]\n");
    list1 = newList( maxNodes );
    showList( list1 );
    for( i = 0; i < maxNodes; i++ ) {
        node = nthToTheLast2( list1, i );
        printf("[%dth to the last] = %d\n",i , node->value);
    }
}

void listDelDupTest() {
    Node *list1;
    printf("\n[List Del Dup Test]\n");
    list1 = newList( maxNodes );
    printf("Before:\n");
    showList( list1 );
    list1 = delDup( list1 );
    printf("After Del Dup:\n");
    showList( list1 );
}

void arrayTest() {
    array2d[0][0] = 100;
}

void listTestAll() {
   time_t t;

   //int a = 5;
   //int b = 6;

   /* Intializes random number generator */
   srand((unsigned) time(&t));
   listMergeTest();
   //listReverseTest();
   listNthElementTest();
   //listSortTest();
   listDelDupTest();
}

