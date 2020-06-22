select elocal, count(*) from encuentros
group by elocal order by elocal;

select elocal,evisitante,abs(plocal-pvisitante)  from encuentros where
abs(plocal-pvisitante)=ANY (select max(abs(plocal-pvisitante)) from encuentros);

select codj,sum(num) from faltas group by codj
having sum(num) <3 order by codj;

select * from equipos where code in
(select evisitante from encuentros where 
pvisitante =any(select max(e.pvisitante) from encuentros e));


select nombree, count(*) from equipos,encuentros
where (code=elocal and plocal>pvisitante) or (code=evisitante and pvisitante>plocal)
group by nombree having count(*) = any (select max(count(*)) from  equipos ee, 
encuentros e
where  (ee.code=e.elocal and e.plocal>e.pvisitante) or (ee.code=e.evisitante and e.pvisitante>e.plocal)
group by ee.code)

