# saludo.s:
#
#
# retorna:
#
Imprimir por pantalla
Hola a todos!
Hello, World!
código retorno 0, programado en la penúltima línea
comprobar desde línea de comandos bash con echo $?
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
#
datos hex, octal, binario, decimal, char, string:
#
0x, 0,
0b,
díg<>0, ‘,
“”
#
ejs: 0x41, 0101, 0b01000001, 65, ‘A,
“AAA”
.section .data
# directivas comienzan por .
# no son instrucciones máquina, son indicaciones para as
# etiquetas recuerdan valor contador posiciones (bytes)
saludo:
.ascii “Hola a todos!\nHello, World!\n”
# \n salto de línea
longsaludo:
.int
.-saludo
# . = contador posic. Aritmética de etiquetas.
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text
.global _start
_start:
# cambiamos de sección, ahora emitimos código
# muestra punto de entrada a ld (como main en C)
# punto de entrada ASM (como main en C)
#
Llamada al sistema WRITE, consultar “man 2 write”
#
ssize_t write(int fd, const void *buf, size_t count);
mov $4, %eax
# write: servicio 4 kernel Linux
mov $1, %ebx
#
fd: descriptor de fichero para stdout
mov
$saludo, %ecx
#
buf: dirección del texto a escribir
mov longsaludo, %edx
# count: número de bytes a escribir
int $0x80
# llamar write(stdout, &saludo, longsaludo);
#
Llamada al sistema EXIT, consultar “man 2 exit”
#
void _exit(int status);
mov $1, %eax
#
exit: servicio 1 kernel Linux
mov $0, %ebx
# status: código a retornar (0=OK)
int $0x80
# llamar exit(0);
