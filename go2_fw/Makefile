TARGET = main



SRC_AP = \
	ap/ap.cpp \

SRC_HW = \
	hw/hw.c \
	hw/driver/libgo2/display.c \
	hw/driver/libgo2/queue.c \
	hw/driver/millis.c \
	hw/driver/delay.c \
	hw/driver/hangul/PHan_Lib.c \
	hw/driver/lcd.c \

SRC_FILES = \
	main.cpp	\
	$(SRC_AP) \
	$(SRC_HW) \


 INC_DIRS =	-I. \
	-I./ap \
	-I./common \
	-I./hw \
	-I./hw/driver/libgo2 \
	-I./common/hw/include \
	-I/usr/include/libdrm \


CFLAGS = 
LIBS = 


ALLSRC     =  $(SRC_FILES)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
ALLOBJ = $(addsuffix .o, $(ALLSRCBASE))


USERCFLAGS = -O0
LDFLAGS = -lEGL -lpthread -lrga -ldrm -lpng -lgbm


all: build
#	g++ $(CFLAGS) $(USERCFLAGS) $(ALLOBJ) $< -o $@ $(LIBS)


build: $(ALLOBJ)
	gcc $(CFLAGS) $(USERCFLAGS) $(ALLOBJ) --output $(TARGET) $(LDFLAGS) $(LIBS)



# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING) $$< to $$@
	gcc -c $$(CFLAGS) $(INC_DIRS) $(USERCFLAGS) $$< -o $$@ $$(LIBS)
endef
$(foreach src, $(SRC_FILES), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 




clean: clean_list

clean_list :
	@echo $(MSG_CLEANING)
	rm -f $(TARGET)
	rm -f $(TARGET).sym
	rm -f $(TARGET).lss
	rm -f $(ALLOBJ)
	rm -f $(LSTFILES)
	rm -f $(DEPFILES)