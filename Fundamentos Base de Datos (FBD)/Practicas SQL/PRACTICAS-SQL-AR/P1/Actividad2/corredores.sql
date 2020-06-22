/*drop table equipos;
drop table paises;
drop table corredor;
drop table etapas;
drop table tiempos;
drop table tests;
drop table test_realizados;
*/

create table equipos(
    equipo# char(4) constraint equipo#_no_nulo not null
        constraint equipo#_cp primary key,
    nombreeq varchar2(30) constraint nombreeq_no_nulo not null,
    director varchar2(30) constraint director_no_nulo not null
);
create table paises(
    pais# char(4) constraint pais#_no_nulo not null
        constraint pais#_cp primary key,
    nombrep varchar2(30) constraint nombrep_no_nulo not null
);

create table corredor(
    corredor# char(4) constraint corredor#_no_nulo not null
        constraint corredor#_cp primary key,
    nombre varchar2(30) constraint nombre_no_nulo not null,
    equipo# constraint equipo#_clave_externa_equipo 
        references equipos(equipo#),
    pais# constraint pais#_clave_externa_paises
        references paises(pais#)
);

create table etapas(
    etapa# char(4) constraint etapa#_no_nulo not null
        constraint etapa#_cp primary key,
    fecha date,
    ciudad_salida varchar2(20),
    ciudad_llegada varchar2(20),
    total_km number(3,1) constraint km_positivo
        check(total_km>0)
);

create table tiempos(
    corredor# constraint corredor#_ce_corredor
        references corredor(corredor#),
    etapa# constraint etapa#_ce_etapas
        references etapas(etapa#),
    tiempo number(5,7) constraint tiempo_positivo
        check(tiempo>=0),
    
    constraint corredor#_etapa#_cp primary key(corredor#,etapa#)
);

create table tests(
    test# char(4) constraint test#_no_nulo not null
        constraint test#_cp primary key,
    denominacion varchar2(50)
);

create table test_realizados(
    corredor# char(4),
    etapa# char(4),
    resultados varchar2(15),
    test# constraint test#_clave_externa_tests
        references tests(test#),
    constraint corredor#_etapa#_test#_cp primary key(corredor#,etapa#,test#),
    constraint corredor#_etapa#_ce foreign key(corredor#,etapa#)
        references tiempos(corredor#,etapa#)
);