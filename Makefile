include platform.mk

SKYNET_BUILD_PATH ?= .

CFLAGS = -g -O2 -Wall -I$(LUA_INC) $(MYCFLAGS)

# lua
LUA_STATICLIB := 3rd/lua/liblua.a
LUA_LIB ?= $(LUA_STATICLIB)
LUA_INC ?= 3rd/lua

$(LUA_STATICLIB) :
	cd 3rd/lua && $(MAKE) CC='$(CC) -std=gnu99' $(PLAT)

CQ_SRC = cq_main.c


# 主程序
all : \
	$(SKYNET_BUILD_PATH)/cq

$(SKYNET_BUILD_PATH)/cq :  $(foreach v, $(CQ_SRC), src/$(v)) $(LUA_LIB) $(MALLOC_STATICLIB)
	$(CC) $(CFLAGS) -o $@ $^ -Isrc -I$(JEMALLOC_INC) $(LDFLAGS) $(EXPORT) $(CQ_LIBS) $(SKYNET_DEFINES)
	

clean :


cleanall : clean
ifneq (,$(wildcard 3rd/jemalloc/Makefile))
	cd 3rd/jemalloc && $(MAKE) clean && rm Makefile
endif
	cd 3rd/lua && $(MAKE) clean
	rm -f $(LUA_STATICLIB)