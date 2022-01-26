
<?php

	session_start();
	
    require_once('php_PDO_POO/claseSecciones.php');

	$id = $_GET["id"];
	
	if(!empty($id)){
		claseSecciones::eliminarSeccion($id);
		header("Location: updatear_secciones.php");
		exit;	
	}
	else{///siempre volvemos a la pagina updatear para ver si se ha borrado correctamente
		header("Location: updatear_secciones.php");
		exit;
	}
	

?>
    