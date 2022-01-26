<?php
    session_start();
	
	require_once("php_PDO_POO/claseSecciones.php");
	
	if($_SESSION["usuario"]!='admin'){
		header("Location: index.php");
	}
	else{
		if(isset($_GET["id"])){
			//recuperamos los datos actuales de la sección (seleccionada con el botón actualizar
			$id=$_GET['id'];
			
			$seccion = claseSecciones::infoSeccion($id);
			
			$nombre = $seccion->devolverValor("nombre");
			$items = $seccion->devolverValor("items");
			$titulo = $seccion->devolverValor("titulo");
			
		}
		else{
			$nombre = '';
			$titulo = '';
			$items = '';	
		}
	}

?>

<!doctype html>
<html lang="es">
	<head>
		<meta charset="utf-8">
		<meta name="author" content="Jose Luis Pedraza Román">
		<title> ¡¡AutoShop!! </title>
		<link  rel="icon" href="Imagenes/icono.jpg" type="image/jpg">
		<link rel="stylesheet" type="text/css" href="style_index.css"/>
        <script src="./js/validadorUpdateoSeccion.js"></script>
        <script src="./js/validadorLogin.js"></script>
	</head>
	<body>
		  
    
		<header>
        	
			<a href="index.php">
					<img id="icono" src="Imagenes/Logo-autoshop.jpg" alt="logo" width="275" height="125"/>
			</a>
            
			<h1>&ensp;&ensp;¡¡Bienvenido a AutoShop!!&ensp;&ensp;</h1>
			<?php
					if(!empty($_SESSION['usuario'])){
						if ($_SESSION['usuario']=='admin'){
							echo '<aside class="registrado">
								<table border="2">
									<tr><th> <strong>  Usuario: ' . $_SESSION['usuario'] . '</strong> </th>
									</tr>
									<tr><th> <a href="registro_seccion.php"> REGISTRAR SECCIÓN </a> <tr><th>
									<tr><th> <a href="registro_item.php"> REGISTRAR VEHÍCULO </a> <tr><th>					
									<tr><th> <a href="updatear_perfil.php"> ACTUALIZAR PERFIL </a> <tr><th>
									
								</table>
								
								<p><a href="cerrar_sesion.php"> LOGOUT </p></a>
			
							</aside>';						
							
						}
						else{
							echo '<aside class="registrado">
								<table border="2">
									<tr><th> <strong>  Usuario: ' . $_SESSION['usuario'] . '</strong> </th>
									</tr>
									<tr><th> <a href="eliminar_perfil.php">  BORRAR PERFIL </a> <tr><th>
								</table>
								
								<p><a href="cerrar_sesion.php"> LOGOUT </p></a>
			
							</aside>';
							
						}
								
					}
					else{
						echo '
							<aside>
            	  
								<form name="comprueba_login" id="comprueba_login" method="POST" action="comprueba_login.php" autocomplete="on" onsubmit="return validarFormularioLogin();">
									
									<label for="user"> Usuario: </label> <br> <!--&nbsp;&nbsp;&nbsp;&nbsp;-->
									<input name="usuario" id="user" type="text" placeholder="nombre de usuario"/>
									<!--<input name="usuario" id="user" type="text" placeholder="nombre de usuario" required />-->
									
									<br><br>
									<label for="password"> Contraseña: </label> <br>
									<input name="password" id="password" type="password" />
									<!--<input name="password" id="password" type="password" pattern=".{8,}" required /> placeholder="al menos 8 caracteres"-->
									<p><a href="recuperar_contraseña.html">¿Has olvidado tu contraseña?</a></p>
									
									<input type="submit" id="btn_submit" value="Enviar"> &nbsp;
									<a href="registro_usuario.php"> Registro gratuito </a>
								</form>
							</aside>
						';	
					}
				
			?>    
            
            
            
		</header>
		
         <nav id="navigation">
			<?php
                    require_once("php_PDO_POO/clasePaginacion.php");
					require_once("php_PDO_POO/claseSecciones.php");
					
					$contador_registros = clasePaginacion::contarRegistros(TABLA_SECCIONES);
					$secciones = clasePaginacion::registrosPagina(0, TABLA_SECCIONES);
					//$secciones = claseSecciones::datosSecciones();
					
			?>

        	<article class="menu">
            	<a href="#navigation" class="open" id="lbar"> Menú </a>
                <a href="#" class="close" > Cerrar </a>
            </article>
        	
            <ul id="bar">
           
                <?php
                    foreach($secciones as $seccion){           
                        echo '<a class="lbar" href="' . $seccion['nombre'] . '.php"><li class="linksBar">' . $seccion['titulo'] . '</li></a>';
                    }
                ?>
            </ul> 
		</nav>
            
		<hr>
		<main>
        	<?php 						
				//secciones para guardar toda la lista de secciones a modificar/borrar
				$secciones = claseSecciones::datosSecciones();
			
			?>
        
        	<h2 class="tituloseccion"> Administrador de secciones</h2>
			<hr>
			<section id="formulario">
				<form action="procesar_act_seccion.php" name="form_updatear_seccion" id="reg_usuario" method="POST" autocomplete"on" onsubmit="return validarActualizarSeccion();">

                    <table border="1">
                    <tr >
                      <td class="primera_fila">id</td>
                      <td class="primera_fila">Nombre del fichero .php</td>
                      <td class="primera_fila">Titulo visible</td>
                      <td class="primera_fila">Items</td>
                    </tr> 
                   
                    <!--registros para borrar o seleccionar para actualizar-->
                     <?php //creamos una linea para cada registro en la tabla secciones
						foreach($secciones as $seccion){
					 ?>
                        <tr>
                            <td><?php echo $seccion->id?></td>
                            <td><?php echo $seccion->nombre?></td>
                            <td><?php echo $seccion->titulo?></td>
                            <td><?php echo $seccion->items?></td>
                            
                            <!--Pasasmos por la url el id a borrar segun el boton de borrar que hayamos pulsado-->
                            <td class="bot"> <a href="procesar_borrar_seccion.php?id=<?php echo $seccion->id;?>"> <input type='button' name='del' id='del' value='Borrar'></a></td>
                            
                            <!--Hacemos lo mismo con el botón actualizar para que mande a la url el id, se recargue la pagina y podamos actualizar los datos de la seccion correspondiente -->
                            <td class='bot'> <a href="updatear_secciones.php?id=<?php echo $seccion->id;?> "><input type='button' name='up' id='up' value='Actualizar'></a></td>
                        </tr>
					<?php		
						}
                	?>
                    
                    <!--registro a actualizar  -->
                    <tr>
                      <td><input type='text' id='id' name='id' size='10' value="<?php 
					  	if(isset($_GET["id"])){
					  		echo $id;
						}
					  	
					  ?>" readonly/></td>	<!--no poner "disabled" porque no lo manda por post...-->
                      <td><input type='text' id='nombre' name='nombre' value="<?php echo $nombre;?>"/></td>
                      <td><input type='text' id='titulo' name='titulo' value="<?php echo $titulo;?>"/></td>
                      <td><input type='text' name='items' id='items' value="<?php echo $items;?>"/></td>
                      
                      <td colspan=2 class='bot'><input type="submit" name='btn_updatearSeccion' id='btn1' value='Guardar cambios'></td></td>
                     </tr>
                  </table>
				</form>
			<section>	
		</main>
        
		<footer>
				<figure>
					<img src="Imagenes/foto4.jpg" alt="logofooter" width="200" height="70">
				</figure>
		
				<address>
				
				Avd/ Villanueva, 06005 Badajoz, Spain
				</address>
				
				<p><a href="Contacto.html"> Contacto </a><p>
				
				<p><a href="warning.php"> AVISO LEGAL </a><p>
		</footer>
		
	</body>
</html>