#include <string.h>
#define  SUCCESS 32
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Book
{
  char *title;
  char *author;
  int  year;  

}BookType;

typedef struct Node
{
  BookType*    data;
  struct Node* next;
  struct Node* prev;
}NodeType;

typedef struct List
{
  NodeType* head;
  NodeType* tail;
  int       size;
  bool      byTitle;
}ListType;

int  initBook(BookType **book);
void initList(ListType *list);
void addByTitle(ListType *list, BookType *newBook);
void addByYear(ListType *list, BookType *newBook);
void copyList(ListType *src, ListType *dest);
void copyByYear(ListType *src, ListType *dest);
void delAuthor(ListType *list, char *name);
void printList(ListType *list);
void cleanupList(ListType *list);
void cleanupData(ListType* list);

int main()
{
  //the author's name user want to delete
  char *authorDel = calloc(10,sizeof(char));

  //initialize the book pointer and 3 list
  BookType *book;
  ListType booksByTitle,booksByYear, tmpList;
  initList(&booksByTitle);
  initList(&booksByYear);
  initList(&tmpList);

  //ask user to enter book name until "end" appears
  while(initBook(&book) == SUCCESS)
  {
    //books are added to the list title
    addByTitle(&booksByTitle,book);
  }

  //print out the original list
  printList(&booksByTitle);

  /*copy the list and ask for author
   * want to delete, then print out
   * the original and the deleted list*/
  copyList(&booksByTitle, &tmpList);
  printf("Enter the author you want to delete: ");
  scanf("%s", authorDel);
  delAuthor(&tmpList, authorDel);
  printList(&booksByTitle);
  printList(&tmpList);

  //copy the list by year decrising order and print out both
  copyByYear(&booksByTitle, &booksByYear);
  printList(&booksByTitle);
  printList(&booksByYear);

  //clean up all allocated items
  cleanupData(&booksByTitle);
  cleanupData(&booksByYear);
  cleanupData(&tmpList);
  cleanupList(&tmpList);
  cleanupList(&booksByTitle);
  cleanupList(&booksByYear);
  free(authorDel);

  return 0;
}

/* Fuction:   initBook
 * Purpose:   allocate and initialize an BookType pointer
 * Parameter: **book: the BookType pointer to be initilized
 * Return:    int
 to show if an book is allocated and initialized successfully
 */
int initBook(BookType **book)
{
  char *tmpTitle  = calloc(40,sizeof(char)),
       *tmpAuthor = calloc(30,sizeof(char));
  int  tmpYear;
  printf("Please enter the book title:\n");
  scanf("%s",tmpTitle);
  if(strcmp(tmpTitle,"end") == 0)
  { 
    free(tmpTitle);
    free(tmpAuthor);
    return -1;
  }
  else
  {
    printf("\nEnter Author:\n");
    scanf("%s",tmpAuthor);
    printf("\nEnter Year\n");
    scanf("%i",&tmpYear);
    *book = calloc(1,sizeof(BookType));
    (*book)->title  = tmpTitle;
    (*book)->author = tmpAuthor;
    (*book)->year   = tmpYear;
    return SUCCESS;    
  }
}

/* Fuction:   initList
 * Purpose:   allocate and initialize an BookType pointer
 * Parameter: **book: the BookType pointer to be initilized
 * Return:    int
 to show if an book is allocated and initialized successfully
 */
void initList(ListType *list)
{
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

/* Fuction:   addByTitle
 * Purpose:   add BookType pointers to the list by thier years increasing order
 * Parameter: *newBook: the BookType pointer to be added
 *            *list:    the list to add books in
 */
void addByTitle(ListType *list, BookType *newBook)
{
  NodeType *tmpNode  = calloc(1,sizeof(NodeType)),
           *prevNode = NULL,
           *currNode = list->head;
  int count = 0;

  tmpNode->data = newBook;
  tmpNode->next = NULL;
  tmpNode->prev = NULL;
  list->byTitle = true;

  if(list->size == 0)
  {
    list->head = tmpNode;
  }
  else
  {
    while(currNode != NULL)
    {
      if(strcmp(newBook->title,currNode->data->title) < 0)
        break;
      prevNode = currNode;
      currNode = currNode->next;
      ++count;
    }
    if(count == 0)
      list->head = tmpNode;
    tmpNode->next = currNode;
    tmpNode->prev = prevNode;
    if(prevNode != NULL)
      prevNode->next = tmpNode;
    if(currNode != NULL)
      currNode->prev = tmpNode;
  }
  if(count == list->size)
    list->tail = tmpNode;
  ++(list->size);
}

/* Fuction:   addByYear
 * Purpose:   add BookType pointers to the list by thier years
 * Parameter: *newBook: the BookType pointer to be added
 *            *list:    the list to add books in
 */
void addByYear(ListType *list, BookType *newBook)
{
  NodeType *tmpNode  = calloc(1,sizeof(NodeType)),
           *prevNode = NULL,
           *currNode = list->head;
  int count = 0;

  tmpNode->data = newBook;
  tmpNode->next = NULL;
  tmpNode->prev = NULL;
  list->byTitle = false;

  if(list->size == 0)
  {
    list->head = tmpNode;
  }
  else
  {
    while(currNode != NULL)
    {
      if(newBook->year > currNode->data->year)
        break;
      prevNode = currNode;
      currNode = currNode->next;
      ++count;
    }
    if(count == 0)
      list->head = tmpNode;
    tmpNode->next = currNode;
    tmpNode->prev = prevNode;
    if(prevNode != NULL)
      prevNode->next = tmpNode;
    if(currNode != NULL)
      currNode->prev = tmpNode;
  }
  if(count == list->size)
    list->tail = tmpNode;
  ++(list->size);
}

/* Fuction:   copyList
 * Purpose:   copy a List into another List by increasing alphabet order
 * Parameter: *src: the ListType to be copyed
 *            *dest:    the new List copyed form src
 */
void copyList(ListType *src, ListType *dest)
{
  NodeType *currNode;
  currNode      = src->head;

  while(currNode != NULL)
  {
    BookType *newBook = calloc(1, sizeof(BookType));
    newBook->title    = calloc(40,sizeof(char));
    newBook->author   = calloc(30,sizeof(char));
    strcpy(newBook->title, currNode->data->title);
    strcpy(newBook->author, currNode->data->author);
    newBook->year = currNode->data->year;
    addByTitle(dest, newBook);
    currNode = currNode->next;
  }
}

/* Fuction:   copyList
 * Purpose:   copy a List into another List by increasing order of years
 * Parameter: *src: the ListType to be copyed
 *            *dest:    the new List copyed form src
 */
void copyByYear(ListType *src, ListType *dest)
{
  NodeType *currNode;
  currNode      = src->head;

  while(currNode != NULL)
  {
    BookType *newBook = calloc(1, sizeof(BookType));
    newBook->title    = calloc(40,sizeof(char));
    newBook->author   = calloc(30,sizeof(char));
    strcpy(newBook->title, currNode->data->title);
    strcpy(newBook->author, currNode->data->author);
    newBook->year = currNode->data->year;
    addByYear(dest, newBook);
    currNode = currNode->next;
  }
}

/* Fuction:   delAuthor
 * Purpose:   delete a books in the list by author's name
 * Parameter: *list: the ListType to delete books from
 *            *name: the name of author to be deleted
 */
void delAuthor(ListType *list, char *name)
{
  printf("%s", name);
  NodeType *tmpNode = list->head, *nextNode = NULL;
  while(tmpNode != NULL)
  {
    if(strcmp(tmpNode->data->author, name) == 0)
    {
      free(tmpNode->data->title);
      free(tmpNode->data->author);
      free(tmpNode->data);
      if(tmpNode->prev != NULL)
      {
        if(tmpNode->next != NULL)
        {
          tmpNode->prev->next = tmpNode->next;
          tmpNode->next->prev = tmpNode->prev;
          nextNode = tmpNode->next;
        }
        else
        {
          tmpNode->prev->next = NULL;
          list->tail = tmpNode->prev;
        } 
      }
      else
      {
        list->head = tmpNode->next;
        list->head->prev = NULL;
        nextNode = tmpNode->next;
      }
      free(tmpNode);
      tmpNode = nextNode;
    }
    else
      tmpNode = tmpNode->next;
  }
}

/* Fuction:   printList
 * Purpose:   print a list out
 * Parameter: *list: the list to be printed
 */
void printList(ListType *list)
{
  NodeType *tmpNode = list->head;

  printf("\n");
  if(list->byTitle)
    printf("*** BOOK LIST BY TITLE ***\n");
  else
    printf("*** BOOK LIST BY Year ***\n");
  printf("BOOK LIST:\n");
  while(tmpNode != NULL)
  {
    printf("--%30s by %15s, Yr: %i\n",
        tmpNode->data->title,
        tmpNode->data->author,
        tmpNode->data->year);
    tmpNode = tmpNode->next;
  }
  printf("\n");
}

/* Fuction:   cleanuptList
 * Purpose:   cleanup the nodes in a list 
 * Parameter: *list: the list to be cleaned up
 */
void cleanupList(ListType *list)
{
  NodeType *tmpNode  = list->head,
           *nextNode = NULL;

  while(tmpNode != NULL)
  {
    nextNode = tmpNode->next;
    free(tmpNode);
    tmpNode = nextNode;
  }
}


/* Fuction:   cleanupData
 * Purpose:   cleanup the data in a list 
 * Parameter: *list: the list to be cleaned up
 */
void cleanupData(ListType* list)
{
  NodeType *tmpNode  = list->head,
           *nextNode = NULL;

  while(tmpNode != NULL)
  {
    free(tmpNode->data->title);
    free(tmpNode->data->author);
    free(tmpNode->data);
    nextNode = tmpNode->next;
    tmpNode = nextNode;
  }
}


