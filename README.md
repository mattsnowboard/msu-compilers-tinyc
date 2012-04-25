# TinyC Compiler

# Authors

 - Matt Durak (durakmat)
 - Jason Harris (harri757)
 - Camden Smith (csmith)

# Project 5 additions

 - Function overriding: You can declare functions of same name, different
   arguments. There is error checking for this and it will complain if you
   call something with the wrong number of arguments (Matt's task)
 - Added run_tests.sh Which will run all tests and print the expected output

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