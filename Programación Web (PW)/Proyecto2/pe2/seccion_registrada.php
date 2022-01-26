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
		<?php
            session_start();
            require('php_PDO_POO/claseSecciones.php');
			
			if((!isset($_SESSION["usuario"])) || ($_SESSION["usuario"]!='admin')){
				header("Location:index.php");
			}
        ?>   
    
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
            
		<hr>
		<main>
            <section>
                <h2 class="tituloseccion"> AHORA PUEDES VER TU SECCIÓN EN EL MENÚ </h2>
                <hr>
                <h2 class="tituloseccion"> <a href="index.php"> IR A: HOME </a></h2>
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