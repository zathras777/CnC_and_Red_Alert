# TODO: proper targets
include_directories(../WIN32LIB/INCLUDE ../WINVQ/INCLUDE)
add_compile_definitions(-DWIN32) # hopefully easier than DOS

# wrappers/workarounds
include_directories(../port)
add_compile_definitions(-D__cdecl= -D__far= -Dcdecl= -Dfar=)

add_library(jshell STATIC
	rotbmp.cpp
	sprite.cpp
)

add_library(tech STATIC
    lzo1x_c.cpp
	lzo1x_d.cpp
	lzopipe.cpp
	lzostraw.cpp
	lzw.cpp
	lzwpipe.cpp
	lzwstraw.cpp
	buff.cpp
	bench.cpp
	rect.cpp
	mpu.cpp
	readline.cpp
	pkpipe.cpp
	pkstraw.cpp
	xstraw.cpp
	xpipe.cpp
	rndstraw.cpp
	pk.cpp
	blwstraw.cpp
	straw.cpp
	b64straw.cpp
	lcwstraw.cpp
	crcstraw.cpp
	shastraw.cpp
	ramfile.cpp
	ini.cpp
	lcwpipe.cpp
	#lcwcomp.asm
	lcw.cpp
	crcpipe.cpp
	shapipe.cpp
	pipe.cpp
	blowpipe.cpp
	b64pipe.cpp
	base64.cpp
	fixed.cpp
	mixfile.cpp
	cdfile.cpp
	bfiofile.cpp
	rawfile.cpp
	mp.cpp
	int.cpp
	monoc.cpp
	random.cpp
	rgb.cpp
	hsv.cpp
	#palette.obj ?
	blowfish.cpp
	sha.cpp
	crc.cpp
	sendfile.cpp
)