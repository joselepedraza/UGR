<?php
$nombre = NULL;
$dni = NULL;
$error = NULL;
$add = false;

if(!empty($_GET)){
    
    if(isset($_GET["event"]) && $_GET["event"] === "add"){
        $add = true;
    }else if(isset($_GET["dni"])){
        
        if(isset($_GET["event"]) && $_GET["event"] === "remove"){
            $query = "DELETE FROM Cliente WHERE `DNI`='". $_GET["dni"] ."'";
            if($result = mysqli_query($link, $query)){
                $error = "¡USUARIO ELIMINADO!";
            }
        }else{
            $query = "SELECT * FROM Cliente WHERE `DNI`='". $_GET["dni"] ."'";
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                $nombre = $row["Nombre"];
                $dni    = $row["DNI"];
            }
        }
    }
}

if(!empty($_POST)){
    
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
        
    }else if(isset($_POST["add"])){
        
        $query = "
            INSERT INTO Cliente 
                (`DNI`, `Nombre`, `Contrasenia`, `Direccion`, `Email`, `Telefono`, `Fecha de Nacimiento`)
            VALUES (
                '".$_POST["dni"]."',
                '".$_POST["nombre"]."',
                '".$_POST["contrasenia"]."',
                '".$_POST["direccion"]."',
                '".$_POST["email"]."',
                ".$_POST["telefono"].",
                '".$_POST["fecha"]."'
            )
            ";
        
        if(!($result = mysqli_query($link, $query))){
            $error = "¡FALLADO AL INSERTAR!";
        }
        
    }
    
}

?>

<?php

if($add){
?>
<form method="post">
    <label>
        DNI
        <input type="text" name="dni" required autocomplete="off" />
    </label>
    <label>
        Nombre
        <input type="text" name="nombre" required autocomplete="off" />
    </label>
    <label>
        Contraseña
        <input type="password" name="contrasenia" required autocomplete="off" />
    </label>
    <label>
        Email
        <input type="email" name="email" required autocomplete="off" />
    </label>
    <label>
        Teléfono
        <input type="telephone" name="telefono" required autocomplete="off" />
    </label>
    <label>
        Dirección
        <input type="text" name="direccion" required autocomplete="off" />
    </label>
    <label>
        Fecha de nacimiento
        <input type="date" name="fecha" required autocomplete="off" />
    </label>
    <input type="submit" value="Añadir" name="add" />
</form>
<?php
}else{
?>
<form method="post">
    <h1>Clientes</h1>
    <?php 
        if(!is_null($error)){
            echo "<div class='error'>$error</div>";
        }
    ?>
    <label>
        Seleccione un cliente
        <select onchange="javascript:window.location.href=this.value" name="client">
            <?php 
            $query = "SELECT * FROM Cliente";
            if(!is_null($dni)){
                $query .= " WHERE NOT(`DNI` = '$dni')";
                echo "<option value='?dni=$dni' selected>$nombre</option>";
            }
            
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                if(is_null($dni)){
                    $nombre    = $row["Nombre"];
                    $dni = $row["DNI"];
                }
                
                do{
                    $nombre = $row["Nombre"];
                    $dni_it = $row["DNI"];
                    echo "<option value='?dni=$dni_it'>$nombre</option>";
                }while($row = mysqli_fetch_assoc($result));
            }
            
             ?>
        </select>
    </label>
    <?php
    $query = "SELECT * FROM Cliente WHERE DNI='$dni'";
    if($result = mysqli_query($link, $query)){
        $row = mysqli_fetch_assoc($result);
        if(!empty($row)){
    ?>
    <label>
        DNI
        <input <?php echo 'value="'.$row["DNI"].'"'; ?> type="text" name="dni" autocomplete="off" disabled />
    </label>
    <label>
        Nombre
        <input <?php echo 'value="'.$row["Nombre"].'"'; ?> type="text" name="nombre" autocomplete="off" disabled />
    </label>
    <label>
        Contraseña
        <input <?php echo 'value="'.$row["Contrasenia"].'"'; ?> type="password" name="contrasenia" autocomplete="off" />
    </label>
    <label>
        Email
        <input <?php echo 'value="'.$row["Email"].'"'; ?> type="email" name="email" autocomplete="off" />
    </label>
    <label>
        Teléfono
        <input <?php echo 'value="'.$row["Telefono"].'"'; ?> type="telephone" name="telefono" autocomplete="off" />
    </label>
    <label>
        Dirección
        <input <?php echo 'value="'.$row["Direccion"].'"'; ?> type="text" name="direccion" autocomplete="off" />
    </label>
    <label>
        Fecha de nacimiento
        <input value="<?php echo $row["Fecha de nacimiento"]; ?>" type="date" name="fecha" autocomplete="off" disabled />
    </label>
    <input value="<?php echo $row["DNI"]; ?>" type="hidden" name="id" />
    <?php
        }
    ?>
    <input type="submit" value="Modificar" name="update" />
    <div class="buttons">
        <a href="<?php echo "?dni=$dni&event=remove"; ?>" class="remove">Eliminar</a>
        <a href="<?php echo "?event=add"; ?>" class="add">Añadir Nuevo</a>
    </div>
</form>
<?php
    }
}
?>
</form>