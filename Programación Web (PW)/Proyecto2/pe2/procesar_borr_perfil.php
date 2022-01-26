
<?php

	session_start();
	
    require_once('php_PDO_POO/claseUsuarios.php');
    
	$logeado = claseUsuarios::loginUsuario($_SESSION['usuario'], $_POST['password_anterior']);
	
	if($logeado){
		claseUsuarios::eliminarMiUsuario($_SESSION['usuario']);
		session_destroy();
		header("Location: index.php");	//ó registro_usuario.php
		exit;
	}
	else{	
		header("Location: eliminar_perfil.php");
		exit;
	}
	

?>
    