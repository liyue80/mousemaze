@echo off
echo ---- gets ----
for /l %%x in (1, 1, 20) do i_gets.exe<in.txt>out.txt
echo ---- read ----
for /l %%x in (1, 1, 20) do i_read.exe<in.txt>out.txt
