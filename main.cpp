// ============================================================================
// File: main.cpp (Spring 2018)
// ============================================================================
// This is a driver program to test the list ADT "CSortedList".  It creates an
// empty list by declaring a local variable of type CSortedList.  Then a loop
// is entered that allows the user to manipulate the list until he/she wishes
// to quit.
// ============================================================================

#include    <iostream>
#include    <cstdlib>
using namespace std;
#include    "csortedlist.h"


// function prototypes;
void    DisplayMenu();
void    DisplayList(const CSortedList  &list);
void    FlushInstream(istream  &inStream = cin);


// ==== main ==================================================================
//
// ============================================================================

int     main()
{
    bool                bLoop = true;
    char                selection;
    CSortedList         myList;
    int                 intVal;

    // let the user manipulate the list
    do  {
        DisplayMenu();
        cout << "Please enter a selection: ";

        cin >> selection;
        switch (toupper(selection))
            {
            // if the list is full, display an error message
            if (myList.IsFull())
                {
                cout << "Sorry, the list is currently full...\n" << endl;
                continue;
                }

            // try to get a valid item from the user
            case   'A':
                cout << "Please enter a value to add to the list: ";
                if (!(cin >> intVal))
                    {
                    cout << "Error reading int, please try again...\n";
                    FlushInstream();
                    }
                else
                    {
                    myList.Insert(intVal);
                    }
                break;

            case   'R':
                // if the list is empty, display an error message
                if (myList.IsEmpty())
                    {
                    cout << "Sorry, the list is currently empty...\n" << endl;
                    continue;
                    }

                cout << "Please enter a value to remove from the list: ";
                if (!(cin >> intVal))
                    {
                    cout << "Error reading int, please try again...\n";
                    FlushInstream();
                    }
                else
                    {
                    myList.Remove(intVal);
                    }
                break;

            case   'D':
                cout << "Here is the current list:\n";
                DisplayList(myList);
                cout << endl;
                break;

            case   'Q':
                intVal = myList.GetNumItems();
                cout << intVal << " item";
                cout << ((intVal != 1) ? "s" : "");
                cout << " released..." << endl;
                bLoop = false;
                break;

            default:
                cout << "Unrecognized selection; please try again...\n";
                FlushInstream();
                break;
            }

        cout << endl;

        } while (true == bLoop);

    return  0;

}  // end of "main"



// ==== DisplayMenu ===========================================================
//
// This function simply displays the list of menu options available to the
// user.
//
// Input:  nothing
// Output: nothing
//
// ============================================================================

void    DisplayMenu()
{
    cout << "A)dd an item\n";
    cout << "R)emove an item\n";
    cout << "D)isplay the list\n";
    cout << "Q)uit\n";

}  // end of "DisplayMenu"



// ==== DisplayList ===========================================================
//
// This function displays the current contents of the list to the standard
// output stream.
//
// Input:
//      list    -- a const reference to a CSortedList object
//
// Output:
//      Nothing.
//
// ============================================================================

void    DisplayList(const CSortedList  &list)
{
    int             index;
    ListType        listItem;

    for (index = 0; index < list.GetNumItems(); ++index)
        {
        list.GetItem(index, listItem);
        cout << listItem << endl;
        }

}  // end of "DisplayList"



// ==== FlushInstream =========================================================
//
// This function flushes the input stream of any remaining content, up to a
// newline character or EOF.
//
// Input:
//      inStream        -- a reference to an istream object
//
// Output:
//      Nothing.
//
// ============================================================================

void    FlushInstream(istream  &inStream)
{
    char        inChar;

    inStream.clear();
    while (false == inStream.eof())
        {
        inStream.get(inChar);
        if ('\n' == inChar)
            {
            break;
            }
        }

}  // end of "FlushInstream"
