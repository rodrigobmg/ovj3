/*
 * @(#)reda_inlineList_impl.h    generated by: makeheader    Mon Dec  3 23:07:54 2007
 *
 *		built from:	inlineList_impl.ifc
 */

#ifndef reda_inlineList_impl_h
#define reda_inlineList_impl_h



  #ifndef reda_dll_h
    #include "reda/reda_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif



struct REDAInlineListNode {
    /*i back pointer to the head of the list. */
    struct REDAInlineList *inlineList;
    /*i next in this list. */
    struct REDAInlineListNode *next;
    /*i prev in this list. */
    struct REDAInlineListNode *prev;
};

struct REDAInlineList {
    /*i Head. */
    struct REDAInlineListNode _dummyNode;
    /*i Tail. */
    struct REDAInlineListNode *_tail;
    /*i Current number of nodes.  Do not modify externally. */
    int _size;
};

  #define REDA_INLINE_LIST_EMPTY {{NULL, NULL, NULL}, 0}

  #define REDAInlineList_getFirstMacro(l) (l)->_dummyNode.next

  #define REDAInlineList_getLastMacro(l) (l)->_tail

  #define REDAInlineList_isNodeInListMacro(l, node) ((l)==(node)->inlineList)

  #define REDAInlineListNode_initMacro(node) \
    (node)->next = NULL, \
    (node)->prev = NULL, \
    (node)->inlineList = NULL

  #define REDAInlineList_initMacro(l) \
    REDAInlineListNode_init(&((l)->_dummyNode)), \
    (l)->_tail = NULL, \
    (l)->_size = 0

  #define REDAInlineList_addNodeToFrontMacro(l, node) \
  { \
    (node)->inlineList = (l); \
    (node)->next = (l)->_dummyNode.next; \
    (node)->prev = &((l)->_dummyNode); \
    if ((node)->next != NULL) { (node)->next->prev = (node); } \
    else { (l)->_tail = (node); } \
    (l)->_dummyNode.next = (node); \
    ++((l)->_size); \
  }

  #define  REDAInlineList_addNodeAfterMacro(l, existingNode, node) \
  { \
    (node)->inlineList = (existingNode)->inlineList; \
    (node)->next = (existingNode)->next; \
    (node)->prev = existingNode; \
    if ((node)->next != NULL) { (node)->next->prev = (node); } \
    else { (l)->_tail = (node); } \
    (existingNode)->next = (node); \
    ++((l)->_size); \
  }

  #define REDAInlineList_addNodeToBackMacro(l, node) \
  { \
    if ((l)->_tail == NULL) { \
        REDAInlineList_addNodeToFrontMacro(l, node); \
    } else { \
        (node)->inlineList = (l); \
        (l)->_tail->next = (node); \
        (node)->prev = (l)->_tail; \
        (node)->next = NULL; \
        (l)->_tail = (node); \
        ++((l)->_size); \
    } \
  }

  #define REDAInlineList_removeNodeMacro(l, node) \
  { \
      if ((l)->_tail == (node)) { \
          (l)->_tail = (node)->prev; \
      } \
      if ((l)->_tail == &((l)->_dummyNode)) { \
        (l)->_tail = NULL; \
      } \
      if ((node)->prev != NULL) { \
          (node)->prev->next = (node)->next; \
      } \
      if ((node)->next != NULL) { \
	  (node)->next->prev = (node)->prev; \
      } \
      --((node)->inlineList->_size); \
      REDAInlineListNode_init((node)); \
  }

  #define REDAInlineList_getSize(l) (l)->_size

  #ifdef RTI_PRECONDITION_TEST
    REDADllExport struct REDAInlineListNode *
    REDAInlineList_getFirst(const struct REDAInlineList *l);

    REDADllExport struct REDAInlineListNode *
    REDAInlineList_getLast(const struct REDAInlineList *l);

    REDADllExport RTIBool REDAInlineList_isNodeInList(
	struct REDAInlineList *l, struct REDAInlineListNode *node);

    REDADllExport void
    REDAInlineListNode_init(struct REDAInlineListNode *node);

    REDADllExport void REDAInlineList_init(struct REDAInlineList *l);

    REDADllExport void REDAInlineList_addNodeToFrontEA(
	struct REDAInlineList *l, struct REDAInlineListNode *node);

    REDADllExport void REDAInlineList_addNodeAfterEA(
        struct REDAInlineList *l, struct REDAInlineListNode *existingNode,
	struct REDAInlineListNode *node);

    REDADllExport void REDAInlineList_addNodeToBackEA(
	struct REDAInlineList *l, struct REDAInlineListNode *node);

    REDADllExport void REDAInlineList_removeNodeEA(
	struct REDAInlineList *l, struct REDAInlineListNode *node);
  #else
    #define REDAInlineList_getFirst         REDAInlineList_getFirstMacro
    #define REDAInlineList_getLast          REDAInlineList_getLastMacro
    #define REDAInlineList_isNodeInList     REDAInlineList_isNodeInListMacro
    #define REDAInlineListNode_init         REDAInlineListNode_initMacro
    #define REDAInlineList_init             REDAInlineList_initMacro
    #define REDAInlineList_addNodeToFrontEA REDAInlineList_addNodeToFrontMacro
    #define REDAInlineList_addNodeAfterEA   REDAInlineList_addNodeAfterMacro
    #define REDAInlineList_addNodeToBackEA  REDAInlineList_addNodeToBackMacro
    #define REDAInlineList_removeNodeEA     REDAInlineList_removeNodeMacro
  #endif /* RTI_PRECONDITION_TEST */



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* reda_inlineList_impl_h */