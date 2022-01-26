<?php
	require_once('datosObject.class.inc');
	
	class claseSecciones extends DataObject {
		protected $datos = array(
		"id"=>"",
		"nombre" => "",
		"items"=>"",
		"titulo"=>"");

		/*Función para añadir una nueva sección a nuestro sistema*/
		public static function registroSeccion($datosSeccion){
			$conexion = parent::conectar();
			$sql1 = "INSERT INTO " . TABLA_SECCIONES . " (id,nombre,items,titulo) VALUES (DEFAULT,:nombre,:items,:titulo);";
			
			try{
				$stmt = $conexion->prepare($sql1);

				$nombre = $datosSeccion['nombre'];
				$items = $datosSeccion['items'];
				$titulo = $datosSeccion['titulo'];
						
				$stmt->bindParam("nombre",$nombre,PDO::PARAM_STR);
				$stmt->bindParam("items",$items,PDO::PARAM_STR);
				$stmt->bindParam("titulo",$titulo,PDO::PARAM_STR);
				
				$stmt->execute();

			}catch( PDOException $e ){
				die( "Registro de sección fallido: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
		}
			
		/*Devuelve la información de la sección a través de su clave primaria*/
		public static function infoSeccion($id) {
			$conexion = parent::conectar();
			$sql = "SELECT id,nombre,items,titulo FROM " . TABLA_SECCIONES . " WHERE id=:id";
			try {
				$st = $conexion->prepare( $sql );
				$st->bindValue( ":id", $id, PDO::PARAM_INT);
				$st->execute();
				
				$fila = $st->fetch();	
				
				if ( $fila ) return new claseSecciones( $fila );
				
			} catch ( PDOException $e ) {
				
				die( "Consulta fallada: " . $e->getMessage() . " en la línea: " . $e->getLine()) ;
			} finally{
				parent::desconectar( $conexion );
			}
		}
		
		/*Devuelve todas las secciones de la tabla (obj para updateo y borrado)*/
		public static function datosSecciones() {
			$conexion = parent::conectar();
			$sql = "SELECT * FROM " . TABLA_SECCIONES;
			try {
				$st = $conexion->prepare( $sql );
				$st->execute();
				
				$registros = $st->fetchAll(PDO::FETCH_OBJ);
				
				return $registros;

			} catch ( PDOException $e ) {
				
				die( "Consulta fallada: " . $e->getMessage() );
			} finally{
				parent::desconectar( $conexion );
			}
		}
		
				
		/*Updatear la información de la sección a través de su clave primaria*/
		public static function updatearSeccion($datosSeccion){
			$conexion = parent::conectar();
			$sql = "UPDATE " . TABLA_SECCIONES . " SET nombre= :nombre, items= :items, titulo= :titulo WHERE id=:id";
			
			try{
				$stmt = $conexion->prepare($sql);
				
				$id = $datosSeccion['id'];
				
				$stmt->bindValue(":id", $id, PDO::PARAM_INT);
									
				$nombre = $datosSeccion['nombre'];
				$items = $datosSeccion['items'];
				$titulo = $datosSeccion['titulo'];
				
				$stmt->bindValue(":nombre",$nombre,PDO::PARAM_STR);
				$stmt->bindValue(":items",$items,PDO::PARAM_STR);
				$stmt->bindValue(":titulo",$titulo,PDO::PARAM_STR);
			
				$stmt->execute();

			}catch( PDOException $e ){
				die( "Actualización de sección fallida: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
				
		}
		
		//Eliminar sección
		public static function eliminarSeccion($id){
			
			$conexion = parent::conectar();
			$sql = "DELETE FROM " . TABLA_SECCIONES . " WHERE id=:id";
			
			try{
				$stmt = $conexion->prepare($sql);
				
				$stmt->bindValue(":id", $id);

				$stmt->execute();

			}catch( PDOException $e ){
				die( "Eliminar sección falló: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
			
		}
		
	}
?>
	