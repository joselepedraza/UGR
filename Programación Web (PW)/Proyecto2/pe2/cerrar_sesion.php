
<?php	


	session_start(); 
	$_SESSION['usuario'] = null;
	$_SESSION['nombre'] = null;
	session_destroy();	
	
	header("Location: index.php"); 

?>
