set ADD_FLAGS=
::set ADD_FLAGS=-march=core2
gcc	-Os -pipe %ADD_FLAGS% -Wl,--as-needed -D_GETS   input.c  -o i_gets.exe
gcc	-Os -pipe %ADD_FLAGS% -Wl,--as-needed -D_READ   input.c  -o i_read.exe
gcc	-Os -pipe %ADD_FLAGS% -Wl,--as-needed -D_PRINTF output.c -o o_printf.exe
gcc	-Os -pipe %ADD_FLAGS% -Wl,--as-needed -D_PUTS   output.c -o o_puts.exe
gcc	-Os -pipe %ADD_FLAGS% -Wl,--as-needed -D_WRITE  output.c -o o_write.exe
