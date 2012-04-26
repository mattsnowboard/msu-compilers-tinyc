#!/bin/bash

# run the tests and print what's going on

echo
echo "Running project4 tests"
echo

# clear make log
echo "" >./make.log

echo "********************************************************************************"
echo "Test 0: main compiles"
echo "Expect: N/A"
make t0 >>./make.log
./t0
echo

echo "********************************************************************************"
echo "Test 1: simple assign and write variable"
echo "Expect: 3"
make t1 >>./make.log
./t1
echo

echo "********************************************************************************"
echo "Test 2: write constant"
echo "Expect: -44"
make t2 >>./make.log
./t2
echo

echo "********************************************************************************"
echo "Test 3: assign x 100/5, print result"
echo "Expect: 20"
make t3 >>./make.log
./t3
echo

echo "********************************************************************************"
echo "Test 4: function call (expr as param)"
echo "Expect: 50"
make t4 >>./make.log
./t4
echo

echo "********************************************************************************"
echo "Test 5: function call, no parameters"
echo "Expect: 2"
make t5 >>./make.log
./t5
echo

echo "********************************************************************************"
echo "Test 6: modulo operator, unused function ignored"
echo "Expect: 0"
make t6 >>./make.log
./t6
echo

echo "********************************************************************************"
echo "Test 7: nested function call"
echo "Expect: 10"
make t7 >>./make.log
./t7
echo

echo "********************************************************************************"
echo "Test 8: complex expression (5 * 2 + 4 % 3 / 2 = 10)"
echo "Expect: 10"
make t8 >>./make.log
./t8
echo

echo "********************************************************************************"
echo "Test 9: undeclared variables"
echo "Expect: Undefined variable: 'x', on line 15"
make t9
rm t9.s
echo

echo "********************************************************************************"
echo "Test 10: call funciton in return statement"
echo "Expect: "
echo "10"
echo "5"
echo "10"
echo "5"
echo "5"
echo "5"
echo ">>END"
make t10  >>./make.log
./t10
echo

echo "********************************************************************************"
echo "Test 11: function call as parameter to function call"
echo "Expect: 6"
make t11 >>./make.log
./t11
echo

echo "********************************************************************************"
echo "Test 12: directly write function result"
echo "Expect: 11"
make t12 >>./make.log
./t12
echo

echo "********************************************************************************"
echo "Test 13: test declare variable anywhere"
echo "Expect: "
echo "500"
echo "250"
echo "749"
echo ">>END"
make t13 >>./make.log
./t13
echo

echo "********************************************************************************"
echo "Test 14: function call in expression (bug fix from Project4)"
echo "Expect:"
echo "21"
echo "55"
echo "-43"
echo ">>END"
make t14 >>./make.log
./t14
echo

echo "********************************************************************************"
echo
echo "Tests of new functionality"
echo 

echo "********************************************************************************"
echo "Test 15: Test function overloading"
echo "Expect: 7"
make t15 >>./make.log
./t15
echo

echo "********************************************************************************"
echo "Test 16: Test lots of adds"
echo "Expect:"
echo "7"
echo "14"
echo ">>END"
make t16 >>./make.log
./t16
echo

echo "********************************************************************************"
echo "Test 17: Test nested function call adds (bug fix)"
echo "Expect: 31"
make t17 >>./make.log
./t17
echo

echo "********************************************************************************"
echo "Test 18: Function call with missing parameters"
echo "Expect: Undefined function called: 'foo', with 0 arguments, on line 9"
make t18
rm t18.s
echo

echo "********************************************************************************"
echo "Test 19: Function call with extra parameters"
echo "Expect: Undefined function called: 'foo', with 2 arguments, on line 9"
make t19
rm t19.s
echo

echo "********************************************************************************"
echo "Test 20: Function redeclared"
echo "Expect: Function 'foo' redeclared with 1 arguments, on line 7"
make t20
rm t20.s
echo

echo "********************************************************************************"
echo "Test 21: Call undefined function name"
echo "Expect: Undefined function called: 'foo', with 0 arguments, on line 3"
make t21
rm t21.s
echo

echo "********************************************************************************"
echo "Test 22: Simple IF"
echo "Expect: 1"
make t22 >>./make.log
./t22
echo

echo "********************************************************************************"
echo "Test 23: IF multiple statemnts and an if that is false"
echo "Expect: 4"
make t23 >>./make.log
./t23
echo

echo "********************************************************************************"
echo "Test 24: IF function call"
echo "Expect: 3"
make t24 >>./make.log
./t24
echo

echo "********************************************************************************"
echo "Test 25: nested IF "
echo "Expect: 100"
make t25 >>./make.log
./t25
echo

echo "********************************************************************************"
echo "Test 26: Simple WHILE"
echo "Expect:"
echo "5"
echo "4"
echo "3"
echo "2"
echo "1"
echo ">>END"
make t26 >>./make.log
./t26
echo

echo "********************************************************************************"
echo "Test 27: nested WHILE"
echo "Expect:"
echo "1"
echo "2"
echo "1"
echo "3"
echo "2"
echo "1"
echo ">>END"
make t27 >>./make.log
./t27
echo


echo "********************************************************************************"
echo "Test 28: Simple IF Equality"
echo "Expect: 1"
make t28 >>./make.log
./t28
echo

echo "********************************************************************************"
echo "Test 29: Simple IF NotEquality"
echo "Expect: 1"
make t29 >>./make.log
./t29
echo

echo "********************************************************************************"
echo "Test 30: Simple IF Equality"
echo "Expect: 0"
make t30 >>./make.log
./t30
echo

echo "********************************************************************************"
echo "Test 31: Simple IF Equality"
echo "Expect: 0"
make t31 >>./make.log
./t31
echo

echo "********************************************************************************"
echo "Test 32: Fibonacci recursion test"
echo "Expect: 8"
make t32 >>./make.log
./t32
echo

echo "********************************************************************************"
echo "Test 33: scope nesting override variable test"
echo "Expect:"
echo "1"
echo "0"
echo ">>END"
make t33 >>./make.log
./t33
echo

echo "********************************************************************************"
echo "Test 34: three level scope test"
echo "Expect: 400"
make t34 >>./make.log
./t34
echo

echo "********************************************************************************"
echo "Test 35: Undefined variable outside of scope"
echo "Expect: Undefined variable: 'i', on line 7"
make t35 >>./make.log
rm t34.s
echo