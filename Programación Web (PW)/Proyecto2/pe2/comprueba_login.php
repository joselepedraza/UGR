
<?php

	session_start();
	
    require_once('php_PDO_POO/claseUsuarios.php');
    
	$logeado = claseUsuarios::loginUsuario($_POST['usuario'], $_POST['password']);
	
	if($logeado){
		$_SESSION['usuario'] = $_POST['usuario'];	
	}
	
	header("Location: index.php");
	exit;
	
?>
    