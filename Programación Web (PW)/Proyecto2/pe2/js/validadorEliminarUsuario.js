// JavaScript Document
function validarEliminarUsuario() {
					
	var contra_orig = document.getElementById('password_anterior').value;

	var patron_pass = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9])(?!.*\s).{8,12}$/;
	if (!patron_pass.test(String(contra_orig))){
			alert('¡Debe introducir su contraseña original para guardar los cambios!');
			return false;
		}
	
	
	return true;
	
}