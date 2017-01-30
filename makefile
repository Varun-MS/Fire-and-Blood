all:
	(cd obj && make)

.PHONY: clean

clean: 
	rm CGProject
	(cd src && rm *.gch)
	(cd obj && make clean)