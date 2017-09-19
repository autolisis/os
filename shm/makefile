%.cpp.out: %.cpp
	g++ -g -o $@ $< -lrt
%.c.out: %.c
	gcc -g -o $@ $< -lrt
clean:
	rm -rf *.out
%.py.out: %.py
	cp $< $@
	chmod +x $@
