/*
Una tienda de licores es frecuentada por varios clientes, que periódicamente la visitan para comprar
botellas de licor. El tendero dispone de poco espacio para almacenar botellas (sólo le caben 30 botellas
de licor). Además sólo puede atender a los clientes de uno en uno (que sólo pueden comprar una
botella cada vez). Para poder contentar a la mayor cantidad de clientes, no permite vender dos botellas
seguidas al mismo cliente, pero cuando quedan menos de 5 botellas se ignora la norma y puede
comprar cualquiera. Cuando se vacía el almacén, y sólo en ese momento, el propio tendero rellena el
almacén y vuelve a impedir comprar dos veces seguidas al mismo cliente (otra vez hasta que queden
menos de 5 botellas).
Implementar los procesos Cliente(i) y Tendero usando paso de mensajes síncrono de forma que no
haya interbloqueo y se cumplan las características del problema. Suponed que el almacén está lleno
inicialmente, que el índice en el vector de procesos es su nombre y que hay N clientes: Cliente(0),
Cliente(1), … Cliente(N-1).
*/



process Cliente[i : 0..N-1]
int peticion
int botella
begin
	while true do begin
		s_send(peticion, Tendero)
		receive(botella, Tendero)
	end
end

process Tendero

int nBotellas = 30
int ultimocliente = -1
int peticion


begin
	while true do begin

		select

			for i=0 to N-1
			when nBotellas >= 5 and ultimocliente != i receive(peticion, Cliente[i]) do

				// hay 5 o mas botellas
				ultimocliente = i
				nBotellas = nBotellas -1
				send(nBotellas, Cliente[i])

			when nBotellas<5 and nBotellas>0 receive(peticion, Cliente[i]) do

				// hay menos de 5 botellas
				nBotellas = nBotellas-1
				send(nBotellas, Cliente[i])

			when nBotellas == 0 do

				// rellenamos
				ultimocliente = -1
				nBotellas = 30


		end
	end
end


