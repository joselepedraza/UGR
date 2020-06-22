g.-Select DISTINCT ventas.codpj from proveedor,ventas,proyecto where proveedor.codpro=ventas.codpro and
   proyecto.codpj=ventas.codpj and proveedor.ciudad<>proyecto.ciudad

h.- Select ciudad from pieza
    union
    Select ciudad from proyecto

i.- Select ciudad from proveedor
    minus
    Select ciudad from pieza

j.- Select ciudad from proveedor
    intersect
    Select ciudad from pieza

k.- Select DISTINCT ventas.codpj from ventas, ventas ven 
    where ven.codp=ventas.codp and ven.codpro='S1'


