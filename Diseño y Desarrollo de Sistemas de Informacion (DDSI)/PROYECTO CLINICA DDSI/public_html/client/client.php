<?php


if(!empty($_POST)){
    
    print_r($_POST);
    
    if(isset($_POST["update"])){
        
        $query = "
            UPDATE Cliente SET 
                Contrasenia='".$_POST["contrasenia"]."',
                Email='".$_POST["email"]."',
                Direccion='".$_POST["direccion"]."',
                Telefono=".$_POST["telefono"]."
            WHERE `DNI`='". $_POST["id"] ."'";
        
        if(!($result = mysqli_query($link, $query))){
            $error = "¡FALLADO AL ACTUALIZAR!";
        }
        
    }
}

$query = "SELECT * FROM Cliente WHERE Dni='$id'";

if($result = mysqli_query($link, $query)){
    $row = mysqli_fetch_assoc($result);
    if(!empty($row)){
?>

<form method="post" name="">
    <h1>Mi información</h1>
    <label>
        DNI
        <input value="<?php echo $row["DNI"]; ?>" name="dni" type="text" disabled />
    </label>
    <label>
        Nombre
        <input value="<?php echo $row["Nombre"]; ?>" name="nombre" type="text" disabled />
    </label>
    <label>
        Contraseña
        <input value="<?php echo $row["Contrasenia"]; ?>" name="contrasenia" type="password" />
    </label>
    <label>
        Email
        <input value="<?php echo $row["Email"]; ?>" name="email" type="email" />
    </label>
    <label>
        Dirección
        <input value="<?php echo $row["Direccion"]; ?>" name="direccion" type="text" />
    </label>
    <label>
        Teléfono
        <input value="<?php echo $row["Telefono"]; ?>" name="telefono" type="telephone" />
    </label>
    <label>
        Fecha de nacimiento
        <input value="<?php echo $row["Fecha de nacimiento"]; ?>" name="fecha" type="date" disabled />
    </label>
    
    <input value="<?php echo $row["DNI"]; ?>" name="id" type="hidden" />
    <input type="submit" value="Modificar" name="update" />
</form>
<?php
    }
}
?>