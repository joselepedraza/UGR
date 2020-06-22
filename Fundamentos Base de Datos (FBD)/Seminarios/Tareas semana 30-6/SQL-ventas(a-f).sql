a) select codpro from ventas where codpj='J1';

b) select * from ventas where cantidad>=100;

c) select nompro,nompie,nompj from proveedor, pieza, proyecto where proveedor.ciudad=pieza.ciudad and pieza.ciudad=proyecto.ciudad;

d) select nompie from pieza, proveedor, ventas where pieza.codpie=ventas.codp and 
   proveedor.codpro=ventas.codpro and proveedor.ciudad='Londres';

e) Select proveedor.ciudad,pieza.ciudad from proveedor, pieza, ventas where
   proveedor.codpro=ventas.codpro and pieza.codpie=ventas.codp;

f) Select ventas.codp from proveedor, proyecto, ventas where proveedor.codpro=ventas.codpro 
   and proyecto.codpj=ventas.codpj and proveedor.ciudad=proyecto.ciudad;