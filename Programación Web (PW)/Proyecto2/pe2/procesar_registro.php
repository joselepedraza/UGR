
<?php

	session_start();
	
	
    require_once('php_PDO_POO/claseUsuarios.php');
    
	claseUsuarios::registroUsuario($_POST);
	
	$_SESSION['usuario'] = $_POST['usuario'];
	$_SESSION['nombre'] = $_POST['nombre'];
	
	header("Location: usuario_registrado.php");
	exit;	

?>
    