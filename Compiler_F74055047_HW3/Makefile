CC = gcc -g
YFLAG = -d
FNAME = compiler_hw3
PARSER = myparser
OBJECT = lex.yy.c y.tab.c y.tab.h ${FNAME}.j ${FNAME}.class

all: y.tab.o lex.yy.o gencode.o
	@${CC} -o ${PARSER} $^
%.o: %.c
	@${CC} -c $<

lex.yy.c: ${FNAME}.l
	@lex ${FNAME}.l

y.tab.c: ${FNAME}.y
	@yacc ${YFLAG} ${FNAME}.y

test1:
	@./${PARSER} < ./example_input/basic_declaration.c
	@echo -e "\n\033[1;33mmain.class output\033[0m"
	@java -jar jasmin.jar ${FNAME}.j
	@java ${FNAME} 

test2:
	@./${PARSER} < ./example_input/basic_function.c
	@echo -e "\n\033[1;33mmain.class output\033[0m"
	@java -jar jasmin.jar ${FNAME}.j
	@java ${FNAME} 

test3:
	@./${PARSER} < ./example_input/basic_if_statement.c
	@echo -e "\n\033[1;33mmain.class output\033[0m"
	@java -jar jasmin.jar ${FNAME}.j
	@java ${FNAME} 

test4:
	@./${PARSER} < ./example_input/basic_while_statement.c
	@echo -e "\n\033[1;33mmain.class output\033[0m"
	@java -jar jasmin.jar ${FNAME}.j
	@java ${FNAME} 

clean:
	rm -f *.o ${PARSER} ${OBJECT} 
