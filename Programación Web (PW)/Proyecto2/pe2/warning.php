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
				<article>
					<h2 class="tituloseccion"> Inform about the use of cookies on their website: </h2>
			 
					<p>What are cookies?
		Cookies are files that can be downloaded to your computer through web pages. They are tools that have an essential role for the provision of numerous services of the information society. Among others, they allow a website to store and retrieve information about the browsing habits of a user or their team and, depending on the information obtained, they can be used to recognize the user and improve the service offered.
		Types of cookies</p>
					<p>Depending on the entity that manages the domain from which the cookies are sent and treat the data obtained, two types can be distinguished:</p>
					<ol>
						<li>Own cookies: those that are sent to the user's terminal equipment from a computer or domain managed by the editor itself and from which the service requested by the user is provided.</li>
						<li>Third party cookies: those that are sent to the user's terminal equipment from a computer or domain that is not managed by the publisher, but by another entity that processes the data obtained through the cookies.</li>
						<li>In the event that cookies are installed from a computer or domain managed by the publisher itself but the information collected through them is managed by a third party, they can not be considered as own cookies.
		There is also a second classification according to the period of time they remain stored in the client's browser, which may be:
		Session cookies: designed to collect and store data while the user accesses a web page. They are usually used to store information that only interests to keep for the provision of the service requested by the user on a single occasion (eg a list of products purchased).</li>
						<li>Persistent cookies: the data is still stored in the terminal and can be accessed and processed during a period defined by the person responsible for the cookie, which can range from a few minutes to several years.</li>
					</ol>
					<p>Finally, there is another classification with five types of cookies according to the purpose for which the data obtained is processed:</p>
					<ol>
						<li>Technical cookies: those that allow the user to navigate through a web page, platform or application and the use of different options or services that exist in it, such as controlling traffic and data communication, identifying the session, access restricted access parts, remember the elements that make up an order, perform the purchase process of an order, make the request for registration or participation in an event, use security elements during navigation, store contents for dissemination of videos or sound or share content through social networks.</li>
						<li>Personalization cookies: allow the user to access the service with some predefined general characteristics based on a series of criteria in the user's terminal, such as the language, the type of browser through which the user accesses the service, regional configuration from where you access the service, etc.</li>
						<li>Analysis cookies: allow the person responsible for them to monitor and analyze the behavior of the users of the websites to which they are linked. The information collected through this type of cookies is used in the measurement of the activity of the websites, application or platform and for the elaboration of navigation profiles of the users of said sites, applications and platforms, in order to introduce improvements in function of the analysis of the usage data made by the users of the service.</li>
						<li>Advertising cookies: allow the management, in the most efficient way possible, of the advertising spaces.</li>
						<li>Behavioral advertising cookies: they store information on the behavior of users obtained through the continuous observation of their browsing habits, which allows the development of a specific profile to display advertising based on it.</li>
						<li>Cookies of external social networks: they are used so that visitors interact with the content of different social networks (facebook, youtube, twitter, LinkedIn, etc.) and that is generated for the users of said social networks. The conditions of use of these cookies and the information collected is regulated by the privacy policy of the corresponding social platform.</li>
					</ol>
					<p>Deactivation and elimination of cookies.
		You have the option to allow, block or eliminate the cookies installed on your computer by configuring the browser options installed on your computer. When you disable cookies, some of the services may also stop working. The way to disable cookies is different for each browser.</p>

				</article> 

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
