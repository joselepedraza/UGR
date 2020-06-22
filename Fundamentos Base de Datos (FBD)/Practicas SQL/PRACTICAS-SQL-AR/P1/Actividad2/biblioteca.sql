/*drop table autor;
drop table ejemplar;
drop table libro;
drop table tema;
drop table usuario;*/

create table autor(
    autor# char(4) constraint autor#_no_nulo not null
        constraint autor#_clave_primaria primary key,
    nomautor varchar2(30) constraint nomautor_no_nulo not null,
    nacionalidad varchar2(15)
);

create table libro(
    libro# char(4) constraint libro#_clave_primaria primary key,
    titulo varchar2(30) constraint titulo_no_nulo not null
);

create table escribe(
    autor# constraint autor#_clave_externa_aut 
        references autor(autor#),
    libro# constraint libro#_clave_externa_lib
        references libro(libro#),
        
    constraint autor#_libro#_clave_primaria primary key(autor#,libro#)

);

create table ejemplar(
    libro# constraint libro#_clave_externa_libro
        references libro(libro#),
    copia# char(4) constraint copia#_no_nulo not null,
    
    constraint libro#_copia#_clave_primaria primary key(libro#,copia#)
);

create table tema(
    tipo char(4) constraint tipo_clave_primaria primary key,
    descripcion varchar2(100) constraint descripcion_no_nulo not null
);

create table trata(
    libro# constraint libro#_clave_externa_libr
        references libro(libro#),
    tipo constraint tipo_clave_externa_tema
        references tema(tipo),
    
    constraint libro#_tipo_clave_primaria primary key(libro#,tipo)
);

create table usuario(
    dni char(8) constraint dni_clave_primaria primary key,
    nombreu varchar2(30) constraint nombreu_no_nulo not null
);


create table historico_prestamos(
    fecha date constraint fecha_no_nulo not null,
    dni constraint dni_clave_externa_usuario
        references usuario(dni),
    libro# char(4) not null,
    copia# char(4) not null,
    constraint fecha_dni_clave_primaria primary key(fecha,dni),
    constraint libro#_copia#_fecha_cc unique(libro#,copia#,fecha),
    constraint libro#_copia#_ce foreign key(libro#,copia#) references ejemplar(libro#,copia#)
);