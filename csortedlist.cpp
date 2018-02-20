// ============================================================================
// File: csortedlist.cpp (Spring 2018)
// ============================================================================
// This is the implementation file for the list ADT "CSortedList".  This
// particular implementation uses an array to store a list of type
// "ListType" items.
// ============================================================================

#include    <iostream>
using namespace std;
#include    "csortedlist.h"



// ==== CSortedList::CSortedList ============================================
//
// This the default constructor.
//
// Input:
//      Nothing.
//
// Output:
//      Nothing.
//
// ============================================================================
CSortedList::CSortedList()
{
    m_currMax = m_numItems = DEFAULT_LISTSIZE;
}



// ==== CSortedList::CSortedList ============================================
//
// This the copy constructor, which performs a deep copy of the parameter.
//
// Input:
//      otherList   -- a reference to an existing CSortedList object
//
// Output:
//      Nothing.
//
// ============================================================================
CSortedList::CSortedList(const CSortedList &other)
{
    int counter;
    counter = m_numItems;
    while(counter > 0)
    {
        m_items[counter] = other.m_items[counter];
        counter --;
    }
}



// ==== CSortedList::CopyList =================================================
//
// This function copies the contents of one CSortedList object to another
// CSortedList object.  If the destination object already contains a list, then
// that list is first released.
//
// Input:
//      otherList   -- a const reference to an existing CSortedList object
//
// Output:
//      The total number of items copied from the source object to the
//      destination object.
//
// ============================================================================
int CSortedList::CopyList(const CSortedList &otherList)
{
    int counter;
    counter = m_numItems;

    while(counter > 0)
    {
        m_items[counter] = otherList.m_items[counter];
        counter --;
    }
    return 0;
}



// ==== CSortedList::DestroyList =============================================
//
// This function destroys a list by releasing any memory allocated for the
// list.
//
// Input:  nothing
//
// Output: nothing
//
// ============================================================================
void CSortedList::Destroy List()
{
    int counter;
    counter = m_numItems;
    while(counter > 0)
    {
        m_numItems[counter] = 0;
        counter --;
    }
    m_numItems = 0;
    m_currMax = 0;
}


// ==== CSortedList::DispRetVal ===============================================
//
// This function is used for debugging purposes.  If a value of type
// ListReturnCode needs to be displayed to stdout, you can call this function.
//
// Input:
//      szMessage   -- a null-terminated string to display to stdout (e.g., the
//                     name of the function calling this function)
//
//      value       -- the list error code to display
//
// Output:
//      nothing
//
// ============================================================================
void CSortedList::DispRetVal(const char* szMessage, LStatus value) const
{
    #ifdef      DEBUG_LIST
    cerr << szMessage << ": ";
    switch(value)
    {
        case L_FULL:
            cerr << "L_FULL\n";
            break;

        case L_EMPTY:
            cerr << "L_EMPTY\n";
            break;

        case L_ERROR:
            cerr << "L_ERROR\n";
            break;

        case L_SUCCESS:
            cerr << "L_SUCCESS\n";
            break;

        case L_INVALID_INDEX:
            cerr << "L_INVALID_INDEX\n";
            break;

        default:
            cerr << "Unrecognized error code\n";
            break;
    }
    #endif //DEBUG_LIST
}


// ==== CSortedList::GetItem ==================================================
//
// This function fetches the value of a target item from the list.
//
// Input:
//      index   -- the index location for the target item (zero-based).
//
//      item    -- a reference to a ListType object; this argument will
//                 contain the desired item after the function completes
//                 (assuming all goes well)
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an error code is
//      returned.
//
// ============================================================================
LStatus CSortedList::GetItem(int index, ListType &item) const
{
    // if the list is empty, return an error code
    if(true == IsEmpty())
    {
        DispRetVal("GetItem", L_EMPTY);
        return L_EMPTY;
    }

    // if the target location is not within appropriate list boundaries
    // (i.e., 0 to m_numItems-1) return an error code
    if ((index < 0) || (index > (m_numItems - 1)))
    {
        DispRetVal("GetItem", L_INVALID_INDEX);
        return L_INVALID_INDEX;
    }

    // initialize the reference parameter and return
    item = m_items[index];
    return L_SUCCESS;

}



// ==== CSortedList::GetIndex =================================================
//
// This function determines the proper index location for the "newItem"
// parameter.  The proper index location is one that will maintain an ascending
// sorted order in the list.  If the "newItem" value is already in the list, a
// value of true is returned to alert the caller, otherwise a value of false is
// returned.
//
// NOTE: this function assumes the caller has already determined that there is
//       enough room in the array to add the new item.
//
// Input:
//
//      newItem     -- a const reference to the new item to insert into the list
//
//      index       -- the target index location for the new item (zero-based)
//
// Output:
//      A value of true if the "newItem" value is already in the list, false if
//      not.
//
// ============================================================================
bool CSortedList::GetIndex(const ListType &newItem, int &index)const
{
    bool bInList = false;
    for(index = 0; index < m_numItems; ++ index)
        {
        if(item == m_items[index])
            {
            bInList = true;
            break;
            }
        else if(item < m_tems[index])
            {
            break;
            }
        }
    return bInList;
}



// ==== CSortedList::Insert ===================================================
//
// This function inserts an item into the list.  If the new item is appended to
// the end of the list, the position of any other list item is unaffected.  If
// the new item is inserted before the last element, all elements after the
// target location are moved towards the back of the array one position to make
// room for the new element.
//
// Input:
//      newItem    -- a const reference to the new item to insert into the list
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================
LStatus CSortedList::Insert(const ListType &item)
{
    // if the list is already full, return an error code
    if(IsFull())
        {
        DispRetVal("Insert", L_FULL);
        return L_FULL;
        }
    int index;
    if(true == GetIndex(item, index))
        {
        DispRetVal("Insert", L_FULL);
        return L_DUPLICATE;
        }
    if(index < m_numItems)
        {
        MoveItems(index, MOVE_TO_BACK);
        }
    m_items[index] = item;
    ++m_numItems;
    return L_SUCCESS;
}



// ==== CSortedList::MoveItems ================================================
//
// This function moves the elements of the list forward or backward one
// position.  If an item is inserted before the last element in the list, the
// "trailing" elements must be moved towards the back of the array one position
// in order to make room for the new list item.  Similarly, if a list item is
// removed from the middle of the list, the trailing elements must be moved
// towards the front of the array one position to fill in the gap left by the
// deleted item.
//
// The caller of this function only needs to indicate the target location where
// an element is being inserted or removed, and the "direction" to move the
// trailing list elements (i.e., towards the front or back of the array).
//
// NOTE: This function assumes that the caller has already verified the
// validity of the index parameter.
//
// Input:
//      index           -- the index location for the target item (zero-based).
//
//      direction       -- the direction to move the trailing (i.e., those
//                         further down the list) list elements; this parameter
//                         should contain the value MOVE_TO_BACK if an item is
//                         being inserted into the list, or MOVE_TO_FRONT if
//                         the item at targetIndex is being removed from the
//                         list.
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an errorcode is
//      returned.
//
// ============================================================================
int CSortedList::MoveItems(int index, int direction)
{
    int destIndex;
    int update;
    int sourceIndex;
    int numItemsMoved = 0;

    // initialize the source and destination index values
    if(MOVE_TO_BACK == direction)
    {
        sourceIndex = m_numItems - 1;
        destIndex = m_numItems;
        update = -1; // move from higher to lower addresses
    }

    else        // MOVE_TO_FRONT
    {
        sourceIndex = index + 1;
        destIndex = index;
        update = 1;
    }

    // loop and "move" elements
    bool        bContinueLoop = true;
    do
    {
        m_items[destIndex] = m_items[sourceIndex];
        destIndex += update;
        sourceIndex += update;
        ++ numItemsMoved;

        if(MOVE_TO_BACK == direction)
        {
            if((sourceIndex < index) || (destIndex < 1))
            {
                bContinueLoop = false;
            }
        }
        else // MOVE_TO_FRONT
        {
            if(sourceIndex >= m_numItems)
            {
                bContinueLoop = false;
            }
        }
    } while(true == bContinueLoop);

    return numItemsMoved;
}



// ==== CSortedList::Remove ===================================================
//
// This function removes an item from the list.  If the target item is at the
// end of the list, the position of any other list item is unaffected.  If the
// target item is before the end of the list, all elements after the target
// location are moved towards the front of the array one position to fill in
// the gap left behind by the deleted item.
//
// Input:
//      target      -- a const reference to the item to remove
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================
LStatus CSortedList::Remove(const ListType &item)
{
    if(IsEmpty())
    {
        DispRetVal("Insert", L_FULL);
        return L_EMPTY;
    }
    int index;
    if(false == GetIndex(item, index))
    {
        DispRetVal("Insert", L_FULL);
        return L_NOT_EXIST;
    }
    if(index < (m_numItems - 1))
    {
        MoveItems(index, MOVE_TO_FRONT);
    }
    -- m_numItems;
    return L_SUCCESS;
}



// ==== CSortedList::SetListSize ==============================================
//
// This function is used to manage the allocated size of a list. The input
// parameter indicates the number of elements to allocate for the list. If the
// calling object already contains a list with data, it can be resized to
// either increase or decrease its allocation. If the size of the existing list
// is being decreased, then the trailing items will be truncated.
//
// Input:
//      numItems  -- the target number of items in the list
//
// Output:
//      Nothing.
//
// ============================================================================
LStatus CSortedList::SetListSize(int numItems)
{
    numItems = m_numItems = m_currMax;
}



// ==== CSortedList::operator= ================================================
//
// This is the overloaded assignment operator, copying the parameter's list to
// the calling object.
//
// Input:
//      otherList         -- a reference to a source CSortedList object
//
// Output:
//      A reference to the calling object.
//
// ============================================================================
CSortedList::operator = (const CSortedList &otherList)
{
    int counter;
    counter = m_numItems;

    while(counter > 0)
    {
        m_items[counter] = otherList.m_items[counter];
    }
}

