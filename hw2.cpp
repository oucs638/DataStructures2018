#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
int main()
{
    //create variables
    int n = 0, m = 0, ibug = 0, jbug = 0, record = 0, moves = 0;
    int imove[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int jmove[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
    srand(time(NULL));
    //initialize variables
    cout << "To initialize n x m array count and strart point: " << endl;
    cout << "Please enter n: " << endl;
    cin >> n;
    cout << "Please enter m: " << endl;
    cin >> m;
    cout << "Please enter ibug of start point: " << endl;
    cin >> ibug;
    cout << "Please enter jbug of start point: " << endl;
    cin >> jbug;
    //create count array
    int count[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            count[i][j] = 0;
        }
    }
    record = n * m; //to record how many tile hasn't  been reached
    //set start point
    count[ibug][jbug] += 1;
    record -= 1;
    //cockroach star run
    while (record != 0) {
        int k = rand() % 8;
        int itemp = ibug + imove[k];
        int jtemp = jbug + jmove[k];
        while (!(itemp >= 0 && itemp < n && jtemp >= 0 && jtemp < m)) {
            k = rand() % 8;
            itemp = ibug + imove[k];
            jtemp = jbug + jmove[k];
        }
        ibug = itemp;
        jbug = jtemp;
        moves += 1;
        if (count[ibug][jbug] == 0) {
            record -= 1;
        }
        count[ibug][jbug] += 1;
    };
    //output the results
    cout << "The number of legal moves: " << moves << endl;
    cout << "The final count array: " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (count[i][j] >= 100) {
                cout << count[i][j];
            } else if (count[i][j] >= 10) {
                cout << " " << count[i][j];
            } else {
                cout << "  " << count[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}