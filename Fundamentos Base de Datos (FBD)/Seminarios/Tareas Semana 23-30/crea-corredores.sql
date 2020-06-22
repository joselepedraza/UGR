Create table Paises(cod_pais varchar(5) primary key, nomb_pais varchar(20) not null unique );

Create table Equipos(cod_eq varchar(5) primary key, nombr_eq varchar(20) not null unique, 
director varchar(30));

Create table Corredores(No_corre varchar(5) primary key, cod_eq varchar(5) references Equipos, 
cod_pais varchar(5) references paises on delete set null, nom_corre varchar(30) not null unique);

Create table etapas(No_etapa varchar(5) primary key, fecha date not null, ciusal varchar(10) not null,
ciulle varchar(10) not null, Kms number(3));

Create table tiempos(No_corre varchar(5) references corredores, No_etapa varchar(5) references etapas, 
tiempo number(5) not null,
primary key (No_corre,No_etapa));

Create table test(Test_id varchar(5) primary key, denominacion varchar(20) unique not null);

Create table T_realizados(No_corre varchar(5), No_etapa varchar(5), 
test_id varchar(5) references test, result varchar(10), 
primary key(No_corre,No_etapa,test_id), Foreign key(no_corre,No_etapa) references tiempos);