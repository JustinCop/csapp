/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  (queue_t*)malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
    {
        return NULL;
    }
    q->head = NULL;
    q->num = 0;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q == NULL)
    {
        return;
    }
    while(q->head != NULL)
    {
        q_remove_head(q, NULL, 0);
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL)
    {
        return false;
    }

    newh = (list_ele_t*)malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
    {
        return false;
    }
    int length = strlen(s) + 1;
    newh->value = (char*)malloc(length);
    if (newh->value == NULL)
    {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->next = q->head;
    q->head = newh;

    // if this is first inserted, record it as tail as well.
    if (q->num == 0)
    {
        q->tail = newh;
    }
    // increase queue num by 1
    q->num++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
    {
        return false;
    }
    list_ele_t *newt;
    newt = (list_ele_t*)malloc(sizeof(list_ele_t));
    if (newt == NULL)
    {
        return false;
    }
    int length = strlen(s) + 1;
    newt->value = (char*)malloc(length);
    if (newt->value == NULL)
    {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);

    newt->next = NULL;

    if(q->head == NULL)
    {
        q->head = newt;
    }
    if(q->tail != NULL)
    {
        q->tail->next = newt;
    }
    q->tail = newt;
    q->num++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->num == 0)   // q->head == NULL
    {
        return false;
    }

    list_ele_t *pHead = q->head;
    // copy to sp
    if(sp != NULL)
    {
        strncpy(sp, pHead->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    // update
    q->head = pHead->next;
    pHead->next = NULL;
    q->num--;
    if (q->num == 0)
    {
        q->tail = NULL;
    }
    // free memory
    free(pHead->value);
    free(pHead);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
    {
        return 0;
    }
    return q->num;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    list_ele_t *p1, *p2, *p3;
    if (q == NULL || q->num == 0) // q->head == NULL
    {
        return;
    }
    p1 = q->head;
    // if only 1 element
    if (p1->next == NULL)
    {
        return;
    }
    p2 = p1->next;
    q->tail = p1;
    while(p2->next != NULL)
    {
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }
    p2->next = p1;
    q->head->next = NULL;
    q->head = p2;
}

