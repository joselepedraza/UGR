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
        <script src="./js/validadorRegistroUsuario.js"></script>
  
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
        	<h2 class="tituloseccion"> Registro de usuario </h2>
			<hr>
			<section id="formulario">
				<form action="procesar_registro.php" name="form_registro" id="reg_usuario" method="POST" autocomplete"on" onsubmit="return validarRegistroUsuario();">
					<label for="name"> Nombre: </label> <br> 
					<!--<input type="text" name="nombre" id="name" required /> -->
                    <input type="text" name="nombre" id="name"/> 
					<br><br>
					<label for="surname"> Apellidos: </label> <br> 
					<!--<input type="text" name="apellidos" id="surname" required />-->
                    <input type="text" name="apellidos" id="surname"/>
					<br><br>
                    <label for="usuario"> Nombre de usuario: </label> <br> <!--&nbsp;&nbsp;&nbsp;&nbsp;-->
					<!--<input id="user" name="usuario" type="text" placeholder="nombre de usuario" required />-->
                    <input id="usuario" name="usuario" type="text" placeholder="nombre de usuario"/>
					<br><br>
                    <label for="password"> Contraseña: </label> <br> <!--&nbsp;&nbsp;&nbsp;&nbsp;-->
					<!--<input id="password" type="password" name="password" placeholder="de 8 a 12 caracteres" pattern="[A-Za-z0-9!?-]{8,12}" required/>-->
                    <input id="pass" type="password" name="password" placeholder="de 8 a 12 caracteres"/>
					<br><br>
					<label for="email"> E-mail: </label> <br> 
					<!--<input type="email" name="email" id="email" placeholder="ejemplo@gmail.com"required />-->
                    <input type="email" name="email" id="email" placeholder="ejemplo@gmail.com"/>
					<br><br>
					<label for="tel"> Teléfono: </label> <br> 
					<!--<input type="tel" name="telefono" id="tel" placeholder="+34" required />-->
                    <input type="tel" name="telefono" id="tel" placeholder="+34" />
					<br><br>
					<label for="birthday"> Fecha nacimiento:  </label> <br> 
					<!--<input type="date" name="nacimiento" step="1" min="1920-01-01" id="birthday" required />-->
                    <input type="date" name="nacimiento" step="1" min="1920-01-01" id="birthday"/>
					<br><br>
					<label for="interest"> Interesado/a en: </label> <br> 
					<input type="radio" name="interes" value="comprar"/ id="interest"> Comprar <br>
					<input type="radio" name="interes" value="vender" id="interest" checked /> Vender <br>
					<input type="radio" name="interes" value="ambas" id="interest"/> Ambas
					<br><br>
					<datalist id="found">
						<option value="Email">
						<option value="Web">
						<option value="Un amigo">
						<option value="Redes sociales">
						<option value="Publicidad">
						<option value="Otro">
					</datalist>
					<label for="found"> ¿Cómo nos conociste? </p>
					<input type="text" id="found" name="conociste" list="found">
					<br><br>
					<input type="submit" id="btn1" name="btn_registroUsuario" value="Enviar"> 
					<input type="reset" id="btn2" value="Resetear"> 
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