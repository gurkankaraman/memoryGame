#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace::std;

void printArray(int** arr, int row, int column, int score);
void clearScreen();
void saveGame(int** arr2, int** arr3, int user_row, int user_column, int right_answer, int wrong_answer);
void sleep(int sec);
void clear();

int main() {

    clearScreen();

jump:

    int column1, column2, row1, row2, right_answer = 0, wrong_answer = 0, score = 0, user_answer, user_column = 0, user_row = 0, cards = 0;
    bool is_game_on = true, start = false, is_card_correct1, is_card_correct2;

    cout << "  0     0    0 0 0 0    0     0    0 0 0 0   0 0 0 0   0     0 " << "\n";
    cout << " 0 0   0 0   0         0 0   0 0   0     0   0     0    0   0  " << "\n";
    cout << " 0  0 0  0   0 0 0 0   0  0 0  0   0     0   0 0 0 0     0 0   " << "\n";
    cout << " 0   0   0   0         0   0   0   0     0   0   0        0    " << "\n";
    cout << " 0       0   0 0 0 0   0       0   0 0 0 0   0     0      0    " << "\n";
    cout << "                            Game                               " << "\n\n";
    cout << "                 Press 1 to Start New Game                     " << "\n";
    cout << "               Press 2 to Load Previous Game                   " << "\n";
    cout << "                 Press 3 to Close the Game                     " << "\n";
    cout << "While the Game is Running, You Can Return the Main Menu (Press Any Key)" << "\n";

    cin >> user_answer;

    clearScreen();

    if (user_answer == 1) {
        while (!start) {
            cout << "Please Enter a Row Size: ";
            cin >> user_row;

            cout << "Please Enter a Column Size: ";
            cin >> user_column;

            cards = user_row * user_column;
            if (cards % 2 == 0 && user_row >= 4 && user_column >= 4) {
                start = true;
            }
            else {
                clearScreen();
                cout << "The Total Number of Cards Must be Even and the Number of Rows and Columns Must be More Than Four. " << "\n";
            }
        }
    }
    else if (user_answer == 2) {
        ifstream main("main.txt");
        main >> user_row;
        main >> user_column;
        main >> right_answer;
        main >> wrong_answer;
        score = (right_answer * 3) - (wrong_answer);
        cards = user_row * user_column;
    }
    else {
        return 0;
    }

    int** arr2 = new int* [user_row];
    for (int i = 0; i < user_row; i++) {
        arr2[i] = new int[user_column];
    }
    int** arr3 = new int* [user_row];
    for (int i = 0; i < user_row; i++) {
        arr3[i] = new int[user_column];
    }

    if (user_answer == 1) {

        int* arr1 = new int[cards];
        int* left = arr1;
        int* right = arr1 + cards - 1;
        int i = 1;
        while (left < right) {
            *left = i;
            *right = i;
            left++;
            right--;
            i++;
        }
        srand((unsigned)time(NULL));

        for (int i = 0; i < 100; i++) {
            int random_number1 = rand() % cards;
            int random_number2 = rand() % cards;
            int c = arr1[random_number1];
            arr1[random_number1] = arr1[random_number2];
            arr1[random_number2] = c;
        }

        for (int i = 0; i < user_row; i++) {
            for (int j = 0; j < user_column; j++) {
                arr3[i][j] = 0;
                arr2[i][j] = arr1[i * user_column + j];
            }
        }

        printArray(arr2, user_row, user_column, score);
        cout << "The game starts in 5 seconds.\n";
        sleep(5);

        delete[] arr1;

    }
    else {
        ifstream fileArr2("arr2.txt");
        ifstream fileArr3("arr3.txt");
        for (int i = 0; i < user_row; i++) {
            for (int j = 0; j < user_column; j++) {
                fileArr2 >> arr2[i][j];
                fileArr3 >> arr3[i][j];
            }
        }
    }

    while (is_game_on) {

        printArray(arr3, user_row, user_column, score);
        cout << "Enter a coordinate: ";
        cin >> row1 >> column1;

        if (!cin.good()) {
            saveGame(arr2, arr3, user_row, user_column, right_answer, wrong_answer);
            clearScreen();
            clear();
            goto jump;
        }
        if (0 < column1 && column1 < user_column + 1 && 0 < row1 && row1 < user_row + 1 &&
            arr3[row1 - 1][column1 - 1] == 0) {
            is_card_correct1 = true;
        }
        else {
            clearScreen();
            cout << "Please make a valid move.\n";
            sleep(2);
            is_card_correct1 = false;
        }

        while (is_card_correct1) {

            arr3[row1 - 1][column1 - 1] = arr2[row1 - 1][column1 - 1];
            printArray(arr3, user_row, user_column, score);
            cout << "Enter a coordinate: ";
            cin >> row2 >> column2;

            if (!cin.good()) {
                arr3[row1 - 1][column1 - 1] = 0;
                saveGame(arr2, arr3, user_row, user_column, right_answer, wrong_answer);
                clearScreen();
                clear();
                goto jump;
            }
            if (0 < column2 && column2 < user_column + 1 && 0 < row2 && row2 < user_row + 1 &&
                arr3[row2 - 1][column2 - 1] == 0) {
                is_card_correct2 = true;
            }
            else {
                clearScreen();
                cout << "Please make a valid move.\n";
                sleep(2);
                is_card_correct2 = false;
            }

            if (is_card_correct2) {
                arr3[row2 - 1][column2 - 1] = arr2[row2 - 1][column2 - 1];

                printArray(arr3, user_row, user_column, score);

                if (arr3[row1 - 1][column1 - 1] == arr3[row2 - 1][column2 - 1]) {
                    right_answer += 1;
                }
                else {
                    arr3[row1 - 1][column1 - 1] = 0;
                    arr3[row2 - 1][column2 - 1] = 0;
                    wrong_answer += 1;
                    sleep(2);
                }
                is_card_correct1 = false;
            }
        }
        score = (right_answer * 3) - (wrong_answer);
        if (right_answer == cards / 2) {

            printArray(arr3, user_row, user_column, score);

            cout << "You Won" << endl;

            cout << "Do You Want to Return the Main Menu ? ( 1 - YES ) ( 2 - NO ) " << endl;
            cin >> user_answer;

            if (user_answer == 1) {
                clear();
                clearScreen();
                goto jump;
            }
            is_game_on = false;
        }
    }

    delete[] arr2;
    delete[] arr3;

    return 0;
}

void printArray(int** arr, int row, int column, int score)
{
    clearScreen();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << arr[i][j];
            if (arr[i][j] >= 10) {
                cout << "   ";
            }
            else {
                cout << "    ";
            }
        }
        cout << endl;
    }
    cout << "Score : " << score << endl;
}

void clearScreen() {
    system("cls");
}

void saveGame(int** arr2, int** arr3, int user_row, int user_column, int right_answer, int wrong_answer) {
    ofstream fileArr2("arr2.txt");
    ofstream fileArr3("arr3.txt");
    ofstream main("main.txt");
    for (int i = 0; i < user_row; i++) {
        for (int j = 0; j < user_column; j++) {
            fileArr2 << arr2[i][j] << " ";
            fileArr3 << arr3[i][j] << " ";
        }
        fileArr2 << endl;
        fileArr3 << endl;
    }
    main << user_row << " ";
    main << user_column << " ";
    main << right_answer << " ";
    main << wrong_answer << " ";
}

void sleep(int sec) {
    this_thread::sleep_for(chrono::seconds(sec));
}

void clear() {
    cin.clear();
    cin.ignore();
}
