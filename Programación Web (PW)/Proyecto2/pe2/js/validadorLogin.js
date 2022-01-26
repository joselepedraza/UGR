// JavaScript Document
function validarFormularioLogin() {
	var usuario = document.getElementById('user').value;
	if(usuario.length == 0) {
		alert('¡El campo usuario está vacío!');
		return false;
	}
	
	var contra = document.getElementById('password').value;
	if(contra.length<8 || contra.length>12) {
		alert('¡La longitud de la contraseña no es válida!');
		return false;
	}

	return true;
}