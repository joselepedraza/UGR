<?php
session_start();
$link = mysqli_connect("localhost", "id12262959_clinicaddsi", "clinicaddsi", "id12262959_clinicaddsi");
if(!$link){
    echo "Error al conectarse";
    exit;
}
?>