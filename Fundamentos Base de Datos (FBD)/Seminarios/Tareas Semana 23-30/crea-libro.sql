create table libro (L# varchar(5) primary key, Titulo varchar(30) not null)

create table ejemplar(L# varchar(5) references libro,Eje# varchar(3), 
primary Key (l#,Eje#));

create table tema(tema# varchar(5) primary key, descr varchar(30));

create table trata(l# varchar(5) references libro, tema# varchar(5) 
references tema, primary key (l#,tema#));

create table autor(DNIA varchar(9) primary key, NombreA varchar(30));

create table escribe(DNIA varchar(9) references autor,
l#  varchar(5) references libro, primary key(DNIA,l#))

create table usuario(DNI varchar(9) primary key, 
NombreU varchar(30) not null unique);

create table prestado(l# varchar(5),Eje# varchar(3), Dini date, 
DNI varchar(9) not null references usuario, Ndias number(2), 
primary key(l#,Eje#,Dini), foreing key(l#,Eje#) references Ejemplar,
(Dini,DNI) unique)





