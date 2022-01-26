<?php
    session_start();
	
	if ($_SESSION["usuario"]!='admin'){
		header("Location: index.php");
		exit;	
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
        <script src="./js/validadorLogin.js"></script>
        <script src="./js/validadorRegistroItem.js"></script>
        
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
        	<h2 class="tituloseccion"> Registrar vehículo </h2>
			<hr>
			<section id="formulario">
				
                <form action="procesar_alta_item.php" name="form_registro_item" id="reg_item" method="post" enctype="multipart/formdata" autocomplete"off" onsubmit="return validarRegistroItem();">
					<label for="name"> Marca y Modelo: </label> <br> 
					<!--<input type="text" name="nombre" id="marca" required /> -->	
                    <input type="text" name="nombre" id="marca"/> 
                    <br>
					<label for="price"> Precio (€): </label> <br> 
					<!--<input type="number" name="precio" id="price" required />-->
                    <input type="number" name="precio" id="price"/>
                    <br>
					<label for="km"> Kilometraje (KM): </label> <br> 
					<!--<input type="number" name="kilometraje" id="km" required />-->
                    <input type="number" name="kilometraje" id="km"/>
                    <br>
					<label for="potencia"> Potencia (CV): </label> <br> 
					<!--<input type="text" name="potencia" id="potencia" required />-->
                    <input type="text" name="potencia" id="potencia" />
                    <br>
                    <label for="lugar"> ¿Dónde estoy? </label> <br> 
					<!--<input type="text" name="ubicacion" id="lugar" required />-->
                    <input type="text" name="ubicacion" id="lugar"/>
                    <br>
					<br>
					<label for="tipo"> Estado del vehículo: </label> <br> 
					<input type="radio" name="tipo_venta" value="Nuevo" id="tipo"/> Nuevo <br>
					<input type="radio" name="tipo_venta" value="Segunda_mano" id="tipo" checked /> Segunda mano <br>
					<input type="radio" name="tipo_venta" value="KM_0" id="tipo"/> Km 0
					<br><br>
                    <label for="carburante"> Carburante: </label> <br> 
					<input type="radio" name="carburante" value="Gasolina" id="carburante"/> Gasolina <br>
					<input type="radio" name="carburante" value="Diesel" id="carburante" checked /> Diésel <br>
					<input type="radio" name="carburante" value="Electrico" id="carburante"/> Electrico <br>
                    <input type="radio" name="carburante" value="Gas" id="carburante"/> Gas <br>
                    <input type="radio" name="carburante" value="Otro" id="carburante"/> Otro
					<br><br>
                    <label for="transmision"> Transmision: </label> <br> 
					<input type="radio" name="transmision" value="Automático" id="transmision"/> Automático <br>
					<input type="radio" name="transmision" value="Manual" id="transmision" checked /> Manual 
                  
					<br>
					<datalist id="año">
						<option value="1990">
						<option value="1991">
						<option value="1992">
						<option value="1993">
						<option value="1994">
						<option value="1995">
                        <option value="1996">
						<option value="1997">
						<option value="1998">
						<option value="1999">
						<option value="2000">
						<option value="2001">
                        <option value="2002">
						<option value="2003">
                        <option value="2004">
						<option value="2005">
                        <option value="2006">
						<option value="2007">
                        <option value="2008">
                        <option value="2009">
						<option value="2010">
                        <option value="2011">
						<option value="2012">
                        <option value="2013">
						<option value="2014">
                        <option value="2015">
                        <option value="2016">
						<option value="2017">
                        <option value="2018">
						<option value="2019">
                        <option value="2020">
                        <option value="2021">
					</datalist>
                    <br>
					<label for="año"> Año del vehículo: </p>
					<!--<input type="text" name="anio" id="anio" list="año" required>-->
                    <input type="text" name="anio" id="anio" list="año" />
					<br><br>
                    
                    <label for="descripcion">Descripción:</label>
					<br><br>
                    <textarea id="descripcion" name="descripcion" rows="10" cols="8">Por ejemplo: 
Espectacular¡¡¡Ibiza 2.0 tdi 140cv Copa,cambio manual 6 vel,llantas 16",tapiceria tela negro/gris con asientos deportivos,aire acondicionado,sistema radio cd/mp3 con conexion AUX,elevalunas electricos,espejos retrovisores electricos,faros antiniebla delanteros,volante deportivo cuero,control crucero velocidad,elevalunas electricos,minimo consumo...
                    </textarea>
                    <br><br>
                    <input type="file" name="imagen" accept="image/png, .jpeg, .jpg"/>
                    <br><br>
                    
					<!--Debido a temas de seguridad del servidor, debemos subir la imagen por separado con sftp y simular la subida a la BD añadiendo la ruta de la misma manualmente-->                 
                    <label for="url_img"> Introduzca la ruta de la imagen anterior: </label> <br> 
					<input type="text" name="url_img" id="url_img" value="Imagenes/Catalogo/prueba.jpg" required /> 	<!--placeholder=""-->
                    <br><br><br>
					<input type="submit" id="btn_registroItem" value="Registrar vehículo en la plataforma"> &nbsp;&nbsp;&nbsp;&nbsp;
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