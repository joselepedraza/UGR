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
        <!--JQuery (para popup emergente)-->
         <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js" type="text/javascript"></script>
        
        <script>
			$(function() {
				$('a.popper').hover(function() {
					$('#pop').toggle();
				});
			});
		</script>
        
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
            
		<hr>
		<main>
        	<h2 class="tituloseccion"> Seat Ibiza Copa </h2>
			<hr>
			<section id="sectItem">    
            		<div id="pop">
                		<p>Seat Ibiza Copa - Segunda Mano</p>
              		</div>               
                <article id="mainImgItem">
                    <a class="popper" href=""><figure>
                       <img src="Imagenes/Catalogo/Seat_Ibiza_Copa.jpg" alt="coche1" width="200" height="100">
                    </figure></a>
                    
                </article>

                <article id="caracteristicas">                    
                    <table border="1">
                        <tr><th> <strong> Precio </strong> </th>
                        	<td> 8500€ </td>
                        </tr>
                        <tr><th> <strong> Kilometraje </strong> </th>
                        	<td> 110000 KM </td>
                        </tr>
                        <tr><th> <strong> Potencia </strong> </th>
                        	<td> 140 CV </td>
                        </tr>
                        <tr><th> <strong> Año </strong> </th>
                        	<td> 2019 </td>
                        </tr>
                        <tr><th> <strong> ¿Donde estoy? </strong> </th>
                        	<td> Soria </td>
                        </tr>
                        <tr><th> <strong> Carburante </strong> </th>
                        	<td> Diesel </td>
                        </tr>
                        <tr><th> <strong> Transmision </strong> </th>
                        	<td> Manual (6 marchas) </td>
                        </tr>
                        <tr><th> <strong> Consumo </strong> </th>
                        	<td> 3-6L/100KM </td>
                        </tr>
                        
                    </table>
                </article>
			</section>
            
            <section id="descripcion">
            	<h3> <strong> Descripción: </strong> </h3>
            	<p>
                     Espectacular¡¡¡Ibiza 2.0 tdi 140cv Copa,cambio manual 6 vel,llantas 16",tapiceria tela negro/gris con asientos deportivos,aire acondicionado,sistema radio cd/mp3 con conexion AUX,elevalunas electricos,espejos retrovisores electricos,faros antiniebla delanteros,volante deportivo cuero,control crucero velocidad,elevalunas electricos,minimo consumo...libro de mantenimiento SEAT.

Precio todo incluido (IVA ,transferencia a su nombre y garantía de 12 meses) Certificado de kilometraje y ausencia de daños estructurales Compramos su coche en el acto y al contado Financiación 100% en el acto Posibilidad de cambio de vehículo en 10 días Entregamos su vehículo en cualquier punto de la península.
             	</p>
                
            </section>
            
            <section id="galeriaItem">
                    <figure>
                      <img src="Imagenes/Catalogo/Seat_Ibiza_Copa.jpg" alt="coche1" width="175" height="100">
                    </figure>
                    <figure>
                      <img src="Imagenes/Catalogo/SeatIbizaCopa/2011_SEAT_Ibiza_SE_Copa.jpg" alt="coche1" width="175" height="100">
                    </figure> 
                    <figure>
                      <img src="Imagenes/Catalogo/SeatIbizaCopa/Seat_Ibiza_Copa_interior.JPG" alt="coche1" width="175" height="100">
                    </figure>             
                    <figure>
                      <img src="Imagenes/Catalogo/SeatIbizaCopa/Seat_Ibiza_Copa_trasero.jpg" alt="coche1" width="175" height="100">
                    </figure>
                    <figure>
                      <img src="Imagenes/Catalogo/SeatIbizaCopa/Seat_Ibiza_SC_Copa_trasero.jpg" alt="coche1" width="175" height="100">
                    </figure>
                    <figure>
                      <img src="Imagenes/Catalogo/SeatIbizaCopa/sin-ibiza_copa_lateral.jpg" alt="coche1" width="175" height="100"> 
                    </figure> 
                    <figure>
                      <img src="Imagenes/Catalogo/SeatIbizaCopa/SEAT-IBIZA-00.jpg" alt="coche1" width="175" height="100">
                    </figure>
                    
            </section>
            <hr>
            <section class="paginacion2">
                <ul>
                    <li><a class="lbar" href="item1.php" id="ocultar"> Anterior </a></li>
                    <li><a class="lbar" href="item2.html"> Siguiente </a></li>
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