##############################################################################
# ejecutar con: gdb -batch -x antonio.gdb
##############################################################################

file antonio
set write on
b main
r

echo Comprobar original:\n
x/3i Comprobar
# xor %eax, %eax  31 c0
# inc %eax        40
# ret             c3
set *(int*) Comprobar = 0xc340c031

echo Comprobar modificado:\n
x/3i Comprobar

b *main + 233
c
p $eax
p $edx

echo main original:\n
x/1i *main + 180
x/1i *main + 233
x/1i *main + 270
set *(char*) (*main + 180) = 0xeb
set *(char*) (*main + 233) = 0xeb
set *(char*) (*main + 270) = 0xeb

echo main modificado:\n
x/1i *main + 180
x/1i *main + 233
x/1i *main + 270

c

