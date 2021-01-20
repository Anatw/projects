/*******************************************************************************
Psaudo code for HeapSort function that can handle increasing/decreasing order
of tree.					  	 
Yehuda remarks - add a recursive heapify after every Seap so the the tree is sorted all the way to the leafs.

                           Written by Anat Wax
						  April 27th, 2020
						Reviewer: Yehuda Levavi
*******************************************************************************/

typedef enum 
{
    DECREASING = -1,
    INCREASING =  1
} order_t;

/* I'm assuming the the heap has already been heapify. */
void HeapSort(int *base, size_t nmemb, order_t order)
{
   index = middle element of the heap (nmemb / 2).
    
   for (index = (nmemb / 2); index >= 0; --index)
   {
        if element in index has children
        {
            successor_element = left child of element.
            if element has a right child
            {
                compare the value of right child and left child.
                if (order = DECREASING)
                {
                    successor_element is equal to the smaller of the two.
                }
                else
                {
                    successor_element is equal to the greater of the two.
                }

                swap successor_element with element (child with parent).
            }
            else
            {
                if (value of index is greater than successor_element)
                {
                    if (order = INCREASING)
                    {
                        break;
                    }
                    else
                    {
                        swap successor_element with element (child with parent).
                    }
                }
                else
                {
                    if (order = INCREASING)
                    {
                        swap successor_element with element (child with parent).
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            break;
        }
   }
}