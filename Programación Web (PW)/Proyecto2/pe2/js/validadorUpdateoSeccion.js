// JavaScript Document
function validarActualizarSeccion() {				
					
	var nombre = document.getElementById('nombre').value;
	var titulo = document.getElementById('titulo').value;
	var items = document.getElementById('items').value;

		if(nombre.length == 0 || nombre.length >= 18) {
			alert('¡Introduzca una longitud válida!');
			return false;
		}
	
		if(titulo.length == 0 || titulo.length >= 50) {
			alert('¡Introduzca una longitud válida!');
			return false;
		}	
		
		if(items.length != 0 && items.length >= 1000) {
			alert('¡Introduzca una longitud válida!');
			return false;
		}	

	return true;
	
}