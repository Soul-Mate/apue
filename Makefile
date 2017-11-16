DIRS = lib unit3 unit7 unit8 unit10 unit11 unit12 unit13

all:
		for i in $(DIRS); do \
			(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
		done

clean:
		for i in $(DIRS); do \
			(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
		done

