---Alumnos entre 20 y 30 a�os provinientes de las provincias de Granada, Jaen o Almer�a

select dni,nombre,ape1,ape2 from alumnos
    where    edad between 20 and 30 and   
     provincia in  ('Jaen','Granada','Almeria') order by ape1,ape2,nombre
/
