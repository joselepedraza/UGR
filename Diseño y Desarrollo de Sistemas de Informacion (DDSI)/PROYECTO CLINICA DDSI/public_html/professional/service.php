<?php
$id = NULL;
$error = NULL;
$add = false;

if(!empty($_GET)){
    
    if(isset($_GET["event"]) && $_GET["event"] === "add"){
        $add = true;
    }else if(isset($_GET["nombre"])){
        
        if(isset($_GET["event"]) && $_GET["event"] === "remove"){
            $query = "DELETE FROM Servicio WHERE `Nombre Servicio`='". $_GET["nombre"] ."'";
            if($result = mysqli_query($link, $query)){
                $error = "¡SERVICIO ELIMINADO!";
            }
        }else{
            $query = "SELECT * FROM Servicio WHERE `Nombre Servicio`='". $_GET["nombre"] ."'";
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                $id    = $row["Nombre Servicio"];
            }
        }
    }
}

if(!empty($_POST)){
    
    if(isset($_POST["update"])){
        
        $query = "
            UPDATE Servicio SET 
                `Nombre Servicio`='".$_POST["nombre"]."',
                `Descripcion`='".$_POST["descripcion"]."'
            WHERE `Nombre Servicio`='". $_POST["id"] ."'";
        
        $id = NULL;
        
        if(!($result = mysqli_query($link, $query))){
            $error = "¡FALLADO AL ACTUALIZAR!";
        }
        
    }else if(isset($_POST["add"])){
        
        $query = "
            INSERT INTO Servicio 
                (`Nombre Servicio`, `Descripcion`)
            VALUES (
                '".$_POST["nombre"]."',
                '".$_POST["descripcion"]."'
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
        Nombre Servicio
        <input type="text" name="nombre" required autocomplete="off" />
    </label>
    <label>
        Descripcion
        <textarea type="text" name="descripcion" autocomplete="off"></textarea>
    </label>
    <input type="submit" value="Añadir" name="add" />
</form>
<?php
}else{
?>
<form method="post">
    <h1>Servicios</h1>
    <?php 
        if(!is_null($error)){
            echo "<div class='error'>$error</div>";
        }
    ?>
    <label>
        Seleccione un servicio
        <select onchange="javascript:window.location.href=this.value" name="client">
            <?php 
            $query = "SELECT * FROM Servicio";
            if(!is_null($id)){
                $query .= " WHERE NOT(`Nombre Servicio` = '$id')";
                echo "<option value='?nombre=$id' selected>$id</option>";
            }
            
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                if(is_null($id)){
                    $id = $row["Nombre Servicio"];
                }
                
                do{
                    $id_it = $row["Nombre Servicio"];
                    echo "<option value='?nombre=$id_it'>$id_it</option>";
                }while($row = mysqli_fetch_assoc($result));
            }
            
             ?>
        </select>
    </label>
    <?php
    $query = "SELECT * FROM Servicio WHERE `Nombre Servicio`='$id'";
    if($result = mysqli_query($link, $query)){
        $row = mysqli_fetch_assoc($result);
        if(!empty($row)){
    ?>
    <label>
        Nombre
        <input <?php echo 'value="'.$row["Nombre Servicio"].'"'; ?> type="text" name="nombre" autocomplete="off" />
    </label>
    <label>
        Descripcion
        <textarea type="text" name="descripcion" autocomplete="off"><?php echo $row["Descripcion"]; ?></textarea>
    </label>
    <input <?php echo 'value="'.$row["Nombre Servicio"].'"'; ?> type="hidden" name="id" />
    <?php
        }
    ?>
    <input type="submit" value="Modificar" name="update" />
    <div class="buttons">
        <a href="<?php echo "?nombre=$id&event=remove"; ?>" class="remove">Eliminar</a>
        <a href="<?php echo "?event=add"; ?>" class="add">Añadir Nuevo</a>
    </div>
</form>
<?php
    }
}
?>
</form>