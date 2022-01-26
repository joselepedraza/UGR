<?php
	require_once('datosObject.class.inc');
	
	class claseItems extends DataObject {
		protected $datos = array(
		"url_img" => "",
		"nombre" => "",
		"precio" => "",
		"kilometraje" => "",
		"potencia" => "",
		"anio" => "",
		"ubicacion" => "");

		/*Función para añadir un nuevo item a nuestro sistema*/
		public static function registroItem($datosItem){
			$conexion = parent::conectar();
			$sql1 = "INSERT INTO " . TABLA_ITEMS . " (url_img,nombre,precio,kilometraje,potencia,anio,ubicacion) VALUES (:url_img,:nombre,:precio,:kilometraje,:potencia,:anio,:ubicacion);";
			
			try{
				$stmt = $conexion->prepare($sql1);
				
				$url_img = $datosItem['url_img'];
				$nombre = $datosItem['nombre'];
				$precio = $datosItem['precio'];
				$kilometraje = $datosItem['kilometraje'];
				$potencia = $datosItem['potencia'];
				$anio = $datosItem['anio'];
				$ubicacion = $datosItem['ubicacion'];
				
				$stmt->bindParam("url_img",$url_img,PDO::PARAM_STR);
				$stmt->bindParam("nombre",$nombre,PDO::PARAM_STR);
				$stmt->bindParam("precio",$precio,PDO::PARAM_INT);
				$stmt->bindParam("kilometraje",$kilometraje,PDO::PARAM_INT);
				$stmt->bindParam("potencia",$potencia,PDO::PARAM_INT);
				$stmt->bindParam("anio",$anio,PDO::PARAM_INT);
				$stmt->bindParam("ubicacion",$ubicacion,PDO::PARAM_STR);

				$stmt->execute();

			}catch( PDOException $e ){
				die( "Registro de usuario fallido: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
		}
		
		/*Devuelve la información del item a través de su clave primaria*/
		public static function infoItem( $url_img_item ) {
			$conexion = parent::conectar();
			$sql = "SELECT * FROM " . TABLA_ITEMS . " WHERE url_img=:url_img_item";
			try {
				$st = $conexion->prepare( $sql );
				$st->bindValue( ":url_img_item", $url_img_item, PDO::PARAM_STR );
				$st->execute();
				
				$fila = $st->fetch();	
				
				if ( $fila ) return new claseItems( $fila );

			} catch ( PDOException $e ) {				
				die( "Consulta fallada: " . $e->getMessage() );
			} finally{
				parent::desconectar( $conexion );
			}
		}
		
		/*Updatear la información del item a través de su clave primaria (FUNCIONALIDAD NO DESARROLLADA POR EL MOMENTO)*/
		public static function updatearItem($url_img_item,$datosItem){
			$conexion = parent::conectar();
			$sql = "UPDATE " . TABLA_ITEMS . " SET nombre= :nombre,precio= :precio,kilometraje= :kilometraje,potencia= :potencia,anio= :anio,ubicacion= :ubicacion WHERE url_img=:url_img_item";
			
			try{
				$stmt = $conexion->prepare($sql);
				
				$stmt->bindValue(":url_img", $url_img_item);
						
				$nombre = $datosItem['nombre'];
				$precio = $datosItem['precio'];
				$kilometraje = $datosItem['kilometraje'];
				$potencia = $datosItem['potencia'];
				$anio = $datosItem['anio'];
				$ubicacion = $datosItem['ubicacion'];
				
				$stmt->bindParam("nombre",$nombre,PDO::PARAM_STR);
				$stmt->bindParam("precio",$precio,PDO::PARAM_INT);
				$stmt->bindParam("kilometraje",$kilometraje,PDO::PARAM_INT);
				$stmt->bindParam("potencia",$potencia,PDO::PARAM_INT);
				$stmt->bindParam("anio",$anio,PDO::PARAM_INT);
				$stmt->bindParam("ubicacion",$ubicacion,PDO::PARAM_STR);
			
				$stmt->execute();

			}catch( PDOException $e ){
				die( "Actualización de item fallida: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
				
		}
		
		//Eliminar Item a través de su clave primaria (FUNCIONALIDAD NO DESARROLLADA POR EL MOMENTO)
		public static function eliminarItem($url_img_item){
			
			$conexion = parent::conectar();
			$sql = "DELETE FROM " . TABLA_ITEMS . " WHERE url_img=:url_img_item";
			
			try{
				$stmt = $conexion->prepare($sql);
				
				$stmt->bindValue(":url_img_item", $url_img);

				$stmt->execute();

			}catch( PDOException $e ){
				die( "Eliminar item falló: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
			
		}
		
	}
?>
	