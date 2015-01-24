mj2MIPS
=======

###compiler

    $ make

###get llvm ir

    $ ./a.out testdata.java

###get mips assembly

    $ llc -march=mips a.ll -o a.s
