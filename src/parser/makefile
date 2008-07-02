
OUT  = guidolex.cpp guidoparse.cpp guidoparse.hpp
YACC = bison
LEX = flex
PREFIX := guido

code : $(OUT)

guidoparse.cpp : guido.y
	$(YACC) -d -o guidoparse.cpp  -p $(PREFIX) guido.y

guidoparse.hpp : guido.y
	$(YACC) -d -o guidoparse.cpp  -p $(PREFIX) guido.y

guidolex.cpp : guido.l guidoparse.hpp
	$(LEX)  -oguidolex.cpp -I -P$(PREFIX) guido.l

clean:
	rm -f $(OUT)
