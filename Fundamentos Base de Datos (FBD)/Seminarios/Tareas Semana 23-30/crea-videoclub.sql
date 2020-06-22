Create table artista(NombreA varchar(20) primary key, Pais varchar(10),
Edad number(2),Historal varchar(200));

Create table Director(NombreA varchar(20) primary key references artista);

Create table Tema(Tema# Varchar(20) primary key);

Create table Pelicula(Pel# primary key varchar(5), titulo varchar(20) not null, año date not null,
tema varchar(20) references Tema on delete set null,
nombre varchar(20) references director on delete set null, unique (titulo,año);

Create table Actor(Nombrea varchar(2) primary key references artista);

Create table Actua(Pel# varchar(5) references pelicula,
nombrea varchar(20) references actor, primary key(Pel#,nombrea));

Create table cliente(DNI varchar(9), Nombreu varchar(30) not null unique, 
direccion varchar(40), telefono number(9));

Create table cinta(Pel# varchar(5) primary key, cinta# varchar(3),tipo varchar(5), 
primary key(Pel#,cinta#));

Create table prestamo(Pel# varchar(5), cinta# varchar(3), fecha date,
DNI varchar(9) references cliente not null, primary key(Pel#,cinta#,fecha), 
FOREIGN KEY (Pel#,cinta#) references cinta);
