@echo off
echo ---- printf ----
for /l %%x in (1, 1, 20) do o_printf.exe<in.txt>out.txt
echo ---- puts ----
for /l %%x in (1, 1, 20) do o_puts.exe<in.txt>out.txt
echo ---- write ----
for /l %%x in (1, 1, 20) do o_write.exe<in.txt>out.txt
