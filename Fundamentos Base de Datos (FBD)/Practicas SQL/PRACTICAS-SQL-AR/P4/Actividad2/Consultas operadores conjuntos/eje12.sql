--Asignaturas que est�n en el �ltimo curso

select asi# from asigna where curso>= all(select curso from asigna)
/
