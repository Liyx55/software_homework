/*
** (C) Copyright 2020 Zty. LTD.(WuHan) All Rights Reserved.
** Description：Shu
** Author：Lyx,Sjy
** Date: 
** Modify Record:
*/
#ifndef INPUTCONTROL
#define INPUTCONTROL
class Input {
 public:
    void ParameterProcess();
    Input(int a, char** b);
    char GetType1();
    char GetType2();
    int GetNum();
    int GetDiff();
    int GetRange1();
    int GetRange2();
 private:
    int argc;
    char** argv;
    char type1;
    char type2;
    int diff;
    int range1;
    int range2;
    int num;
};
#endif
