// JavaScript Document
function validarRegistroSeccion() {
					
	var nombre = document.getElementById('nombre').value;
	var titulo = document.getElementById('titulo').value;

	
	if(nombre.length == 0 || nombre.length >= 18) {
		alert('¡Introduzca una longitud válida!');
		return false;
	}
	
	if(titulo.length == 0 || titulo.length >= 50) {
		alert('¡Introduzca una longitud válida!');
		return false;
	}	
	
	return true;
	
}