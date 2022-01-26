
<?php

	session_start();
	
	if ($_SESSION["usuario"]='admin'){ 
		require_once('php_PDO_POO/claseSecciones.php');
		
		claseSecciones::updatearSeccion($_POST);
		header("Location: updatear_secciones.php");
		exit;	
	}
	else{
		header("Location: index.php");
		exit;
	}


?>
    