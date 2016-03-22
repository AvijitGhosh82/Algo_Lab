#define RED 1
#define BLACK 0

#include <stdio.h>
#include <stdlib.h>

int GT=0; // Global Time
int current=0; //current number of processes


typedef struct rbtree{
	int T; //time
	int p; //priority
	int id;
    int CT;//Create time
    int ET;//End time
	int color; // 0 for black, 1 for red
	struct rbtree *left;
	struct rbtree *right;
	struct rbtree *parent;
}rbtree;


int max(int a, int b)
{
	if(a>b) 
		return a;
	else
		return b;
}

rbtree *grandparent(rbtree *n)
{
 if ((n != NULL) && (n->parent != NULL))
  return n->parent->parent;
 else
  return NULL;
}


rbtree *parentOf(rbtree *n) {
        return n == NULL ? NULL : n->parent;
    }

rbtree *leftOf(rbtree *n) {
        return n == NULL ? NULL : n->left;
    }

rbtree *rightOf(rbtree *n) {
        return n == NULL ? NULL : n->right;
    }


void setcolor(rbtree *n, int c) {
        if (n != NULL)
            n->color = c;
    }

int colorOf(rbtree *n) {
        return (n == NULL)? BLACK : n->color;
    }


int isRed(rbtree *n) {
        return n != NULL && colorOf(n) == RED;
    }

int isBlack(rbtree *n) {
        return n == NULL || colorOf(n) == BLACK;
    }

rbtree *minValue(rbtree* node) {
  rbtree* current = node;
  
    while (current->left != NULL) {
    current = current->left;
  }
  return current;
}


rbtree *findsuccessor(rbtree *root, rbtree *n)
{
  if( n->right != NULL )
    return minValue(n->right);
 
  rbtree *p = n->parent;
  while(p != NULL && n == p->right)
  {
     n = p;
     p = p->parent;
  }
  return p;
}


rbtree *findpredecessor(rbtree *node) {
        rbtree *n = node->left;
        if (n != NULL) {
            while (n->right != NULL) {
                n = n->right;
            }
        }
        return n;
    }

rbtree *sibling(rbtree *n)
{
 if ((n == NULL) || (n->parent == NULL))
  return NULL; // no parent means no sibling
 if (n == n->parent->left)
  return n->parent->right;
 else
  return n->parent->left;
}

rbtree *create(int tim, int pr, int id, int CT, int ET)
{
    rbtree *node=(rbtree *)malloc(sizeof(rbtree));
    node->color=BLACK;
    node->p=pr;
    node->T=tim;
    node->id=id;
    node->CT=CT;
    node->ET=ET;
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;
    return node;
}

rbtree* search(rbtree* root, int key)
{
    if (root == NULL || root->T == key)
       return root;
    
    if (root->T < key)
       return search(root->right, key);
 
    return search(root->left, key);
}

int height(rbtree *t) {
    if (t == NULL)
        return 0;
    else
        return max(height(t->left), height(t->right)) + 1;
}

void pretty(rbtree* root)
{
    if (root == NULL)
        return;
    pretty(root->left);
    int h=height(root);
    int i;
    for(i=1;i<h;i++)
    	printf("\t");
    if(root->color==RED)
    	printf("[%d, R] \n", root->T);
    else
    	printf("[%d, B] \n", root->T);
    pretty(root->right);
}

void left_rotate(rbtree *root, rbtree *x)
{
	rbtree *y=x->right;
	if (y==NULL)
		return;
	x->right=y->left;
	if(y->left != NULL)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		root=y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else x->parent->right=y;
	y->left=x;
	x->parent=y;
}

void right_rotate(rbtree *root, rbtree *x)
{
	rbtree *y=x->left;
	if (y==NULL)
		return;
	x->left=y->right;
	if(y->right != NULL)
		y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		root=y;
	else if(x==x->parent->right)
		x->parent->right=y;
	else x->parent->left=y;
	y->right=x;
	x->parent=y;
}


    void adjustAfterInsertion(rbtree *root, rbtree *n) {
        // New node is RED
        n->color=RED;

        // Correcting double red problems, if they exist
        if (n != NULL && n != root && isRed(n->parent)) {

            // Case A. Recolor, and move up to see if more work
            // needed
            if (isRed(sibling(n->parent))) {
                setcolor(n->parent,BLACK);
                setcolor(sibling(n->parent),BLACK);
                setcolor(grandparent(n),RED);
                adjustAfterInsertion(root, grandparent(n));
            }

            // Case B: Restructure for a parent who is the left child of the
            // grandparent. This will require a single right rotation if n is
            // also
            // a left child, or a left-right rotation otherwise.
            else if (n->parent == (grandparent(n))->left) {
                if (n == n->parent->right) {
                	n=n->parent;
                    left_rotate(root, n);
                }
                setcolor(n->parent,BLACK);
                setcolor(grandparent(n),RED);
                right_rotate(root, grandparent(n));
            }

            // Case C: Restructure for a parent who is the right child of the
            // grandparent. This will require a single left rotation if n is
            // also
            // a right child, or a right-left rotation otherwise.
            else if (n->parent == (grandparent(n))->right) {
                if (n == n->parent->left) {
                	n=n->parent;
                    right_rotate(root, n);
                }
                setcolor(n->parent,BLACK);
                setcolor(grandparent(n),RED);
                left_rotate(root, grandparent(n));
            }
        }

        // At last: Color the root black
        root->color=BLACK;
    }


void insert(rbtree **root, rbtree *z) {
        current+=1;
        if (*root == NULL) {
            *root = z;
        }
        rbtree *n = *root;
        while (1) {
            int comparisonResult = n->T-z->T;
            if (comparisonResult == 0) {
                return;
            } else if (comparisonResult < 0) {
                if (leftOf(n) == NULL) {
                    n->left=z;
                    adjustAfterInsertion(*root, z);
                    break;
                }
                n = leftOf(n);
            } else { // comparisonResult > 0
                if (rightOf(n) == NULL) {
                    n->right=z;
                    adjustAfterInsertion(*root,z);
                    break;
                }
                n = rightOf(n);
            }
        }
    }


void adjustAfterRemoval(rbtree *root, rbtree *n) {
        while (n != root && isBlack(n)) {
            if (n == n->parent->left) {
                // Pulled up node is a left child
                rbtree *sib;
                sib = sibling(n);
                if(sib==NULL)
                	return;


                if (isRed(sib)) {
                    setcolor(sib, BLACK);
                    setcolor(n->parent, RED);
                    left_rotate(root, n->parent);
                    sib = n->parent->right;
                }
                if (isBlack(sib->left) && isBlack(sib->right)) {
                    setcolor(sib, RED);
                    n = n->parent;
                } else {
                    if (isBlack(sib->right)) {
                        setcolor(sib->left, BLACK);
                        setcolor(sib, RED);
                        right_rotate(root, sib);
                        sib = n->parent->right;
                    }
                    setcolor(sib, n->parent->color);
                    setcolor(n->parent, BLACK);
                    setcolor(sib->right, BLACK);
                    left_rotate(root,n->parent);
                    n = root;
                }
            } else {
                // pulled up node is a right child
                rbtree *sib = sibling(n);
                if(sib==NULL)
                	return;

                if (isRed(sib)) {
                    setcolor(sib, BLACK);
                    setcolor(n->parent, RED);
                    right_rotate(root, n->parent);
                    sib = n->parent->left;
                }
                if (isBlack(sib->left) && isBlack(sib->right)) {
                    setcolor(sib, RED);
                    n = n->parent;
                } else {
                    if (isBlack(sib->left)) {
                        setcolor(sib->right, BLACK);
                        setcolor(sib, RED);
                        left_rotate(root,sib);
                        sib = n->parent->left;
                    }
                    setcolor(sib, n->parent->color);
                    setcolor(n->parent, BLACK);
                    setcolor(sib->left, BLACK);
                    right_rotate(root, n->parent);
                    n = root;
                }
            }
        }
        setcolor(n, BLACK);
    }

void removeFromParent(rbtree *n) {
        if (n->parent != NULL) {
            if (n->parent->left == n) {
                n->parent->left = NULL;
            } else if (n->parent->right == n) {
                n->parent->right = NULL;
            }
            n->parent = NULL;
        }
    }


void delete(rbtree *root, rbtree *node) {
        current-=1;
        if (node == NULL) {
            // No such object, do nothing.
            return;
        } else if (node->left != NULL && node->right != NULL) {
            // Node has two children, Copy predecessor data in.
            rbtree *predecessor = findpredecessor(node);
            node->T=predecessor->T;
            node->p=predecessor->p;
            node->CT=predecessor->CT;
            node->ET=predecessor->ET;
            node->id=predecessor->id;
            node = predecessor;
        }
        // At this point node has zero or one child
        rbtree *pullUp = (node->left == NULL) ? node->right : node->left;
        if (pullUp != NULL) {
            // Splice out node, and adjust if pullUp is a double black.
            if (node == root) {
                root=pullUp;
            } else if (node->parent->left == node) {
                node->parent->left=pullUp;
            } else {
                node->parent->right=pullUp;
            }
            if (isBlack(node)) {
                adjustAfterRemoval(root, pullUp);
            }
        } else if (node == root) {
            // Nothing to pull up when deleting a root means we emptied the tree
            root=NULL;
        } else {
            // The node being deleted acts as a double black sentinel
            if (isBlack(node)) {
                adjustAfterRemoval(root, node);
            }
            removeFromParent(node);
        }
    }



// void transplant(rbtree *root, rbtree *u, rbtree *v)
// {
// 	if(u->parent==NULL)
// 		root=v;
// 	else if(u==u->parent->left)
// 		u->parent->left=v;
// 	else
// 		u->parent->right=v;
// 	v->parent=u->parent;
// }


void newproc(rbtree **root, int tim, int prio, int c)
{
    // printf("%d\n",tim );
    rbtree *node=create(tim,prio,c,GT,-1);
    insert(root, node);
    pretty(*root);
    printf("\n\n\n\n\n\n");

}

void scheduler(rbtree *root)
{
    FILE *f;
    f = fopen("output.txt", "a");
    rbtree *min=minValue(root); //least execution time
    int s=min->T;
    if(s<0)
        {
            delete(root, min);
            min=NULL;
            return;
        }
    
    printf("Mintime %d\n", min->T);
    if(min!=root)
    printf("Post delete\n");
    pretty(root);
    
    min->T = min->T - ((min->p)*50);
    int PT=GT;
    GT+=((min->p)*50);//Update Clock
    if((min->T)>0)
        insert(&root, min);
    else
        min->ET=GT;
    fprintf(f,"%d\t%7d\t%7d\t%7d\t%7d\t%7d\n", min->id,min->CT,min->p,PT,GT,min->ET);

    //process ended

    if(min->ET>0)
    {
        delete(root, min);
        min=NULL;
        return;
    }

    // if(min->T<0)
    //     printf("Gone\n");
    fclose(f);
}


void testin(rbtree **root, int T)
{
    printf("Insert %d\n", T);
	rbtree *node=create(T,0,0,GT,-1);
	insert(root, node);
	pretty(*root);
	printf("\n\n\n\n\n\n");

}

void testout(rbtree *root, int T)
{
	rbtree *node=search(root, T);
	printf("Delete %d\n", T);
	delete(root, node);
	pretty(root);
	printf("\n\n\n\n\n\n");

}

int main()
{
	rbtree *root=NULL;
	// testin(&root, 2);
	// testin(&root, 1);
	// testin(&root, 4);
	// testin(&root, 5);
	// testin(&root, 9);
	// testin(&root, 3);
	// testin(&root, 6);
	// testin(&root, 7);

	// testout(root,5);
	// testout(root,3);
	// testout(root,7);


      int M,N;
    printf("Enter the value of M (number of nodes)\n");
    scanf("%d", &M);
    printf("Enter the value of N (number of processes in tree at a time)\n");
    scanf("%d", &N);

    FILE *f;

    f = fopen("output.txt", "w");
    fprintf(f, "PID\tCREATED\tPRIORITY\tONLOAD\tOFFLOAD\tEND\n");
    fclose(f);


    int flag[1000]={0};
    int val;
    int max=1000, min=1;

    int i,j;
    int c=1;

    int tim, prio;

    while(c<=M)//outer loop
    {
        //creating process
        // if(count(root)<=N)
        // {
        if(current<N && c<=M)
        {   while(1)
            {
                val = (rand() % (max+1-min))+min;
                if (flag[val-1]==0)
                {
                    flag[val-1]=1;
                    break;
                }

            }
            tim=val;
            // printf("%d\n", tim);

            prio=(rand() % (4))+1;
            newproc(&root,tim,prio,c);
            c=c+1;
            printf("INSERT \n\n");
            // pretty(root);

         // }
        }

        printf("SCHEDULER \n\n");
        scheduler(root);
         // pretty(root);


   }

   while(current>=-1)
   {
    printf("SCHEDULER \n\n");
    scheduler(root);
   }

	return 0;




}





 