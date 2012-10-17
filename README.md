# TinyC Compiler

A project for CSE450 Compilers

The assignment was to create a simple "C-like" compiler which compiles to assembly.

# Authors

 - Matt Durak (durakmat)
 - Jason Harris (harri757)
 - Camden Smith (csmith)

# Project 5 additions

 - Function overriding: You can declare functions of same name, different
   arguments. There is error checking for this and it will complain if you
   call something with the wrong number of arguments (Matt's task)
 - Added run_tests.sh Which will run all tests and print the expected output
 - Added 'if' and 'while' (Jason and Cam)
 - Added '<', '>', '!=', '==' comparisons (Jason and Cam)

# Project 5 Honor's Option (Matt Durak)

 - Expanded on my last Honor's option to add nested block-level scopes
 - Can declare a variable in an arbitrily nested block (within {}) and only
   access it at that level or deeper
 - Child scopes can override parent
 - Parent scope is accessible from child
 - Tests t33, t34, and t35 show it working

# Notes

 - If you try to use an undeclared variable, it gives an error and shows the 
   line number
 - Test "t9" demonstrates this but it does **not** run by default because
   the compiler will return a "1" and stop the make from continuing
 - There is no error checking for function parameters

# Do Something Extra (Matt Durak)
 - I made it so that you can declare variables later in the functions
 - Also, you can assign and declare in one statement
 - Test t13.tc demonstrates this working