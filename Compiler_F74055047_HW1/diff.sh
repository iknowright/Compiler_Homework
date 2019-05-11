#! /bin/bash

diff -u <(./myscanner input/basic_overall.c) output/basic_overall.out
diff -u <(./myscanner input/comment.c) output/comment.out
diff -u <(./myscanner input/declaration.c) output/declaration.out
diff -u <(./myscanner input/function.c) output/function.out
diff -u <(./myscanner input/if_condition.c) output/if_condition.out
diff -u <(./myscanner input/loop.c) output/loop.out
diff -u <(./myscanner input/operators.c) output/operators.out
diff -u <(./myscanner input/print.c) output/print.out