
<?php

	session_start();
	
	if ($_SESSION["usuario"]='admin'){ //&& !empty($_POST)
		require_once('php_PDO_POO/claseItems.php');
		
		claseItems::registroItem($_POST);
		header("Location: item_registrado.php");
		exit;	
	}
	else{
		header("Location: index.php");
		exit;
	}

	

?>
    