TARGET = main



SRC_AP = \
	ap/ap.cpp \

SRC_HW = \
	hw/hw.c \
	hw/core/resize.c \
	hw/driver/libgo2/display.c \
	hw/driver/libgo2/queue.c \
	hw/driver/libgo2/input.c \
	hw/driver/libgo2/audio.c \
	hw/driver/millis.c \
	hw/driver/micros.c \
	hw/driver/delay.c \
	hw/driver/hangul/PHan_Lib.c \
	hw/driver/lcd.c \
	hw/driver/button.c \
	hw/driver/joypad.c \
	hw/driver/speaker.c \

SRC_GNUBOY = \
	ap/gnuboy/cpu.c \
	ap/gnuboy/debug.c \
	ap/gnuboy/emu.c \
	ap/gnuboy/events.c \
	ap/gnuboy/exports.c \
	ap/gnuboy/fastmem.c \
	ap/gnuboy/hw_.c \
	ap/gnuboy/inflate.c \
	ap/gnuboy/keytable.c \
	ap/gnuboy/lcd_.c \
	ap/gnuboy/lcdc.c \
	ap/gnuboy/loader.c \
	ap/gnuboy/main_.c \
	ap/gnuboy/mem.c \
	ap/gnuboy/newsound.c \
	ap/gnuboy/palette.c \
	ap/gnuboy/path.c \
	ap/gnuboy/rccmds.c \
	ap/gnuboy/rcfile.c \
	ap/gnuboy/rckeys.c \
	ap/gnuboy/rcvars.c \
	ap/gnuboy/refresh.c \
	ap/gnuboy/rtc.c \
	ap/gnuboy/save.c \
	ap/gnuboy/sound.c \
	ap/gnuboy/split.c \
	ap/gnuboy/sys/orocaboy/filer.c \
	ap/gnuboy/sys/orocaboy/orocaboy.c \



SRC_FILES = \
	main.cpp	\
	$(SRC_AP) \
	$(SRC_HW) \
	$(SRC_GNUBOY) \


 INC_DIRS =	-I. \
	-I./ap \
	-I./common \
	-I./hw \
	-I./hw/driver/libgo2 \
	-I./common/hw/include \
	-I/usr/include/libdrm \


CFLAGS = -DGNUBOY_NO_MINIZIP -DGNUBOY_NO_SCREENSHOT -DIS_LITTLE_ENDIAN
LIBS = 


ALLSRC     =  $(SRC_FILES)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
ALLOBJ = $(addsuffix .o, $(ALLSRCBASE))


USERCFLAGS = -O0
LDFLAGS = -lEGL -lpthread -lrga -ldrm -lpng -lgbm -levdev -lopenal -lasound -lm


all: build
#	g++ $(CFLAGS) $(USERCFLAGS) $(ALLOBJ) $< -o $@ $(LIBS)


build: $(ALLOBJ)
	gcc $(CFLAGS) $(USERCFLAGS) $(ALLOBJ) --output $(TARGET) $(LDFLAGS) $(LIBS)

run: all
	./main

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