SUBDIRS := $(wildcard examples/ats/*/)

all:
	@for i in $(SUBDIRS); do \
		$(MAKE) -C $$i; \
	done

clean realclean:
	@for i in $(SUBDIRS); do \
		$(MAKE) -C $$i $@; \
	done

.PHONY: all clean
