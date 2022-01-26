// JavaScript Document
function validarRegistroUsuario() {
					
	var username = document.getElementById('usuario').value;
	var contra = document.getElementById('pass').value;
	var nombre = document.getElementById('name').value;
	var apellidos = document.getElementById('surname').value;
	var correo = document.getElementById('email').value;
	var phone = document.getElementById('tel').value;
	var birthday = document.getElementById('birthday').value;
	
	
	if(username.length == 0) {
		alert('¡El campo usuario está vacío!');
		return false;
	}
	
	var patron_pass = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9])(?!.*\s).{8,12}$/;
	if (!patron_pass.test(String(contra))){
		alert('¡La contraseña debe tener entre 8 y 12 caracteres, y al menos un número, letra mayuscula, letra minúscula y caracter especial!');
		return false;
	}
	
	var patron_letras = /^[A-Za-z]+$/;
	if(!patron_letras.test(String(nombre))){
		alert('¡Introduce un nombre real!');
		return false;
	}
	if(!patron_letras.test(String(apellidos))){
		alert('¡Introduce un apellido real!');
		return false;
	}
	
	var patron_email = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
	if(!patron_email.test(String(correo))){
		alert('¡Introduzca un email real!');
		return false;
	}
	
	var patron_tel = /^[0-9]+$/;
	if(!patron_tel.test(String(phone))){
		alert('¡El telefono contiene caracteres no válidos o está vacío!');
		return false;
	}
	
	if(birthday.length==0){
		alert('¡Debe introducir su fecha de nacimiento!');
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