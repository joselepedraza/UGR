<?php
    session_start();
?>


<!doctype html>
<html lang="es">
	<head>
		<meta charset="utf-8">
		<meta name="author" content="Jose Luis Pedraza Román">
		<title> ¡¡AutoShop!! </title>
		<link  rel="icon" href="Imagenes/icono.jpg" type="image/jpg">
		<link rel="stylesheet" type="text/css" href="style_index.css"/>
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
									<tr><th> <a href="updatear_perfil.php"> ACTUALIZAR PERFIL </a> <tr><th>
									<tr><th> <a href="registro_item.php"> REGISTRAR VEHÍCULO </a> <tr><th>
									<tr><th> <a href="registro_seccion.php"> GESTIONAR SECCIONES </a> <tr><th>
								</table>
								
								<p><a href="cerrar_sesion.php"> LOGOUT </p></a>
			
							</aside>';						
							
						}
						else{
							echo '<aside class="registrado">
								<table border="2">
									<tr><th> <strong>  Usuario: ' . $_SESSION['usuario'] . '</strong> </th>
									</tr>
									<tr><th> <a href="updatear_perfil.php"> ACTUALIZAR PERFIL </a> <tr><th>
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
        
        
        
        
		<main>
			<?php
                /*CALCULOS PAGINACIÓN*/
                require_once("php_PDO_POO/clasePaginacion.php");
                
                //obtenemos el parámetro que nos dice en qué página estamos actualmente
                
                $pagina=1;	//inicializamos a la primera página por defecto
                
                if(array_key_exists('pag',$_GET)){	//si el valor pag existe en nuestra URL significa que estamos en una página específica (no la primera), es decir, ya se ha pulsado en alguna pagina
                    $pagina = $_GET['pag'];					
                }

				//calculamos el número de registros respecto de la página
                $contador_registros = clasePaginacion::contarRegistros(TABLA_ITEMS);
                
                //ya sabemos en qué página estamos en cada momento y cuántos registros tenemos en total
				
				$max_num_paginas = ceil($contador_registros/TAMANIO_PAGINA);//dividimos el contador del total de registros por el numero de registros que queremos por página // con intval no redondea correctamente, por eso usamos ceil
				
				//obtenemos el segmento paginado que corresponde con el número de página actual
				$segmento = clasePaginacion::registrosPagina($pagina, TABLA_ITEMS);
            ?>
           <hr>
           <h2 class="tituloseccion"> SEGUNDA MANO </h2>

           <hr>
           <!--Código paginación al principio de la sección (y al final) -->
           <section class="paginacion">
                <ul>
                    <?php
                        for ($i=0; $i < $max_num_paginas; $i++){
							if ($pagina == $i+1){
								//con ?pag hacemos que el valor vaya por la url
								echo '<li><a id="active" class="lbar" href="seccion1.php?pag=' . ($i + 1) . '">' . ($i + 1) . '</a></li>';
							} 
							else{
								echo '<li><a class="lbar" href="seccion1.php?pag=' . ($i + 1) . '">' . ($i + 1) . '</a></li>';
							}
							
                        }
                    
                    ?>
                </ul>
            </section>
           <hr>
           
            <section id="segundamano">
       			<?php
					foreach ($segmento as $item){
				?>
                    <article class="img_card">               
                        <a href="item1.php">
                         <table border="1">
                            <tr>
                                <th rowspan="6">
                                        <img src="<?php echo $item['url_img']?>" alt="coche1" width="275" height="175">
                                </th>
                                <td><h3><strong><?php echo $item['nombre'] ?></strong></h3></td>
                            </tr>
                            <tr>
                                <td><?php echo $item['precio'] ?> € </td>
                            </tr>
                            <tr>
                                <td><?php echo $item['kilometraje'] ?> KM </td>
                            </tr>
                            <tr>
                                <td><?php echo $item['potencia'] ?> CV</td>
                            </tr>
                            <tr>
                                <td>Año <?php echo $item['anio'] ?> </td>
                            </tr>
                            <tr>
                                <td><?php echo $item['ubicacion'] ?></td>
                            </tr>
                        </table>
                        </a>
                    </article>
                <?php
					}
				?>
                
            </section>
            <hr>        
            
            <!--Código paginación al final de la sección (y al principio) -->
           <section class="paginacion">
                <ul>
                    <?php
                        for ($i=0; $i < $max_num_paginas; $i++){
							if ($pagina == $i+1){
								echo '<li><a id="active" class="lbar" href="seccion1.php?pag=' . ($i + 1) . '">' . ($i + 1) . '</a></li>';
							} 
							else{
								echo '<li><a class="lbar" href="seccion1.php?pag=' . ($i + 1) . '">' . ($i + 1) . '</a></li>';
							}
							
                        }
                    
                    ?>
                </ul>
            </section>
            
        
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