
#include <stdio.h>
#include <string.h>

typedef struct binTree binTree;

struct binTree 
{
  binTree * lchild, * rchild, *parent;
  int data;
};

binTree *make_empty(binTree *t)
{
  if (t != NULL)
  {
    make_empty(t->lchild);
    make_empty(t->rchild);
    free(t);
  }

  return NULL;
}

binTree *find_min(binTree *t)
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (t->lchild == NULL)
  {
    return t;
  }
  else
  {
    return find_min(t->lchild);
  }
}

binTree *find_max(binTree *t)
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (t->rchild == NULL)
  {
    return t;
  }
  else
  {
    return find_max(t->rchild);
  }
}

binTree *find(int elem, binTree *t)
{
  if (t == NULL)
  {
    return NULL;
  }

  if (elem < t->data)
  {
    return find(elem, t->lchild);
  }
  else if (elem > t->data)
  {
    return find(elem, t->rchild);
  }
  else
  {
    return t;
  }
}

//Insert i into the tree t, duplicate will be discarded
//Return a pointer to the resulting tree.                 
binTree * insert(int value, binTree * t) 
{
  binTree * new_node;
    
  if (t == NULL) 
  {
    new_node = (binTree *) malloc (sizeof (binTree));
    if (new_node == NULL) 
    {
      return t;
    }

    new_node->data = value;

    new_node->lchild = new_node->rchild = NULL;
    return new_node;
  }
  
  if (value < t->data) 
  {
    t->lchild = insert(value, t->lchild);
  } 
  else if (value > t->data) 
  {
    t->rchild = insert(value, t->rchild);
  } 
  else 
  { 
    //duplicate, ignore it
    return t;
  }
  return t;
}

binTree * delete(int value, binTree * t) 
{
  //Deletes node from the tree
  // Return a pointer to the resulting tree
  binTree * x;
  binTree *tmp_cell;
  
  if (t==NULL) return NULL;
  
  if (value < t->data) 
  {
    t->lchild = delete(value, t->lchild);
  } 
  else if (value > t->data) 
  {
    t->rchild = delete(value, t->rchild);
  } 
  else if (t->lchild && t->rchild)
  {
    tmp_cell = find_min(t->rchild);
    t->data = tmp_cell->data;
    t->rchild = delete(t->data, t->rchild);
  }
  else
  { 
    tmp_cell = t;
    if (t->lchild == NULL)
      t = t->rchild;
    else if (t->rchild == NULL)
      t = t->lchild;
    free(tmp_cell);
  }

  return t;
}


//printing tree in ascii

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
  asciinode * lchild, * rchild;

  //length of the edge from this node to its children
  int edge_length; 
    
  int height;      

  int lablen;

  //-1=I am lchild, 0=I am root, 1=rchild   
  int parent_dir;   
                         
  //max supported unit32 in dec, 10 digits max
  char label[11];  
};


#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between lchild and rchild nodes
int gap = 3;  

//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;    

int MIN (int X, int Y)  
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)  
{
  return ((X) > (Y)) ? (X) : (Y);
}

asciinode * build_ascii_tree_recursive(binTree * t) 
{
  asciinode * node;
  
  if (t == NULL) return NULL;

  node = malloc(sizeof(asciinode));
  node->lchild = build_ascii_tree_recursive(t->lchild);
  node->rchild = build_ascii_tree_recursive(t->rchild);
  
  if (node->lchild != NULL) 
  {
    node->lchild->parent_dir = -1;
  }

  if (node->rchild != NULL) 
  {
    node->rchild->parent_dir = 1;
  }

  sprintf(node->label, "%d", t->data);
  node->lablen = strlen(node->label);

  return node;
}


//Copy the tree into the ascii node structre
asciinode * build_ascii_tree(binTree * t) 
{
  asciinode *node;
  if (t == NULL) return NULL;
  node = build_ascii_tree_recursive(t);
  node->parent_dir = 0;
  return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node) 
{
  if (node == NULL) return;
  free_ascii_tree(node->lchild);
  free_ascii_tree(node->rchild);
  free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y) 
{
  int i, islchild;
  if (node == NULL) return;
  islchild = (node->parent_dir == -1);
  lprofile[y] = MIN(lprofile[y], x-((node->lablen-islchild)/2));
  if (node->lchild != NULL) 
  {
    for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
    {
      lprofile[y+i] = MIN(lprofile[y+i], x-i);
    }
  }
  compute_lprofile(node->lchild, x-node->edge_length-1, y+node->edge_length+1);
  compute_lprofile(node->rchild, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y) 
{
  int i, notlchild;
  if (node == NULL) return;
  notlchild = (node->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notlchild)/2));
  if (node->rchild != NULL) 
  {
    for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
    {
      rprofile[y+i] = MAX(rprofile[y+i], x+i);
    }
  }
  compute_rprofile(node->lchild, x-node->edge_length-1, y+node->edge_length+1);
  compute_rprofile(node->rchild, x+node->edge_length+1, y+node->edge_length+1);
}

//This function fills in the edge_length and 
//height fields of the specified tree
void compute_edge_lengths(asciinode *node) 
{
  int h, hmin, i, delta;
  if (node == NULL) return;
  compute_edge_lengths(node->lchild);
  compute_edge_lengths(node->rchild);

  /* first fill in the edge_length of node */
  if (node->rchild == NULL && node->lchild == NULL) 
  {
    node->edge_length = 0;
  } 
  else 
  {
    if (node->lchild != NULL) 
    {
      for (i=0; i<node->lchild->height && i < MAX_HEIGHT; i++) 
      {
        rprofile[i] = -INFINITY;
      }
      compute_rprofile(node->lchild, 0, 0);
      hmin = node->lchild->height;
    } 
    else 
    {
      hmin = 0;
    }
    if (node->rchild != NULL) 
    {
      for (i=0; i<node->rchild->height && i < MAX_HEIGHT; i++) 
      {
        lprofile[i] = INFINITY;
      }
      compute_lprofile(node->rchild, 0, 0);
      hmin = MIN(node->rchild->height, hmin);
    } 
    else 
    {
      hmin = 0;
    }
    delta = 4;
    for (i=0; i<hmin; i++) 
    {
      delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
    }
    
    //If the node has two children of height 1, then we allow the
    //two leaves to be within 1, instead of 2 
    if (((node->lchild != NULL && node->lchild->height == 1) ||
        (node->rchild != NULL && node->rchild->height == 1))&&delta>4) 
    {
      delta--;
    }
      
    node->edge_length = ((delta+1)/2) - 1;
  }

  //now fill in the height of node
  h = 1;
  if (node->lchild != NULL) 
  {
    h = MAX(node->lchild->height + node->edge_length + 1, h);
  }
  if (node->rchild != NULL) 
  {
    h = MAX(node->rchild->height + node->edge_length + 1, h);
  }
  node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level) 
{
  int i, islchild;
  if (node == NULL) return;
  islchild = (node->parent_dir == -1);
  if (level == 0) 
  {
    for (i=0; i<(x-print_next-((node->lablen-islchild)/2)); i++) 
    {
      printf(" ");
    }
    print_next += i;
    printf("%s", node->label);
    print_next += node->lablen;
  } 
  else if (node->edge_length >= level) 
  {
    if (node->lchild != NULL) 
    {
      for (i=0; i<(x-print_next-(level)); i++) 
      {
        printf(" ");
      }
      print_next += i;
      printf("/");
      print_next++;
    }
    if (node->rchild != NULL) 
    {
      for (i=0; i<(x-print_next+(level)); i++) 
      {
        printf(" ");
      }
      print_next += i;
      printf("\\");
      print_next++;
    }
  } 
  else 
  {
    print_level(node->lchild, 
                x-node->edge_length-1, 
                level-node->edge_length-1);
    print_level(node->rchild, 
                x+node->edge_length+1, 
                level-node->edge_length-1);
  }
}

//prints ascii tree for given binTree structure
void print_ascii_tree(binTree * t) 
{
  asciinode *proot;
  int xmin, i;
  if (t == NULL) return;
  proot = build_ascii_tree(t);
  compute_edge_lengths(proot);
  for (i=0; i<proot->height && i < MAX_HEIGHT; i++) 
  {
    lprofile[i] = INFINITY;
  }
  compute_lprofile(proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) 
  {
    xmin = MIN(xmin, lprofile[i]);
  }
  for (i = 0; i < proot->height; i++) 
  {
    print_next = 0;
    print_level(proot, -xmin, i);
    printf("\n");
  }
  if (proot->height >= MAX_HEIGHT) 
  {
    printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
  }
  free_ascii_tree(proot); 
}


//driver routine
// void main() 
// {
//   //A sample use of these functions.  Start with the empty tree
//   //insert some stuff into it, and then delete it
//   binTree * root;
//   int i;
//   root = NULL;    
  
//   make_empty(root);

//   printf("\nAfter inserting data 10..\n");
//   root = insert(10, root);
//   print_ascii_tree(root);

//   printf("\nAfter inserting data 5..\n");
//   root = insert(5, root);
//   print_ascii_tree(root);

//   printf("\nAfter inserting data 15..\n");
//   root = insert(15, root);
//   print_ascii_tree(root);

//   printf("\nAfter inserting datas 9, 13..\n");
//   root = insert(9, root);
//   root = insert(13, root);
//   print_ascii_tree(root);

//   printf("\nAfter inserting datas 2, 6, 12, 14, ..\n");
//   root = insert(2, root);
//   root = insert(6, root);
//   root = insert(12, root);
//   root = insert(14, root);
//   print_ascii_tree(root);

  
//   printf("\n\nAfter deleting a node (14) with no child..\n");
//   root = delete(14, root);
//   print_ascii_tree(root);

//   printf("\n\nAfter deleting a node (13) with lchild child..\n");
//   root = delete(13, root);
//   print_ascii_tree(root);

//   printf("\n\nAfter deleting a node (5) with lchild and rchild children..\n");
//   root = delete(5, root);
//   print_ascii_tree(root);

//     printf("\n\nAfter deleting a node (10, root node) with lchild and rchild children..\n");
//   root = delete(10, root);
//   print_ascii_tree(root);

//   make_empty(root);
// }