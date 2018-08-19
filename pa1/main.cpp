#include <iostream>
#include <iomanip>

using  namespace std;

const int MAX_SIZE = 15;    // Maximum size the magic square can be

// Initialize functions
int getMagicSquareSize();
void fillMagicSquare(int, int[MAX_SIZE][MAX_SIZE]);
void getRowSum(int, int[MAX_SIZE][MAX_SIZE]);
void getColSum(int, int[MAX_SIZE][MAX_SIZE]);
void getDiagonalSum(int, int[MAX_SIZE][MAX_SIZE]);
void rotateSquare(int, int[MAX_SIZE][MAX_SIZE]);
void flipSquare(int, int[MAX_SIZE][MAX_SIZE]);
void printSquare(int, int[MAX_SIZE][MAX_SIZE]);
void switchRows(int, int[MAX_SIZE][MAX_SIZE]);
void switchCols(int, int[MAX_SIZE][MAX_SIZE]);

int main() {

    int magicSquare[MAX_SIZE][MAX_SIZE];    // Initialize magic square
    char quit = ' ';

    while(quit != 'q') {
        int sqSize = getMagicSquareSize();

        int i = 1;  // Counter

        cout << "\nMagic Square #" << i << " is: \n\n";

        fillMagicSquare(sqSize, magicSquare);
        printSquare(sqSize, magicSquare);
        cout << endl;

        getRowSum(sqSize, magicSquare);
        getColSum(sqSize, magicSquare);
        getDiagonalSum(sqSize, magicSquare);

        i++;

        for (; i <= 4; i++) {   // Rotate square 3 times
            cout << "\nMagic Square #" << i << " is: \n\n";

            rotateSquare(sqSize, magicSquare);  // Rotate square clockwise
            printSquare(sqSize, magicSquare);

            cout << endl;

            getRowSum(sqSize, magicSquare);
            getColSum(sqSize, magicSquare);
            getDiagonalSum(sqSize, magicSquare);
        }

        cout << "\nMagic Square #" << i << " is: \n\n";
        flipSquare(sqSize, magicSquare);    // flip square
        printSquare(sqSize, magicSquare);
        cout << endl;

        getRowSum(sqSize, magicSquare);
        getColSum(sqSize, magicSquare);
        getDiagonalSum(sqSize, magicSquare);

        i++;

        for (; i <= 8; i++) {   // Rotate 3 times
            cout << "\nMagic Square #" << i << " is: \n\n";

            rotateSquare(sqSize, magicSquare);
            printSquare(sqSize, magicSquare);

            cout << endl;

            getRowSum(sqSize, magicSquare);
            getColSum(sqSize, magicSquare);
            getDiagonalSum(sqSize, magicSquare);
        }

        cout << "\nMagic Square #" << i << " is: \n\n";
        switchRows(sqSize, magicSquare);    // Switch top and bottom rows
        printSquare(sqSize, magicSquare);   // Switch first and last columns

        cout << endl;

        getRowSum(sqSize, magicSquare);
        getColSum(sqSize, magicSquare);
        getDiagonalSum(sqSize, magicSquare);

        i++;

        cout << "\nMagic Square #" << i << " is: \n\n";
        switchCols(sqSize, magicSquare);
        printSquare(sqSize, magicSquare);

        cout << endl;

        getRowSum(sqSize, magicSquare);
        getColSum(sqSize, magicSquare);
        getDiagonalSum(sqSize, magicSquare);

        cout << "\nEnter 'q' to quit, or enter any key to continue: ";
        cin >> quit;
        cout << endl;
    }

    return 0;
}

int getMagicSquareSize() {
    /*
     * Asks user for the size of the magic square.
     * Checks if the input is an odd number from 3 to 15.
     * Returns magic square size.
     */

    int i = 0;

    cout << "Enter the size of a magic square: ";

    int x = 0;
    cin >> x;

    // if input is not an odd number between 3 and 15, or input is bad, ask user for valid input
    while (x != 3 && x != 5 && x != 7 && x != 9 && x != 11 && x != 13 && x != 15) {
        cout << "\nThe value must be an odd number between 3 and 15.\n";
        cout << "Enter the size of a magic square: ";

        // Clear input stream
        cin.clear();
        cin.ignore(900000, '\n');
        cin >> x;
    }

    return x;
}

void fillMagicSquare(int arraySize, int array[MAX_SIZE][MAX_SIZE]) {
    /*
     * Fills magic square according to the "Siamese method" on Wikipedia, which starts "in the central column of the
     * first row with the number 1. After that, the fundamental movement for filling the squares is diagonally up and
     * right, one step at a time. If a filled square is encountered, one moves vertically down one square instead, then
     * continues as before. When an "up and to the right" move would leave the square, it is wrapped around to the last
     * row or first column, respectively."
     */

    // Set array elements to 0
    for (int i = 0; i <= MAX_SIZE - 1; i++) {
        for (int j = 0; j <= MAX_SIZE - 1; j++) {
            array[i][j] = 0;
        }
    }

    int row = 0, col = arraySize / 2; // Start position for first element

    for(int count = 1; count <= (arraySize * arraySize);) {
        // If row and column are out of bounds, increase row by 2 and decrease column by 1.
        // This is for the case when array is at column 3 and row -1, which is out of bounds.
        if(row == -1 && col == arraySize){
            row += 2;
            col--;
        }
        else {
            // If only column is out of bounds, wrap around to first column
            if(col == arraySize){
                col = 0;
            }
            // If only row is out of bounds, wrap around to last row
            if (row < 0) {
                row = arraySize - 1;
            }
        }
        // If next space is not 0, decrease row by 2 and column by one, so the space will be below the current space
        if (array[row][col] != 0) {
            row += 2;
            col--;
            continue;
        }
        // Otherwise, set space to count
        else{
            array[row][col] = count++;
        }
        // Decrease row, increase column. Move up one, right one.
        row--;
        col++;
    }
}

void printSquare(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    // Print magic square
    for(int x = 0; x <= arraySize - 1; x++) {
        for(int y = 0; y <= arraySize - 1; y++){
            printf("%3d ", array[x][y]);
        }
        cout << "\n";
    }
}

void rotateSquare(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    int temp[arraySize][arraySize];

    // Rotate square clockwise
    for(int x = 0; x <= arraySize - 1; x++){
        for(int y = 0; y <= arraySize - 1; y++){
            temp[x][y] = array[arraySize - y - 1][x];
        }
    }
    // Set array to temp array
    for(int x = 0; x <= arraySize - 1; x++){
        for(int y = 0; y <= arraySize - 1; y++){
            array[x][y] = temp[x][y];
        }
    }
}

void flipSquare(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    int temp[arraySize][arraySize];

    // flip square
    for(int x = 0; x <= arraySize - 1; x++){
        for(int y = 0; y <= arraySize - 1; y++){
            temp[x][y] = array[y][x];
        }
    }
    // Set array to temp array
    for(int x = 0; x <= arraySize - 1; x++){
        for(int y = 0; y <= arraySize - 1; y++){
            array[x][y] = temp[x][y];
        }
    }
}

void switchRows(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    /*
     * Switch first and last rows of magic square
     */

    int temp[arraySize];

    for(int x = 0; x <= arraySize - 1; x++) {
        temp[x] = array[0][x];
        array[0][x] = array[arraySize - 1][x];
        array[arraySize - 1][x] = temp[x];
    }
}

void switchCols(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    /*
     * Switch first and last columns of magic square
     */

    int temp[arraySize];

    for(int x = 0; x <= arraySize - 1; x++) {
        temp[x] = array[x][0];
        array[x][0] = array[x][arraySize - 1];
        array[x][arraySize - 1] = temp[x];
    }
}

void getRowSum(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    /*
     * Calculate and print row sums
     */

    int rowSum = 0;

    cout << "Checking sums of every row: " << fixed << setw(7);

    for(int x = 0; x <= arraySize - 1; x++){
        for(int y = 0; y <= arraySize - 1; y++){
            rowSum += array[x][y];
        }
        cout << rowSum << " ";
        rowSum = 0;
        }
     cout << endl;
}

void getColSum(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    /*
     * Calculate and print column sums
     */

    int colSum = 0;

    cout << "Checking sums of every column: " << fixed << setw(4);

    for(int x = 0; x <= arraySize - 1; x++){
        for(int y = 0; y <= arraySize - 1; y++){
            colSum += array[y][x];
        }
        cout << colSum << " ";
        colSum = 0;
    }
    cout << endl;
}

void getDiagonalSum(int arraySize, int array[MAX_SIZE][MAX_SIZE]){
    /*
     * Calculate and print diagonal sums
     */

    int diagonalSum1 = 0, diagonalSum2 = 0;
    int count = 0;

    cout << "Checking sums of every diagonal: ";

    for(int x = 0; x <= arraySize - 1; x++){    // Calculate first diagonal
        diagonalSum1 += array[x][count];
        count++;
    }

    count = arraySize - 1;
    for(int x = arraySize - 1; x >= 0; x--){    // Calculate second diagonal
        diagonalSum2 += array[x][count];
        count--;
    }

    cout << fixed << setw(2) << diagonalSum1 << " " << diagonalSum2 << endl;



}