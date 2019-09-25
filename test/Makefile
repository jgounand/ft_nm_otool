SRC_FILE	?=
BIN_FILE	?=
INC_DIR		:= ..
LIB_DIR		:= ..
LIB_NAME	:= fts

ICFLAGS		:= $(addprefix -I, $(INC_DIR))
CFLAGS		:= -g3 -Werror
LPCFLAGS	:= $(addprefix -L, $(LIB_DIR))
LCFLAGS		:= $(addprefix -l, $(LIB_NAME))

ifeq "$(SRC_FILE)" ""
$(error not to specify a name for source file)
endif

ifeq "$(BIN_FILE)" ""
$(error not to specify a name bin file)
endif

ifneq "$(shell uname -s)" "Darwin"
CFLAGS += -no-pie
endif

$(BIN_FILE): $(SRC_FILE) ../libfts.a
	$(CC) $(ICFLAGS) $(CFLAGS) -o $@ $< $(LPCFLAGS) $(LCFLAGS)
