// JavaScript Document
function validarRegistroItem() {
					
	var marca = document.getElementById('marca').value;
	var precio = document.getElementById('price').value;
	var kilometraje = document.getElementById('km').value;
	var potencia = document.getElementById('potencia').value;
	var ubicacion = document.getElementById('lugar').value;
	var anio = document.getElementById('anio').value;
	
	
	if(marca.length == 0) {
		alert('¡Introduzca la marca y modelo del vehículo!');
		return false;
	}
	
	var patron_num = /^[0-9]+$/;
	if(!patron_num.test(String(precio))){
		alert('¡Introduzca el precio (valor numérico)!');
		return false;
	}
	
	if(!patron_num.test(String(kilometraje))){
		alert('¡Introduzca número de kilómetros!');
		return false;
	}
	
	if(!patron_num.test(String(potencia))){
		alert('¡Introduzca la potencia del vehículo (valor numérico)!');
		return false;
	}
	
	var patron_letras = /^[A-Za-z]+$/;
	if(!patron_letras.test(String(ubicacion))){
		alert('¡Introduce una ubicación real!');
		return false;
	}
	
	
	if(!patron_num.test(String(anio)) || (anio < 1990 || anio >= 2022)){
		alert('¡Introduzca un año correcto (valor numérico entre 1990 y 2021)!');
		return false;
	}
	
	
	
	
	/*
	if(name.length==0) {
		alert('¡Introduzca su nombre!');
		return false;
	}
	if(surname.length==0) {
		alert('¡Introduzca sus apellidos!');
		return false;
	}
	
	*/
	
	/*if(password.length<8 || password.length>12) {
		alert('¡La contraseña debe tener entre 8 y 12 caracteres!');
		return false;
	}*/
	
	
	return true;
	
}