#define RED 1
#define BLACK 0

typedef struct rbtree{
	int T; //time
	int p; //priority
	int id;
	int color; // 0 for black, 1 for red
	struct rbtree *left;
	struct rbtree *right;
	struct rbtree *parent;
}rbtree;

rbtree *grandparent(rbtree *n)
{
 if ((n != NULL) && (n->parent != NULL))
  return n->parent->parent;
 else
  return NULL;
}

rbtree *uncle(rbtree *n)
{
 struct node *g = grandparent(n);
 if (g == NULL)
  return NULL; // No grandparent means no uncle
 if (n->parent == g->left)
  return g->right;
 else
  return g->left;
}

struct node *sibling(rbtree *n)
{
 if ((n == NULL) || (n->parent == NULL))
  return NULL; // no parent means no sibling
 if (n == n->parent->left)
  return n->parent->right;
 else
  return n->parent->left;
}

rbtree *nil(rbtree *node)
{
	rbtree *emp;
	emp=(rbtree*)malloc(sizeof(rbtree));
	emp->left=NULL;
	emp->right=NULL;
	emp->parent=node;
	emp->color=BLACK;
	emp->p=-1; //leaf node
	return emp;
}

rbtree *create(int l, int u, int pr, int id, int tim)
{
	rbtree *node;
	node=(rbtree*)malloc(sizeof(rbtree));
	node->color=BLACK;
	node->p=pr;
	node->id=id;
	node->T=tim;
	node->left=NULL;
	node->right=NULL:
	node->parent=NULL;
	return node;

}

void insert1();
void insert2();
void insert3();
void insert4();
void insert5();
void insert6();

void bst_insert(rbtree* root, rbtree *node)
{
	if (root==NULL)
	{
		root=node;
		root->parent=NULL;
	}


	else
	{
		if(root->T < tim)
		{
			if(root->left==NULL)
			{
				root->left=node;
				node->parent=root;
				insert1(node);
				return;
			}
			else
				bst_insert(root->left, node);
		}
		if(root->T >= tim)
		{
			if(root->right==NULL)
			{
				root->right=node;
				node->parent=root;
				insert1(node);
				return;
			}
			else
				bst_insert(root->right, node);
		}

	}


}


void insert1(rbtree *n)
{
	if (n->parent == NULL)
  		n->color = BLACK;
 	else
  	insert2(n);
}

void insert2(rbtree *n)
{
 if (n->parent->color == BLACK)
  	return; /* Tree is still valid */
 else
  	insert3(n);
}

void insert3(rbtree *n)
{
 	rbtree *u = uncle(n), *g;

 	if ((u != NULL) && (u->color == RED)) {
	  n->parent->color = BLACK;
	  u->color = BLACK;
	  g = grandparent(n);
	  g->color = RED;
	  insert1(g);
	 } else {
	  insert4(n);
	 }
}



