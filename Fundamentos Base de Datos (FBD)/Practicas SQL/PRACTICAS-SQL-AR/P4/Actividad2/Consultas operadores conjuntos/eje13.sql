--Alumnos matriculados en asignaturas del �ltimo curso

select distinct dni from matricula where codasi# in (select asi# from asigna where
curso >=all (select asi.curso from asigna asi))
/

-- Asignaturas del �ltimo curso
select asi# from asigna where curso>=all(Select asi.curso from asigna asi)
/

---Alumnos amtriculados en asignaturas del �ltimo curso una vez que se sabe cuales son.  (Mal enfoque para resolver la consulta. Se necesitan dos sentencias)
Select distinct dni from matricula where codasi# in ('alg','bda','mab2')
/