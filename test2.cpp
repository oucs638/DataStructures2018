#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX_SIZE 100

// define the struct element
typedef enum { head,
    element } tagfield;
typedef struct Node* nodeptr;
struct NodeElement {
    int row;
    int col;
    int val;
};
struct Node {
    nodeptr down;
    nodeptr right;
    tagfield tag;
    union {
        nodeptr next;
        NodeElement element;
    } u;
};
nodeptr hdnode[MAX_SIZE];

// the function to read and create a sparse matrix with linked list
nodeptr mread(void)
{
    // declare
    nodeptr headNode, temp, last;
    int numRows = 0, numCols = 0, numTerms = 0, numHeads = 0;
    int row = 0, col = 0, val = 0, currentRow = 0;
    // set the number of rows, columns and nonzero terms
    cout << "Please enter number of rows, columns and nonzero terms: " << endl;
    cin >> numRows >> numCols >> numTerms;
    // create the headNode of linked list
    numHeads = (numCols > numRows) ? numCols : numRows;
    headNode = new Node;
    headNode->tag = element;
    headNode->u.element.row = numRows;
    headNode->u.element.col = numCols;
    // create the linked list
    if (!numHeads) {
        // if the sparse matrix is empty
        // just create a head
        headNode->right = headNode;
    } else {
        // initialize all head nodes
        for (int i = 0; i < numHeads; ++i) {
            temp = new Node;
            hdnode[i] = temp;
            hdnode[i]->tag = head;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0]; // the last node of the row
        for (int i = 0; i < numTerms; ++i) {
            cin >> row >> col >> val;
            if (row > currentRow) { // finish the row
                last->right = hdnode[currentRow];
                currentRow = row;
                last = hdnode[row];
            }
            temp = (nodeptr)malloc(sizeof(*temp));
            temp->tag = element;
            temp->u.element.row = row;
            temp->u.element.col = col;
            temp->u.element.val = val;
            last->right = temp; // link row list
            last = temp;
            // link column list
            hdnode[col]->u.next->down = temp;
            hdnode[col]->u.next = temp;
        }
        // let the last node of this row
        // point to the first node of this row
        last->right = hdnode[currentRow];
        // let the last node of every column list in this row
        // point to the first node of same list
        for (int i = 0; i < numCols; ++i) {
            hdnode[i]->u.next->down = hdnode[i];
        }
        // link all head nodes
        for (int i = 0; i < numHeads - 1; ++i) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = headNode;
        headNode->right = hdnode[0];
    }
    return headNode;
}

void mwrite(nodeptr headNode)
{
    // output the sparse matrix mainly row
    nodeptr temp, head = headNode->right;
    cout << "numRows = " << headNode->u.element.row
         << ", numCols = " << headNode->u.element.col << endl
         << "The matrix by row, column and value:" << endl;
    // output
    for (int i = 0; i < headNode->u.element.row; ++i) {
        for (temp = head->right; temp != head; temp = temp->right) {
            cout.setf(ios_base::left, ios_base::adjustfield);
            cout << setw(4) << temp->u.element.row << setw(4)
                 << temp->u.element.col << setw(4) << temp->u.element.val
                 << endl;
        }
        head = head->u.next;
    }
}

nodeptr mtranspose(nodeptr reqHeadNode)
{
    // declare
    nodeptr resHeadNode;
    nodeptr temp, last, reqhead = reqHeadNode->right;
    vector<NodeElement> tempElements;
    // set the number of rows and the number of cols of transpose matrix
    int numRows = reqHeadNode->u.element.col,
        numCols = reqHeadNode->u.element.row;
    int numHeads = (numCols > numRows) ? numCols : numRows;
    int numTerms = 0, currentRow = 0;
    // read the matrix that would be transposed
    for (int i = 0; i < reqHeadNode->u.element.row; ++i) {
        for (temp = reqhead->right; temp != reqhead; temp = temp->right) {
            NodeElement tempElement;
            tempElement.row = temp->u.element.col;
            tempElement.col = temp->u.element.row;
            tempElement.val = temp->u.element.val;
            tempElements.push_back(tempElement);
        }
        reqhead = reqhead->u.next;
    }
    // create the headNode of linked list
    numTerms = tempElements.size();
    resHeadNode = new Node;
    resHeadNode->tag = element;
    resHeadNode->u.element.row = numRows;
    resHeadNode->u.element.col = numCols;
    // sort the elements
    for (int i = 0; i < tempElements.size(); ++i) {
        for (int j = i; j < tempElements.size(); ++j) {
            if (tempElements[i].row > tempElements[j].row) {
                int tmpRow = tempElements[i].row;
                int tmpCol = tempElements[i].col;
                int tmpVal = tempElements[i].val;
                tempElements[i].row = tempElements[j].row;
                tempElements[i].col = tempElements[j].col;
                tempElements[i].val = tempElements[j].val;
                tempElements[j].row = tmpRow;
                tempElements[j].col = tmpCol;
                tempElements[j].val = tmpVal;
            } else if (tempElements[i].row == tempElements[j].row) {
                if (tempElements[i].col > tempElements[j].col) {
                    int tmpCol = tempElements[i].col;
                    int tmpVal = tempElements[i].val;
                    tempElements[i].col = tempElements[j].col;
                    tempElements[i].val = tempElements[j].val;
                    tempElements[j].col = tmpCol;
                    tempElements[j].val = tmpVal;
                }
            }
        }
    }
    // create the linked list
    if (!numHeads) {
        // if the sparse matrix is empty
        // just create a head
        resHeadNode->right = resHeadNode;
    } else {
        // initialize all head nodes
        for (int i = 0; i < numHeads; ++i) {
            temp = new Node;
            hdnode[i] = temp;
            hdnode[i]->tag = head;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0]; // the last node of the row
        for (int i = 0; i < numTerms; ++i) {
            if (tempElements[i].row > currentRow) { // finish the row
                last->right = hdnode[currentRow];
                currentRow = tempElements[i].row;
                last = hdnode[tempElements[i].row];
            }
            temp = (nodeptr)malloc(sizeof(*temp));
            temp->tag = element;
            temp->u.element.row = tempElements[i].row;
            temp->u.element.col = tempElements[i].col;
            temp->u.element.val = tempElements[i].val;
            last->right = temp; // link row list
            last = temp;
            // link column list
            hdnode[tempElements[i].col]->u.next->down = temp;
            hdnode[tempElements[i].col]->u.next = temp;
        }
        // let the last node of this row
        // point to the first node of this row
        last->right = hdnode[currentRow];
        // let the last node of every column list in this row
        // point to the first node of same list
        for (int i = 0; i < numCols; ++i) {
            hdnode[i]->u.next->down = hdnode[i];
        }
        // link all head nodes
        for (int i = 0; i < numHeads - 1; ++i) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = resHeadNode;
        resHeadNode->right = hdnode[0];
    }

    return resHeadNode;
}

nodeptr mmult(nodeptr req1, nodeptr req2)
{
    if (req1->u.element.col != req2->u.element.row) {
        return NULL;
    }
    // cout << "reqT2:" << endl;
    // mwrite(req2T);
    nodeptr resHeadNode, tmp1, tmp2, last, temp;
    nodeptr req1head = req1->right, req2head = req2->right;
    vector<NodeElement> tempElements, tmpReq1, tmpReq2;
    int tmpsum[req1->u.element.row][req2->u.element.col];
    for (int i = 0; i < req1->u.element.row; ++i) {
        for (int j = 0; j < req2->u.element.col; ++j) {
            tmpsum[i][j] = 0;
        }
    }
    for (int i = 0; i < req1->u.element.row; ++i) {
        for (temp = req1head->right; temp != req1head; temp = temp->right) {
            NodeElement tempElement;
            tempElement.row = temp->u.element.row;
            tempElement.col = temp->u.element.col;
            tempElement.val = temp->u.element.val;
            tmpReq1.push_back(tempElement);
        }
        req1head = req1head->u.next;
    }
    for (int i = 0; i < req2->u.element.row; ++i) {
        for (temp = req2head->right; temp != req2head; temp = temp->right) {
            NodeElement tempElement;
            tempElement.row = temp->u.element.row;
            tempElement.col = temp->u.element.col;
            tempElement.val = temp->u.element.val;
            tmpReq2.push_back(tempElement);
        }
        req2head = req2head->u.next;
    }
    for (int i = 0; i < tmpReq1.size(); ++i) {
        for (int j = 0; j < tmpReq2.size(); ++j) {
            if (tmpReq1[i].col == tmpReq2[j].row) {
                tmpsum[tmpReq1[i].row][tmpReq2[j].col] += tmpReq1[i].val * tmpReq2[j].val;
            }
        }
    }
    for (int i = 0; i < req1->u.element.row; ++i) {
        for (int j = 0; j < req2->u.element.col; ++j) {
            if (tmpsum[i][j] != 0) {
                NodeElement tempElement;
                tempElement.row = i;
                tempElement.col = j;
                tempElement.val = tmpsum[i][j];
                tempElements.push_back(tempElement);
            }
        }
    }
    int numRows = req1->u.element.row,
        numCols = req2->u.element.col;
    int numHeads = (numRows > numCols) ? numRows : numCols;
    int numTerms = 0, currentRow = 0;
    // create the headNode of linked list
    numTerms = tempElements.size();
    resHeadNode = new Node;
    resHeadNode->tag = element;
    resHeadNode->u.element.row = numRows;
    resHeadNode->u.element.col = numCols;
    // sort the elements
    for (int i = 0; i < tempElements.size(); ++i) {
        for (int j = i; j < tempElements.size(); ++j) {
            if (tempElements[i].row > tempElements[j].row) {
                int tmpRow = tempElements[i].row;
                int tmpCol = tempElements[i].col;
                int tmpVal = tempElements[i].val;
                tempElements[i].row = tempElements[j].row;
                tempElements[i].col = tempElements[j].col;
                tempElements[i].val = tempElements[j].val;
                tempElements[j].row = tmpRow;
                tempElements[j].col = tmpCol;
                tempElements[j].val = tmpVal;
            } else if (tempElements[i].row == tempElements[j].row) {
                if (tempElements[i].col > tempElements[j].col) {
                    int tmpCol = tempElements[i].col;
                    int tmpVal = tempElements[i].val;
                    tempElements[i].col = tempElements[j].col;
                    tempElements[i].val = tempElements[j].val;
                    tempElements[j].col = tmpCol;
                    tempElements[j].val = tmpVal;
                }
            }
        }
    }
    // create the linked list
    if (!numHeads) {
        // if the sparse matrix is empty
        // just create a head
        resHeadNode->right = resHeadNode;
    } else {
        // initialize all head nodes
        for (int i = 0; i < numHeads; ++i) {
            temp = new Node;
            hdnode[i] = temp;
            hdnode[i]->tag = head;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0]; // the last node of the row
        for (int i = 0; i < numTerms; ++i) {
            if (tempElements[i].row > currentRow) { // finish the row
                last->right = hdnode[currentRow];
                currentRow = tempElements[i].row;
                last = hdnode[tempElements[i].row];
            }
            temp = (nodeptr)malloc(sizeof(*temp));
            temp->tag = element;
            temp->u.element.row = tempElements[i].row;
            temp->u.element.col = tempElements[i].col;
            temp->u.element.val = tempElements[i].val;
            last->right = temp; // link row list
            last = temp;
            // link column list
            hdnode[tempElements[i].col]->u.next->down = temp;
            hdnode[tempElements[i].col]->u.next = temp;
        }
        // let the last node of this row
        // point to the first node of this row
        last->right = hdnode[currentRow];
        // let the last node of every column list in this row
        // point to the first node of same list
        for (int i = 0; i < numCols; ++i) {
            hdnode[i]->u.next->down = hdnode[i];
        }
        // link all head nodes
        for (int i = 0; i < numHeads - 1; ++i) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = resHeadNode;
        resHeadNode->right = hdnode[0];
    }

    return resHeadNode;
}

int main()
{
    cout << "Please input the first matrix A:" << endl;
    nodeptr A = mread();
    cout << "Please input the second matrix B:" << endl;
    nodeptr B = mread();
    nodeptr BT = mtranspose(B);
    nodeptr D = mmult(A, BT);
    cout << "B transpose:" << endl;
    mwrite(BT);
    cout << "A * B transpose:" << endl;
    mwrite(D);
    return 0;
}