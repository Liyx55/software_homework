/*
** (C) Copyright 2020 Zty. LTD.(WuHan) All Rights Reserved.
** Description：Shu
** Author：Lyx,Sjy
** Date: 
** Modify Record:
*/
#include"shudu.h"

Input::Input(int a, char** b) {
    this->argc = a;
    this->argv = b;
    type1 = 'y';
    type2 = 'y';
    this->num = 0;
    this->diff = 0;
    this->range1 = 0;
    this->range2 = 0;
}

void Input::ParameterProcess() {
    if (this->argc == 3) {
        if (!strcmp(this->argv[1], "-c")) {
            int len = strlen(this->argv[2]);
            for (int i = 0; i < len; i++) {
                if (this->argv[2][i] > '9' || this->argv[2][i] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The second param should be a positive integer\n";
                    exit(1);
                }
            }

            int number = 0;
            for (int i = 0; i < len; i++) {
                number = number * 10 + this->argv[2][i] - '0';
            }
            if (number < 1 || number>1000000) {
                printf("Please input 1 to 1000000֮\n");
                exit(1);
            } else {
                this->num = number;
                this->type1 = 'c';
            }
        }

        if (!strcmp(this->argv[1], "-s")) {
            this->type1 = 's';
            strncpy(AbsolutePath, this->argv[2], 30);  // ?
        }

        // default path ques.txt
        if (!strcmp(this->argv[1], "-n")) {
            int len = strlen(this->argv[2]);
            for (int i = 0; i < len; i++) {
                if (this->argv[2][i] > '9' || this->argv[2][i] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The second param should be a positive integer\n";
                    exit(1);
                }
            }

            int number = 0;
            for (int i = 0; i < len; i++) {
                number = number * 10 + this->argv[2][i] - '0';
            }
            if (number < 1 || number>1000000) {
                printf("Please input 1 to 1000000֮\n");
                exit(1);
            } else {
                this->num = number;
                this->type1 = 'n';
            }
        }
    } else if (argc == 4) {
        if (strcmp(this->argv[1], "-n") && strcmp(this->argv[3], "-u"))    {
            cout << "Illegal paramater\n"
                << "The first param should be -n, the third should be -u\n";
            exit(1);
        }

        if (!strcmp(this->argv[1], "-n")) {
            int len = strlen(this->argv[2]);
            for (int i = 0; i < len; i++) {
                if (this->argv[2][i] > '9' || this->argv[2][i] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The second param should be a positive integer\n";
                    exit(1);
                }
            }

            int number = 0;
            for (int i = 0; i < len; i++) {
                number = number * 10 + this->argv[2][i] - '0';
            }
            if (number < 1 || number>1000000) {
                printf("Please input 1 to 1000000֮\n");
                exit(1);
            } else {
                this->num = number;
                this->type1 = 'n';
                this->type2 = 'u';
            }
        }
    } else if (argc == 5) {
        if (strcmp(this->argv[1], "-n") && (strcmp(this->argv[3], "-m")
        || strcmp(this->argv[3], "-r"))) {
            cout << "Illegal paramater\n"
                << "The first param should be -n, the third -r or -m\n";
            exit(1);
        }

        if (!strcmp(this->argv[1], "-n")) {
            int len = strlen(this->argv[2]);
            for (int i = 0; i < len; i++) {
                if (this->argv[2][i] > '9' || this->argv[2][i] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The second param should be a positive int\n";
                    exit(1);
                }
            }

            int number = 0;
            for (int i = 0; i < len; i++) {
                number = number * 10 + this->argv[2][i] - '0';
            }
            if (number < 1 || number>1000000) {
                printf("Please input 1 to 1000000֮\n");
                exit(1);
            } else {
                this->num = number;
                this->type1 = 'n';
            }
            if (!strcmp(this->argv[3], "-m")) {
                if (this->argv[4][0] > '3' || this->argv[4][0] < '1') {
                    cout << "Illegal paramater\n";
                    cout << "The forth param should be a positive int(1-3)\n";
                    exit(1);
                }

                int diff = 0;
                diff = this->argv[4][0] - '0';
                this->type2 = 'm';
                this->diff = diff;
            } else {
                int len = strlen(this->argv[4]);
                if (this->argv[4][0] > '9' || this->argv[4][0] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The forth param should be a positive integer\n";
                    exit(1);
                }
                if (this->argv[4][1] > '9' || this->argv[4][1] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The forth param should be a positive integer\n";
                    exit(1);
                }
                /*if (argv[4][2] != '~' || argv[4][2] != '-')
                {
                    cout << "Illegal paramater\n";
                    cout << "The split symbol should be ~ or -\n";
                    return 1;
                }*/
                if (this->argv[4][3] > '9' || this->argv[4][3] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The forth param should be a positive integer\n";
                    exit(1);
                }
                if (this->argv[4][4] > '9' || this->argv[4][4] < '0') {
                    cout << "Illegal paramater\n";
                    cout << "The forth param should be a positive integer\n";
                    exit(1);
                }
                int number1 = 0;
                int number2 = 0;
                int temp1 = (this->argv[4][0] - '0') * 10;
                int temp2 = (this->argv[4][3] - '0') * 10;
                number1 = temp1 + this->argv[4][1] - '0';
                number2 = temp2 + this->argv[4][4] - '0';
                this->type2 = 'r';
                this->range1 = number1;
                this->range2 = number2;
            }
        }
    } else {
        cout << "Illegal paramater number\n"
            << "Usage:\n"
            << "      sudoku.exe -c number --> "
            << "generate n sudoku finals. \n"
            << "      sudoku.exe -s path --> Read sudoku from"
            << " file in the given path,and solve them.\n"
            << "      sudoku.exe -n number --> produce sudoku problem"
            << " into the given path(prepare for the sudoku game)\n"
            << "      The charactre should be itself:"
            << "such as C is not equal to c.\n";
        exit(1);
    }
}

char Input::GetType1() {
    char c;
    c = this->type1;
    return c;
}

char Input::GetType2() {
    char c;
    c = this->type2;
    return c;
}

int Input::GetNum() {
    int x;
    x = this->num;
    return x;
}

int Input::GetDiff() {
    int x;
    x = this->diff;
    return x;
}

int Input::GetRange1() {
    int x;
    x = this->range1;
    return x;
}

int Input::GetRange2() {
    int x;
    x = this->range2;
    return x;
}
