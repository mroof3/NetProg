#!/bin/sh
#########################################################
#                     compile
#
#     Options:
#        -nolink          #just compile, don't link
#        -link exe_name   # name of executable to build,
#        -link all        # build all executables (default)
#
#########################################################

#########################################################
#                         Setup
#########################################################

set -e    # halt on first error

# check command line parameters

link=all  # link all binaries by default
linked=no # track whether we linked

case $1 in  
  -nolink) link=none ; shift ;;  # don't link
  -link)   [ -n "$2" ] || { echo "You need to say *what* to link" >&2; exit 1; } #IDK what this is asking for
           link="$2" ; shift ; shift ;;  # link only one binary
esac

# Choose compilers and set compiler flags

# use 'gcc' as the C compiler
CC=gcc

#  Use the pkg-config utiltiy to get the correct include file flags
#  (-I) and library search flags (-L and -l)
#
CIIFLAGS=`pkg-config --cflags p2server`
CIILIBS=`pkg-config --libs p2server`

# the next three lines enable you to compile and link against 
# course software by setting the compiler search path for 
# includes of .h files (the -I switch) and the search
# path for libraries containing .o files (-L and -l)
#
CFLAGS="-I. -I/comp/40/include $CIIFLAGS"
LIBS="$CIILIBS -lm"    # might add more libraries for some projects
LFLAGS="-L/comp/40/lib64"

# these flags max out warnings and debug info
FLAGS="-g -O -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic"

#########################################################
#     Clean out old object files and compile everything
#########################################################

rm -f *.o  # make sure no object files are left hanging around

case $# in
  0) set *.c ;; # if no args are given, compile all .c files
esac

# compile each argument to a .o file
for cfile 
do
  $CC $FLAGS $CFLAGS -c $cfile
done

#########################################################
#     Link the .o files and libraries to create an
#     executable program
#########################################################

# One case statement per exectuble binary

case $link in
  all|brightness) $CC $FLAGS $LFLAGS -o brightness brightness.o -lpnmrdr $LIBS 
                  linked=yes ;;
esac

case $link in
  all|fgroups)    $CC $FLAGS $LFLAGS -o fgroups    fgroups.o             $LIBS 
                  linked=yes ;;
esac

# put out error msg if asked to link something we didn't recognize
if [ $linked = no ]; then
  case $link in  # if the -link option makes no sense, complain 
    none) ;; # OK, do nothing
    *) echo "`basename $0`: don't know how to link $link" 1>&2 ; exit 1 ;;
  esac
fi
