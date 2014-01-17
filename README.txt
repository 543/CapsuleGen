 -------------------------------------------------------------------
| New PeriScop Project https://github.com/Lnc/new_PeriScopp_project |
 -------------------------------------------------------------------

Skeleton to start a new project that uses all PeriScop libraries https://github.com/periscop 


 ---------------------------------------------
| System requirement for New PeriScop Project |
 ---------------------------------------------

All projects use CMake, except CLooG witch uses autotools.

The required packages are:
build-essential cmake git flex bison autoconf automake libtool autotools-dev

The optional packages (but recommended, needed for this example) are:
libgmp-dev doxygen

To install all dependencies, you can download and execute:
https://gitorious.org/install_project/install_project/raw/master:example/install_project_PeriScop.py
from https://gitorious.org/install_project


 -------------------------------------
| Compilation of New PeriScop Project |
 -------------------------------------

Use CMake to build New PeriScop Project:
---------------------------------------
mkdir build
cd build
cmake .. #-DCMAKE_INSTALL_PREFIX=/path/to/install/the/project
make
# make doc
# make test
# make install # su -c "make install" # sudo make install

Run the executable:
------------------
./main ../source_code_with_scop/for_loop.c
