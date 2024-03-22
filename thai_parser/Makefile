MODULE_big = thai_parser
OBJS = src/thai_parser.o src/converter.o src/tokenizer.o

EXTENSION = thai_parser
DATA = sql/thai_parser--1.0.sql sql/thai_parser--unpackaged--1.0.sql

REGRESS = thai_parser

LIBDIR = /usr/local/lib/
LIB_FLAGS = -lthai -liconv #-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -fno-omit-frame-pointer
PG_CPPFLAGS = -I$(LIBDIR)/include
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LIB_FLAGS += -liconv
endif
SHLIB_LINK = $(LIB_FLAGS) -L$(LIBDIR)

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)


test:
	gcc src/converter.c src/tokenizer.c tests/test_thai_parser.c $(LIB_FLAGS) -g -o tests/test_tp && ./tests/test_all.sh
