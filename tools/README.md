# mock generator
A simple script that can generate mock function for cmock automatically.

# Requirements
* Linux(Can't run on some Windows platform because of some unknown bug in python. Untested on other platforms)
* Python 2.7.11+

# Dependencies
clang 3.9.0([http://clang.llvm.org/](http://clang.llvm.org/)) indexing library with python binding.

# Usage
```
python mock_generator.py <Header file of function declaration> [-I<dependence including path>...]
```
You can try the example in this folder using command
``` shell
python mock_generator.py sample/myfuction.h -I./sample/subdir
```
