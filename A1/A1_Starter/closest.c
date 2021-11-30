/************************************************************************
 *                       CSCB63 Winter 2021
 *                  Assignment 1 - AVL Trees
 *                  (c) Mustafa Quraish, Jan. 2021
 *
 * This is the file which should be completed and submitted by you
 * for the assignment. Make sure you have read all the comments
 * and understood what exactly you are supposed to do before you
 * begin. A few test cases are provided in `testClosest.c`, which
 * can be run on the command line as follows:
 *
 *  $> gcc testClosest.c -o testClosest
 *  $> ./testClosest [optional testname]  (or .\testClosest.exe if on Windows)
 *
 * I strongly advise that you write more test cases yourself to see
 * if you have expected behaviour, especially on the edge cases for
 * insert(). You are free to make any reasonable design choices for
 * the implementation of the data structure as long as (1) the outputs
 * are consistent with the expected results, and (2) you meet the
 * complexity requirement. Your closestPair() function will only
 * be tested with cases where there are unique solutions.
 *
 * Mark Breakdown (out of 10):
 *  - 0 marks if the code does not pass at least 1 test case.
 *  - If the code passes at least one test case, then:
 *    - Up to 6 marks for successfully passing all the test cases
 *    - Up to 4 marks for meeting the complexity requirements for 
 *        the functions as described in the comments below.
 *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * This defines the struct(ure) used to define the nodes
 * for the AVL tree we are going to use for this
 * assignment. You need to add some more fields here to be
 * able to complete the functions in order to meet the
 * complexity requirements
 */
typedef struct avl_node {
  // Stores the value (key) of this node
  int value;

  // Pointers to the children
  struct avl_node *left;
  struct avl_node *right;

  // TODO: Add the other fields you need here to complete the assignment!
  //      (Hint: You need at least 1 more field to keep balance)
  int height;

  struct avl_node *minimiumValue;
  struct avl_node *maximumValue;
  struct avl_node *a;
  struct avl_node *b;




} AVLNode;;

/**
 * This function allocates memory for a new node, and initializes it. 
 * The allocation is already completed for you, in case you haven't used C 
 * before. For future assignments this will be up to you!
 * 
 * TODO: Initialize the new fields you have added
 */
AVLNode *newNode(int value) {

  AVLNode *node = calloc(sizeof(AVLNode), 1);
  if (node == NULL) {  // In case there's an error
    return NULL;
  }

  node->value = value;
  node->left = NULL;
  node->right = NULL;

  // Initialize values of the new fields here...
  node->height = 1;

  node->minimiumValue = node;
  node->maximumValue = node;
  node->a = NULL;
  node->b = NULL;

  return node;
}

int avl_height(AVLNode *root){
  if (root == NULL){
    return 0;
  }    
  else {
    return root->height;
  }
}

AVLNode *setab(AVLNode *root){

  int leftDifference1 = 999999;
  int leftDifference2 = 999999;
  int rightDifference1 = 999999;
  int rightDifference2 = 999999;
  

  if (root->left == NULL && root->right == NULL) { //If the the node has no children nodes, then we set min and max values to the node itself and a and b values to NULL
    root->a = NULL;
    root->b=NULL;
    root->minimiumValue = root;
    root->maximumValue = root;
    return root;
  }

  //printf("root value is %d \n", root->value);


  if (root->left == NULL){
    root->minimiumValue = root;
    //printf("root value in 1st if statement is %d \n", root->value);
  }
  else{
    root->minimiumValue = root->left->minimiumValue;
    //printf("it ran");
  }
  if (root->right == NULL){
    root->maximumValue = root;
  }
  else {
    root->maximumValue = root->right->maximumValue;
    //printf("suss root value here is %d \n", root->value);
  }
  
  //int term1 = root->value - root->left->maximumValue->value;
  //int term2 = root->left->b->value - root->left->a->value;

  if (root->left != NULL) {
    leftDifference1 = root->value - root->left->maximumValue->value;

    if (root->left->left != NULL || root->left->right != NULL) {
      leftDifference2 = root->left->b->value - root->left->a->value;
      //printf("term 1 is %d, \n", term1);
      //printf("left difference 2 is %d, \n", leftDifference2);
    }
  }
  
  //int term3 = root->right->minimiumValue->value - root->value;
  //int term4 = root->right->b->value - root->right->a->value;



  if (root->right != NULL) {
    //printf("it ran \n");
    //printf("root right is  %d \n", root->right->value);
    rightDifference1 = root->right->minimiumValue->value - root->value;

    if (root->right->left != NULL || root->right->right != NULL) {
      //printf("root right minimum value is %d \n", root->right->minimiumValue->value);
      rightDifference2 = root->right->b->value - root->right->a->value;
    }
  }
  
  //printf("right difference is %d \n", rightDifference1);

  if (leftDifference1 < leftDifference2) {
    if (leftDifference1 < rightDifference1 && leftDifference1 < rightDifference2) {
      root->a = root->left->maximumValue;
      root->b = root;
    } else {
      if (rightDifference1 < rightDifference2) {
        root->a = root;
        root->b = root->right->minimiumValue;
      }
      else { //basically, rightDifference2 is the smallest value out of all differences
        root->a = root->right->a;
        root->b = root->right->b;
      }
    }
  }
  else { //leftDifference2 is smaller than leftDifference1 which means that term 2 is smaller than term 1 (look at if else statement on line 124)
    if (leftDifference2 < rightDifference1 && leftDifference2 <rightDifference2){
      root->a = root->left->maximumValue;
      root->b = root;
    }
    else {
      if (rightDifference1 < rightDifference2){
        root->a = root;
        root->b = root->right->minimiumValue;
      }
      else { //basically, rightDifference2 is smallest out of all difference values
        root->a = root->right->a;
        root->b = root->right->b;
      }
    }
  }
  return root;
} 

AVLNode *leftRotate(AVLNode *root){
  AVLNode *node1 = root->right;
  AVLNode *node2 = node1->left;

  node1->left = root;
  root->right = node2;

  int node1LeftHeight = avl_height(node1->left);
  int node1RightHeight = avl_height(node1->right);
  int rootLeftHeight = avl_height(root->left);
  int rootRightHeight = avl_height(root->right);

  if (node1RightHeight > node1LeftHeight){
    node1->height = node1RightHeight + 1;
  }
  else {
    node1->height = node1LeftHeight + 1;
  }
  if (rootRightHeight > rootLeftHeight) {
    root->height = rootRightHeight + 1;
  }
  else {
    root->height = rootLeftHeight + 1;
  }

  root = setab(root);
  node1 = setab(node1);

  return node1;
}

AVLNode *rightRotate(AVLNode *root){
  AVLNode *node1 = root->left;
  AVLNode *node2 = node1->right;

  node1->right = root;
  root->left = node2;

  int node1LeftHeight = avl_height(node1->left);
  int node1RightHeight = avl_height(node1->right);
  int rootLeftHeight = avl_height(root->left);
  int rootRightHeight = avl_height(root->right);
  
  if (node1RightHeight > node1LeftHeight){
    node1->height = node1RightHeight + 1;
  }
  else {
    node1->height = node1LeftHeight + 1;
  }
  if (rootRightHeight > rootLeftHeight) {
    root->height = rootRightHeight + 1;
  }
  else {
    root->height = rootLeftHeight + 1;
  }

  root = setab(root);
  node1 = setab(node1);

  return node1;
}
/**
 * This function is supposed to insert a new node with the give value into the 
 * tree rooted at `root` (a valid AVL tree, or NULL)
 *
 *  NOTE: `value` is a positive integer in the range 1 - 1,000,000 (inclusive)
 *       The upper bound here only exists to potentially help make the 
 *                implementation of edge cases easier.
 *
 *  TODO:
 *  - Make a node with the value and insert it into the tree
 *  - Make sure the tree is balanced (AVL property is satisfied)
 *  - Return the *head* of the new tree (A balance might change this!)
 *  - Make sure the function runs in O(log(n)) time (n = number of nodes)
 * 
 * If the value is already in the tree, do nothing and just return the root. 
 * You do not need to print an error message.
 *
 * ----
 * 
 * An example call to this function is given below. Note how the
 * caller is responsible for updating the root of the tree:
 *
 *  AVLNod *root = (... some tree is initialized ...);
 *  root = insert(root, 5); // Update the root!
 */
AVLNode *insert(AVLNode *root, int value) {
  if (root == NULL){
    return newNode(value);
  }

  if (root->value > value){
    root->left = insert(root->left, value);
  }
  else if (root->value < value){
    //printf("right child of root before update is %d", root->right->value);
    root->right = insert(root->right, value);
    //printf("root after update is %d \n", root->value);
  }
  else {
    return root;
  }

  int height_nodeleft = avl_height(root->left);
  int height_noderight = avl_height(root->right);

  if (height_noderight > height_nodeleft){
    root->height = height_noderight + 1;
  }
  else {
    root->height = height_nodeleft + 1;
  }

  root = setab(root);
  
  int balance = height_nodeleft - height_noderight;

  if (balance > 1) {
    if (root->left->value > value){
      root = rightRotate(root);
    }
    else if (root->left->value < value) {
      root->left = leftRotate(root->left);
      root = rightRotate(root);
    }
  }
  if (balance < -1) {
    if (root->right->value < value){
      root = leftRotate(root);
    }
    else {
      root->right = rightRotate(root->right);
      root = leftRotate(root);
    }
  }
  return root;  // Placeholder statement... replace this.
}

/**
 * This function returns the closest pair of points in the tree rooted
 * at `root`. You can assume there are at least 2 values already in the
 * tree. Since you cannot return multiple values in C, for this function
 * we will be using pointers to return the pair. In particular, you need
 * to set the values for the two closest points in the locations pointed
 * to by `a` and `b`. For example, if the closest pair of points is
 * `10` and `11`, your code should have something like this:
 *
 *   (*a) = 10 // This sets the value at the address `a` to 10
 *   (*b) = 11 // This sets the value at the address `b` to 11
 *
 * NOTE: Make sure `(*a)` stores the smaller of the two values, and
 *                 `(*b)` stores the greater of the two values.
 * 
 * NOTE: The test cases will have a unique solution, don't worry about 
 *        multiple closest pairs here.
 *
 *
 * TODO: Complete this function to return the correct closest pair.
 *       Your function should not be any slower than O(log(n)), but if 
 *       you are smart about it you can do it in constant time.
 */
void closestPair(AVLNode *root, int *a, int *b) {
  

  (*a) = root->a->value;  // Placeholder values for the closest pair,
  (*b) = root->b->value;  // replace these with the actual ones.
  return;
}

/******************************************************************************
 * QUERY() and DELETE() are not part for this assignment, but I recommend you
 * try to implement them on your own time to make sure you understand how AVL
 * trees work.
 *
 *                              End of Assignment 1
 *****************************************************************************/
