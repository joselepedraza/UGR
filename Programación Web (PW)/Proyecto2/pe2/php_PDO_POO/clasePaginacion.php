<?php
	require_once('datosObject.class.inc');
	
	class clasePaginacion extends DataObject {
	
		public static function contarRegistros($tabla){
			$conexion = parent::conectar();
			$sql = "SELECT COUNT(*) FROM " . $tabla . ";";
			try{
				
				$st = $conexion->prepare($sql);
				$st->execute();
				
				$n_registros = $st->fetchAll();
				
				return $n_registros['0']['0'];	//Al ser un array lo que devuelve de la consulta, debemos seleccionar la primera posición en donde estará reflejado el valor de "count"
				
			}catch( PDOException $e ){
				die( "Contar registros fallido: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}	
			
		}
		
		public static function registrosPagina($pagina, $tabla){
			$conexion = parent::conectar();
			
			if (($pagina) > 0){
				$sql = "SELECT * FROM " . $tabla . " LIMIT " . (($pagina -1)*TAMANIO_PAGINA) . "," . TAMANIO_PAGINA . ";";
			}else{
				$sql = "SELECT * FROM " . $tabla . ";";
			}
			//$sql = "SELECT *  FROM " . $tabla . " LIMIT " . TAMANIO_PAGINA . " OFFSET " . ($pagina * TAMANIO_PAGINA) . ";";
			
			/*		
    		-LIMIT("empezar desde" en la version corta): Limita el máximo de resultados que te devuelve en cada consulta. Para este ejemplo usamos 18 registros.
				(($pagina -1)*TAMANIO_PAGINA) --> pagina-1 para que cuando esté en la primera página se rescate desde el primer elemento (0 de la BD) al 3,por ejemplo; ó si estuviesemos en la página 3(mostrando 3 registros por página) empecemos a mostrar desde el registro 6 al 9.
    		-OFFSET: Especifica a partir de qué registro quiero que me muestre los resultados. Como en cada página me ha de mostrar, por ejemplo, 18 resultados, si estoy en la página 5 me ha de mostrar esos 18 resultados partiendo del registro 90 (hasta el 108), y así sucesivamente.
			*/
			
			try{
				
				$st = $conexion->prepare($sql);
				$st->execute();
				
				$registros = $st->fetchAll();
				
				return $registros;
				
			}catch( PDOException $e ){
				die( "Recuperacion registros fallido: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}	
				
			
		}
	}
?>
	