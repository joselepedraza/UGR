-- Asignaturas que tienen o han tenido  matriculados a todos los alumnos de Almer�a

Select asi#,nombreas from asigna where
not exists(select dni from alumnos where
provincia='Almeria' and 
not exists (select * from matricula where codas=asi# and codal=dni))
/
