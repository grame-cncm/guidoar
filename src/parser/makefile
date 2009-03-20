
OUT  = guidolex.c++ guidoparse.c++ guidoparse.hpp
YACC = bison
LEX = flex
PREFIX := guidoar

code : $(OUT)

guidoparse.c++ : guido.y
	$(YACC) -d -o guidoparse.c++  -p $(PREFIX) guido.y

guidoparse.hpp : guido.y
	$(YACC) -d -o guidoparse.c++  -p $(PREFIX) guido.y

guidolex.c++ : guido.l guidoparse.hpp
	$(LEX)  -oguidolex.c++ -I -P$(PREFIX) guido.l

clean:
	rm -f $(OUT)
