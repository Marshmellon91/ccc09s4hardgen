# ccc09s4hardgen
Source Code for CCC'09 S4 (Hard) Generator

# How the siggrading works
Each test case run on the judge is of the form `{generator: generator.cpp, generator_args:[short, int, short, short, bool, bool, bool, bool, bool]}` and stored in `init.yml`. The judge compiles `generator.cpp`, and runs the generator which creates the input file and output file using the reference solution. The input file is read by `handler.cpp`, which packages all the input as parameters and calls the user's function with them. From there, the grading proceeds as normal. Hopefully the output from `handler.cpp` matches the generator's output file and the user gets AC.
