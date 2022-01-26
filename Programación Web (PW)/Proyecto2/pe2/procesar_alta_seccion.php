
<?php

	session_start();
	
	if ($_SESSION["usuario"]='admin'){ //&& !empty($_POST)
		require_once('php_PDO_POO/claseSecciones.php');
		
		claseSecciones::registroSeccion($_POST);
		header("Location: seccion_registrada.php");
		exit;	
	}
	else{
		header("Location: index.php");
		exit;
	}

	

?>
    