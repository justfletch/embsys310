#if 1
int func1 (int arg1, int arg2, int arg3, int arg4, int arg5){
    
    int input_arg1 = arg1;
    int input_arg2 = arg2;
    int input_arg3 = arg3;
    int input_arg4 = arg4;
    int input_arg5 = arg5;
    
    int sum;
    sum = input_arg1 + input_arg2 + input_arg3 + input_arg4 + input_arg5;
    
    return sum;
}

int func2 (){
    
    int input1 = 10;
    int input2 = 20;
    int input3 = 30;
    int input4 = 40;
    int input5 = 50;
    
    int sum_plus_one;
    sum_plus_one = func1(input1, input2, input3, input4, input5) + 1;
    
    return sum_plus_one;
}

int main()
    {
        int runFunc2;
        runFunc2 = func2();
        return 0;
    }

#endif

#if 0
int func1 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10){
    
    int input_arg1 = arg1;
    int input_arg2 = arg2;
    int input_arg3 = arg3;
    int input_arg4 = arg4;
    int input_arg5 = arg5;
    int input_arg6 = arg6;
    int input_arg7 = arg7;
    int input_arg8 = arg8;
    int input_arg9 = arg9;
    int input_arg10 = arg10;
    
    int sum;
    sum = input_arg1 + input_arg2 + input_arg3 + input_arg4 + input_arg5 + input_arg6 + input_arg7 + input_arg8 + input_arg9 + input_arg10;
    
    return sum;
}

int func2 (){
    
    int input1 = 10;
    int input2 = 20;
    int input3 = 30;
    int input4 = 40;
    int input5 = 50;
    int input6 = 60;
    int input7 = 70;
    int input8 = 80;
    int input9 = 90;
    int input10 = 100;
    
    int sum_plus_one;
    sum_plus_one = func1(input1, input2, input3, input4, input5, input6, input7, input8, input9, input10) + 1;
    
    return sum_plus_one;
}

int main()
    {
        int runFunc2;
        runFunc2 = func2();
        return 0;
    }

#endif