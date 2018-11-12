#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

#define MAX_SIZE 100

// define the struct element
typedef struct Node* nodeptr;
struct NodeElement {
    int row;
    int col;
    int val;
};
struct Node {
    nodeptr down;
    nodeptr right;
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
    nodeptr headNode, temp, last, connect;
    int numRows = 0, numCols = 0, numTerms = 0, numHeads = 0;
    int row = 0, col = 0, val = 0, currentRow = 0;
    // set the number of rows, columns and nonzero terms
    cout << "Please enter number of rows, columns and nonzero terms: " << endl;
    cin >> numRows >> numCols >> numTerms;
    // create the headNode of linked list
    numHeads = (numCols > numRows) ? numCols : numRows;
    headNode = new Node;
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
            hdnode[i]->down = temp;
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
            temp->u.element.row = row;
            temp->u.element.col = col;
            temp->u.element.val = val;
            last->right = temp; // link row list
            last = temp;
            // link column list
            connect = hdnode[col]->down;
            if (connect == hdnode[col]) {
                hdnode[col]->down = temp;
                temp->down = hdnode[col];
            } else if (connect != hdnode[col]) {
                while (connect->down != hdnode[col]) {
                    connect = connect->down;
                }
                connect->down = temp;
                temp->down = hdnode[col];
            }
        }
        // let the last node of this row
        // point to the first node of this row
        last->right = hdnode[currentRow];
        // link all head nodes
        for (int i = 0; i < numHeads - 1; ++i) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = headNode;
        headNode->down = hdnode[0];
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
void testwrite(nodeptr headNode)
{
    nodeptr temp, head = headNode->down;
    cout << "numRows = " << headNode->u.element.row
         << ", numCols = " << headNode->u.element.col << endl
         << "The matrix by row, column and value:" << endl;
    for (int i = 0; i < headNode->u.element.col; ++i) {
        for (temp = head->down; temp != head; temp = temp->down) {
            cout.setf(ios_base::left, ios_base::adjustfield);
            cout << setw(4) << temp->u.element.row << setw(4)
                 << temp->u.element.col << setw(4) << temp->u.element.val
                 << endl;
        }
        head = head->u.next;
    }
}

nodeptr mtranspose(nodeptr req)
{
    // create a new matrix to contain req transpose
    nodeptr res, temp, last, connect;
    nodeptr reqtmp, reqhd = req->down;
    // set the number of rows and columns
    int numRows = req->u.element.col,
        numCols = req->u.element.row;
    int row = 0, col = 0, val = 0, currentRow = 0;
    // create the headNode of linked list
    int numHeads = (numCols > numRows) ? numCols : numRows;
    res = new Node;
    res->u.element.row = numRows;
    res->u.element.col = numCols;
    // create the linked list
    if (!numHeads) {
        // if the sparse matrix is empty
        // just create a head
        res->right = res;
    } else {
        // initialize all head nodes
        for (int i = 0; i < numHeads; ++i) {
            temp = new Node;
            hdnode[i] = temp;
            hdnode[i]->down = temp;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0]; // the last node of the row
        for (int i = 0; i < req->u.element.col; ++i) {
            for (reqtmp = reqhd->down; reqtmp != reqhd; reqtmp = reqtmp->down) {
                row = reqtmp->u.element.col;
                col = reqtmp->u.element.row;
                val = reqtmp->u.element.val;
                if (row > currentRow) { // finish the row
                    last->right = hdnode[currentRow];
                    currentRow = row;
                    last = hdnode[row];
                }
                temp = (nodeptr)malloc(sizeof(*temp));
                temp->u.element.row = row;
                temp->u.element.col = col;
                temp->u.element.val = val;
                last->right = temp; // link row list
                last = temp;
                // link column list
                connect = hdnode[col]->down;
                if (connect == hdnode[col]) {
                    hdnode[col]->down = temp;
                    temp->down = hdnode[col];
                } else if (connect != hdnode[col]) {
                    while (connect->down != hdnode[col]) {
                        connect = connect->down;
                    }
                    connect->down = temp;
                    temp->down = hdnode[col];
                }
            }
            reqhd = reqhd->u.next;
        }
        // let the last node of this row
        // point to the first node of this row
        last->right = hdnode[currentRow];
        // link all head nodes
        for (int i = 0; i < numHeads - 1; ++i) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = res;
        res->down = hdnode[0];
        res->right = hdnode[0];
    }

    return res;
}

nodeptr mmult(nodeptr req1, nodeptr req2)
{
    if (req1->u.element.col != req2->u.element.row) {
        return NULL;
    }
    nodeptr res, temp, last, connect;
    nodeptr tmp1, tmp2, head1 = req1->right, head2;
    int numRows = req1->u.element.row,
        numCols = req2->u.element.col;
    int row = 0, col = 0, val = 0, currentRow = 0;
    // create the headNode of linked list
    int numHeads = (numCols > numRows) ? numCols : numRows;
    res = new Node;
    res->u.element.row = numRows;
    res->u.element.col = numCols;

    int sum[numRows][numCols];
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            sum[i][j] = 0;
        }
    }

    for (int i = 0; i < numRows; ++i) {
        head2 = req2->down;
        for (int j = 0; j < numCols; ++j) {
            tmp1 = head1->right;
            if (tmp1 == head1) {
                break;
            } else {
                tmp2 = head2->down;
                while (tmp2 != head2) {
                    if (tmp1 == head1) {
                        break;
                    }
                    if (tmp1->u.element.col != tmp2->u.element.row) {
                        if (tmp1->u.element.col > tmp2->u.element.row) {
                            tmp2 = tmp2->down;
                        } else {
                            tmp1 = tmp1->right;
                        }
                    } else {
                        sum[i][j] += tmp1->u.element.val * tmp2->u.element.val;
                        tmp1 = tmp1->right;
                        tmp2 = tmp2->down;
                    }
                }
                head2 = head2->u.next;
            }
        }
        head1 = head1->u.next;
    }

    // create the linked list
    if (!numHeads) {
        // if the sparse matrix is empty
        // just create a head
        res->right = res;
    } else {
        // initialize all head nodes
        for (int i = 0; i < numHeads; ++i) {
            temp = new Node;
            hdnode[i] = temp;
            hdnode[i]->down = temp;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0]; // the last node of the row
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (sum[i][j] != 0) {
                    row = i;
                    col = j;
                    val = sum[i][j];
                    if (row > currentRow) { // finish the row
                        last->right = hdnode[currentRow];
                        currentRow = row;
                        last = hdnode[row];
                    }
                    temp = (nodeptr)malloc(sizeof(*temp));
                    temp->u.element.row = row;
                    temp->u.element.col = col;
                    temp->u.element.val = val;
                    last->right = temp; // link row list
                    last = temp;
                    // link column list
                    connect = hdnode[col]->down;
                    if (connect == hdnode[col]) {
                        hdnode[col]->down = temp;
                        temp->down = hdnode[col];
                    } else if (connect != hdnode[col]) {
                        while (connect->down != hdnode[col]) {
                            connect = connect->down;
                        }
                        connect->down = temp;
                        temp->down = hdnode[col];
                    }
                }
            }
        }
        // let the last node of this row
        // point to the first node of this row
        last->right = hdnode[currentRow];
        // link all head nodes
        for (int i = 0; i < numHeads - 1; ++i) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = res;
        res->down = hdnode[0];
        res->right = hdnode[0];
    }

    return res;
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