<?php
	require_once('datosObject.class.inc');
	
	class claseUsuarios extends DataObject {
		protected $datos = array(
		"usuario" => "",
		"password" => "",
		"nombre" => "",
		"apellidos" => "",
		"email" => "",
		"telefono" => "",
		"nacimiento" => "",
		"intereses" => "",
		"conociste"=>"");

		/*Función para añadir un nuevo usuario a nuestro sistema*/
		public static function registroUsuario($datosUsuario){
			$conexion = parent::conectar();
			$sql1 = "INSERT INTO " . TABLA_USUARIOS . " (usuario,password,nombre,apellidos,email,telefono,nacimiento,intereses,conociste) VALUES (:usuario,:password,:nombre,:apellidos,:email,:telefono,:nacimiento,:intereses,:conociste);";
			
			try{
				$stmt = $conexion->prepare($sql1);
				
				$usuario = $datosUsuario['usuario'];
				$password = $datosUsuario['password'];
				$nombre = $datosUsuario['nombre'];
				$apellidos = $datosUsuario['apellidos'];
				$email = $datosUsuario['email'];
				$telefono = $datosUsuario['telefono'];
				$nacimiento = $datosUsuario['nacimiento'];
				$intereses = $datosUsuario['interes'];
				$conociste = $datosUsuario['conociste'];
				
				$stmt->bindParam("usuario",$usuario,PDO::PARAM_STR);
				//$pw_encriptada = hash('sha256',$pass);
				$stmt->bindParam("password",$password,PDO::PARAM_STR);
				$stmt->bindParam("nombre",$nombre,PDO::PARAM_STR);
				$stmt->bindParam("apellidos",$apellidos,PDO::PARAM_STR);
				$stmt->bindParam("email",$email,PDO::PARAM_STR);
				$stmt->bindParam("telefono",$telefono,PDO::PARAM_STR);
				$stmt->bindParam("nacimiento",$nacimiento,PDO::PARAM_STR);	//posible problema con date
				$stmt->bindParam("intereses",$intereses,PDO::PARAM_STR);
				$stmt->bindParam("conociste",$conociste,PDO::PARAM_STR);
			
			/*
				foreach($datosUsuario as $key => $value){
					if(!empty($value)){
						$stmt->bindValue(":".$key, $value,PDO::PARAM_STR);
					}else{
						$stmt->bindValue(":".$key,"",PDO::PARAM_STR);
					}
				}
			*/
				$stmt->execute();

			}catch( PDOException $e ){
				die( "Registro de usuario fallido: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
		}
		
		/*Función para hacer el login de un usuario de nuestro sistema*/
		public static function loginUsuario($usuario_email,$pass){
				$conexion = parent::conectar();
				$sql = "SELECT * FROM " . TABLA_USUARIOS . " WHERE (usuario=:usuario_email OR email=:usuario_email) AND password=:pass";
				
				try{
					$stmt = $conexion->prepare($sql);
					
					$stmt->bindParam("usuario_email",$usuario_email,PDO::PARAM_STR);
					$stmt->bindParam("pass",$pass,PDO::PARAM_STR);
					
					$stmt->execute();
					
					$contador=$stmt->rowCount();
					$fila = $stmt->fetch(); //fetch(PDO::FETCH_OBJ)
					//si existe en la bd el usuario y la contraseña
					if($contador!=0){
							//guardamos su sesión
							//$_SESSION['uid']=$fila->uid;
							return true;
					}else{
						//echo "<br><br>ERROR. Usuario o contraseña incorrectos. VUELVE A INTENTARLO";
						return false;	
					}
					
				}catch( PDOException $e ){
					die("Error en Login: " . $e->getMessage());			
				}finally{
					parent::desconectar( $conexion );				
				}	
		}
		
		
		/*Devuelve la información del usuario a través de su clave primaria*/
		public static function infoUsuario( $usuario ) {
			$conexion = parent::conectar();
			$sql = "SELECT * FROM " . TABLA_USUARIOS . " WHERE (usuario=:usuario_email OR email=:usuario_email)";
			try {
				$st = $conexion->prepare( $sql );
				$st->bindValue( ":usuario_email", $usuario, PDO::PARAM_STR );
				$st->execute();
				
				$fila = $st->fetch();	
				
				if ( $fila ) return new claseUsuarios( $fila );//$fila
				/*
				$fila = $st->fetch(PDO::FETCH_OBJ); //User data
				return $fila;
*/
			} catch ( PDOException $e ) {
				
				die( "Consulta fallada: " . $e->getMessage() );
			} finally{
				parent::desconectar( $conexion );
			}
		}
		
		/*Updatear la información del usuario a través de su clave primaria*/
		public static function updatearUsuario($usuario,$datosUsuario){
			$conexion = parent::conectar();
			$sql = "UPDATE " . TABLA_USUARIOS . " SET password= :password, nombre= :nombre,apellidos= :apellidos,email= :email,telefono= :telefono,nacimiento= :nacimiento WHERE (usuario=:usuario_email OR email=:usuario_email)";
			
			try{
				$stmt = $conexion->prepare($sql);
				
				//si no se actualiza la contraseña, guardamos la original
				if(empty($datosUsuario['password'])){
					$datosUsuario['password'] = $datosUsuario['password_anterior'];	
				}
				unset($datosUsuario['password_anterior']);//liberamos
				
				$stmt->bindValue(":usuario_email", $usuario);
						
				$password = $datosUsuario['password'];
				$nombre = $datosUsuario['nombre'];
				$apellidos = $datosUsuario['apellidos'];
				$email = $datosUsuario['email'];
				$telefono = $datosUsuario['telefono'];
				$nacimiento = $datosUsuario['nacimiento'];

				//$pw_encriptada = hash('sha256',$pass);
				$stmt->bindValue(":password",$password,PDO::PARAM_STR);
				$stmt->bindValue(":nombre",$nombre,PDO::PARAM_STR);
				$stmt->bindValue(":apellidos",$apellidos,PDO::PARAM_STR);
				$stmt->bindValue(":email",$email,PDO::PARAM_STR);
				$stmt->bindValue(":telefono",$telefono,PDO::PARAM_STR);
				$stmt->bindValue(":nacimiento",$nacimiento,PDO::PARAM_STR);	//posible problema con date
			
				$stmt->execute();

			}catch( PDOException $e ){
				die( "Actualización de usuario fallida: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
				
		}
		
		//Eliminar la cuenta del usuario
		public static function eliminarMiUsuario($usuario){
			
			$conexion = parent::conectar();
			$sql = "DELETE FROM " . TABLA_USUARIOS . " WHERE (usuario=:usuario_email OR email=:usuario_email)";
			
			try{
				$stmt = $conexion->prepare($sql);
				
				$stmt->bindValue(":usuario_email", $usuario);

				$stmt->execute();

			}catch( PDOException $e ){
				die( "Eliminar mi usuario falló: " . $e->getMessage() . " en la línea: " . $e->getLine());
			}finally{
				parent::desconectar( $conexion );
			}
			
		}
		
	}
?>
	