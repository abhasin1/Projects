#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include "avl-dictionary.h"

// Constructor
AVLDictionary::AVLDictionary()
{
	root = NULL;
}

// Add a record to the dictionary. Returns false if key already exists
bool AVLDictionary::addRecord( KeyType key, DataType record)
{
	//Find node to insert to
	AVLNode *current = root;
	AVLNode *previous = NULL;

	while(current != NULL)
	{
		previous = current;
		
		if(!strcmp(key, current->key))
		{
			//printf("key already exists, do nothing");
			current->data = record;
			return false;
		}		
		
		else if(strcmp(key, current->key) < 0)
		{
			previous = current;
			current = current->left;
		}
		else if(strcmp(key, current->key) > 0)
		{
			previous = current;
			current = current->right;
		}
	}

	//did not find the key
    AVLNode * n = new AVLNode();
    n->height = 1;
    n->key = (char *)malloc(sizeof(char) * strlen(key));
    memcpy((void *)n->key, (void *)key, strlen(key) + 1); // copy buffer
    n->data = record;
    n->left = NULL;
    n->right = NULL;
    n->parent = previous;

    if(previous == NULL)
    {
		//tree is empty, insert at root
		root = n;
    }
    else
    {
		//tree is not empty, link parent to child
		if(strcmp(key, previous->key) < 0)
		{
			//insert in left
			previous->left = n;
		}
		else
		{
			previous->right = n;
		}
    }

	//Adjust height, starting at parent of inserted node
    AVLNode * temp = n->parent;

    while(temp != NULL)
    {
		//Get maximum height of left and right children
		int maxheight = 0;

		if(temp->left != NULL)
		{
			maxheight = temp->left->height;
		}
		if(temp->right != NULL && maxheight < temp->right->height)
		{
			maxheight = temp->right->height;
		}

		temp->height = maxheight + 1;
		temp = temp->parent;
    }

	//restruct if necessary
    //Start at  node , up to the root

//	restructure(n);
    return true;

}

// Find a key in the dictionary and return corresponding record or NULL
DataType AVLDictionary::findRecord( KeyType key )
{
	AVLNode * node = root;
	
	while (node != NULL)
	{
		if (!strcmp(node->key, key))
		{
			return node->data;
		}
		else if(strcmp(key, node->key) < 0 )
		{
			node = node->left;
		}
		else if(strcmp(key, node->key) > 0 )
		{
			node = node->right;
		}
	}
	
	return NULL;

}

void AVLDictionary::restructure(AVLNode *node)
{
	//Rebalance tree starting at n
	//find z = parent of the first unbalance subtree

	AVLNode *z = node->parent;

	while(z != NULL)
	{
		//Find parent of unbalance subtree
		int heightLeft = 0;

		if(z->left != NULL)
		{
			heightLeft = z->left->height;
		}

		int heightRight = 0;

		if(z->right != NULL)
		{
			heightRight = z->right->height;
		}

		//at this point, recompute the height of z in case it was modified

		if(heightLeft > heightRight)
		{
			z->height = heightLeft +1;
		}
		else
		{
			z->height = heightRight + 1;
		}

		//Verify if tree rooted by z is balance
		int heightDifference = heightRight - heightLeft;

		//Obtain the absolute value
		if(heightDifference < 0)
		{
			heightDifference = -heightDifference;
		}

		if(heightDifference <= 1)
		{
			z = z->parent;
			continue;
		}

		//subtree rooted by z in unbalanced
		//Find y: child with largest height

		AVLNode *y = NULL;

		int maxh = 0;

		if(z->left != NULL)
		{
			y = z->left;
			maxh = y->height;
		}
		if(z->right != NULL && maxh < z->right->height)
		{
			y = z->right;
		}

		assert(y!=NULL);

		//Find x: child of y with largest height

		AVLNode *x = NULL;
		maxh = 0;

		if(y->left != NULL)
		{
			x = y->left;
			maxh = x->height;
		}
		if(y->right != NULL && maxh < y->right->height)
		{
			x = y->right;
		}

		assert(x != NULL);

		//have x, y, z.  need to label as a,b,c according to inorder traversal

		AVLNode *a, *b, *c, *t0, *t1, *t2, *t3;

		if(z->right == y)
		{
			//case 1 or 2
			if(y->right == x)
			{
				//case 1
				a = z;
				b = y;
				c = x;
				t0 = a->left;
				t1 = b->left;
				t2 = c->left;
				t3 = c->right;
			}
			else
			{
				//case 2
				a = z;
		        b = x;
		        c = y;
		        t0 = a->left;
		        t1 = b->left;
		        t2 = b->right;
		        t3 = c->right;
			}
		}
		else
		{
			//case 3 or 4
	       if(y->left == x)
			{
				//case 3
				a = x;
				b = y;
				c = z;
				t0 = a->left;
				t1 = a->right;
				t2 = b->right;
				t3 = c->right;
			}
			else
			{
				//case 4
				a = y;
				b = x;
				c = z;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		}

		//Now we have a,b,c.  Do the rotation
		//Connect to parent of z
		AVLNode *p = z->parent;

		if(p != NULL)
		{
			if(p->left == z)
			{
				p->left = b;
			}
			else
			{
				p->right = b;
			}
		}
		else
		{
			//z is root, make root parent to b
			root = b;

			//update b
			b->parent = p;
			b->left = a;
			b->right = c;

			//update a
			a->parent = b;
			a->left = t0;
			a->right = t1;

			//update c
			c->parent = b;
			c->left = t2;
			c->right = t3;

			//connect parents of t0, t1, t2, t3

			if(t0 != NULL)
			{
				t0->parent = a;
			}
			if(t1 != NULL)
			{
				t1->parent = a;
			}
			if(t2 != NULL)
			{
				t2->parent = c;
			}
			if(t3 != NULL)
			{
				t3->parent = c;
			}

			//We need to update the heights of a,b,c


			//update height of a
			int maxHeight = 0;

			if(a->left != NULL)
			{
				maxHeight = a->left->height;
			}
			if(a->right != NULL && a->right->height > maxHeight)
			{
				maxHeight = a->right->height;
			}
			a->height = maxHeight + 1;

			//updating the height of c
			maxHeight = 0;
			if(c->left != NULL)
			{
				maxHeight = c->left->height;
			}
			if(c->right != NULL && c->right->height > maxHeight)
			{
				maxHeight = c->right->height;
			}
			c->height = maxHeight + 1;

			//updating the height of b
			maxHeight = 0;
			if( b->left != NULL )
			{
				maxHeight = b->left->height;
			}
			if( b->right != NULL && b->right->height > maxHeight )
			{
				maxHeight = b->right->height;
			}
			b->height = maxHeight + 1;

			//Have to go one node above..
			z = p;
		}
	} // end of while
} // end of restructure function





bool AVLDictionary::removeElement(KeyType key)
{

        AVLNode *toDelete = root;

        // Find node to delete

        while(toDelete != NULL)

        {

               if(key < toDelete->key)

               {

                       toDelete = toDelete->left;

               }

               else if(key > toDelete->key)

               {

                       toDelete = toDelete->right;

               }

               else

               {

                       break;

               }

        }

        // If not found return false

        if(toDelete == NULL)

        {

               return false;

        }

        // If the node is at the bottom of the tree just delete the node

        if(toDelete->height == 1)

        {

          //check if remove last node

          if (toDelete == root) {

            root = NULL;

            return 1;

          }

 

               if(toDelete->key < toDelete->parent->key)

               {

                       toDelete->parent->left = NULL;

               }

               else if(toDelete->key > toDelete->parent->key)

               {

                       toDelete->parent->right = NULL;

               }

              

               //restructure may still be needed

               restructure(toDelete);

 

               return true;

        }

        // Find node to replace other with

        AVLNode *replacement = NULL, *replacement_parent = NULL;

 

        if (toDelete->left != NULL)

        {

               replacement = toDelete->left;

               while (replacement->right != NULL)

               {

                       replacement = replacement->right;

               }

               // Unlink the replacement from its parent

               if(replacement->parent == toDelete)

               {

                       replacement->parent->left = replacement->left;

               }

               else

               {

                       replacement->parent->right = NULL;

               }

        }

        else if (toDelete->right != NULL)

        {

               replacement = toDelete->right;

               while (replacement->left != NULL)

               {

                       replacement = replacement->left;

               }

               // Unlink the replacement from its parent

               if(replacement->parent == toDelete)

               {

                       replacement->parent->right = replacement->right;

               }

               else

               {

                       replacement->parent->left = NULL;

               }

        }

        // Store the parent for later use

        replacement_parent = replacement->parent;

        // Exchange pointers from node to be deleted with its replacement

        replacement->parent = toDelete->parent;

        replacement->left = toDelete->left;

        replacement->right = toDelete->right;

        replacement->height = toDelete->height;

        if(toDelete->left != NULL)

        {

               toDelete->left->parent = replacement;

        }

        if(toDelete->right != NULL)

        {

               toDelete->right->parent = replacement;

        }

        if(toDelete == root)

        {

               root = replacement;

        }

        else if(toDelete->key < toDelete->parent->key)

        {

               toDelete->parent->left = replacement;

        }

        else if(toDelete->key > toDelete->parent->key)

        {

               toDelete->parent->right = replacement;

        }

        //free(toDelete);

        //Adjust path from replancmentparent->root

        if(replacement_parent == toDelete)

        {

               replacement_parent = replacement;

        }

        if(replacement_parent->left == NULL && replacement_parent->right == NULL)

        {

               replacement_parent->height = 1;

        }

        AVLNode *m = replacement_parent;

        while(m != NULL)

        {

               int maxheight = 0;

               if(m->left != NULL)

               {

                       maxheight = m->left->height;

               }

               if(m->right != NULL && m->right->height > maxheight)

               {

                       maxheight = m->right->height;

               }

               m->height = maxheight + 1;

               m = m->parent;

        }

        //Reconstruct tree

        restructure(replacement_parent);

        return true;

 

}
// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType* AVLDictionary:: keys(int * n)
{
	
}
