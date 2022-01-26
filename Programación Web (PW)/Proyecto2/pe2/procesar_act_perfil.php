
<?php

	session_start();
	
    require_once('php_PDO_POO/claseUsuarios.php');
    
	$logeado = claseUsuarios::loginUsuario($_SESSION['usuario'], $_POST['password_anterior']);
	
	if($logeado){
		claseUsuarios::updatearUsuario($_SESSION['usuario'], $_POST);
		header("Location: updatear_perfil.php");
		exit;	
	}
	else{
		header("Location: updatear_perfil.php");
		exit;
	}
	

?>
    