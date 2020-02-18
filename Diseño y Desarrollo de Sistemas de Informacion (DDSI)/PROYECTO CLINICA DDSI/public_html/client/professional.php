<?php
$error = NULL;
$ok = NULL;
$servicio = NULL;
$descripcion = NULL;
if(!empty($_GET) && isset($_GET["servicio"])){
    $query = "SELECT * FROM Servicio WHERE `Nombre Servicio`='". $_GET["servicio"] ."'";
    if($result = mysqli_query($link, $query)){
        $row = mysqli_fetch_assoc($result);
        $servicio    = $row["Nombre Servicio"];
        $descripcion = $row["Descripcion"];
    }
}


if(!empty($_POST)){

    $query = "
        INSERT INTO Agenda 
            (`Fecha`, `DNI_Profesional`, `DNI_Cliente`)
        VALUES (
            '".$_POST["date"]."',
            '".$_POST["dniprofesional"]."',
            '".$_POST["dnicliente"]."'
        )
        ";
        
    if($result = mysqli_query($link, $query)){
        $ok = "¡Cita realizada correctamente!";
    }else{
        $error = "¡NO SE PUDO PEDIR LA CITA!";
    }
    
}
?>

<form method="post" name="">
    <h1>Pedir Cita</h1>
    <?php 
        if(!is_null($error)){
            echo "<div class='error'>$error</div>";
        }
        if(!is_null($ok)){
            echo "<div class='ok'>$ok</div>";
        }
    ?>
    <label>
        Seleccione un servicio
        <select onchange="javascript:window.location.href=this.value" name="service">
            <?php
            $query = "SELECT * FROM Servicio";
            if($servicio !== NULL){
                $query .= " WHERE NOT(`Nombre Servicio` = '$servicio')";
                echo "<option value='?servicio=$servicio' selected>$servicio</option>";
            }
            
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                if(is_null($servicio)){
                    $servicio    = $row["Nombre Servicio"];
                    $descripcion = $row["Descripcion"];
                }
                
                do{
                    $servicio_it = $row["Nombre Servicio"];
                    echo "<option value='?servicio=$servicio_it'>$servicio_it</option>";
                }while($row = mysqli_fetch_assoc($result));
            }
            ?>
        </select>
    </label>
    <?php echo "<p>\"". $descripcion ."\"</p>"; ?>
    <label>
        Seleccione un profesional
        <select onchange="javascript:window.location.href=this.value" name="service">
            <?php
            $query = "SELECT * FROM Profesional WHERE `Nombre Servicio`='$servicio'";
            $profesional = null;
            if(!empty($_GET) && isset($_GET["professional"])){
                
                $profesional = $_GET["professional"];
                
                $query .= " WHERE NOT(`DNI` = '". $profesional ."')";
                
                
                if($result = mysqli_query($link, "SELECT Nombre FROM Profesional WHERE DNI='".$profesional."'")){
                    $row = mysqli_fetch_assoc($result);
                echo "<option value='?servicio=$servicio&professional=$profesional' selected>".$row["Nombre"]."</option>";
                }
            }
            
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                $profesional = $row["DNI"];
                do{
                    echo "<option value='?servicio=$servicio&professional=". $row["DNI"] ."'>". $row["Nombre"] ."</option>";
                }while($row = mysqli_fetch_assoc($result));
            }
            ?>
        </select>
    </label>
    <?php 
        if(!is_null($profesional)){
            $query = "
                SELECT * FROM Agenda WHERE DNI_Profesional='$profesional' AND 
                	DATE(Fecha) <= DATE_ADD(CURDATE(),INTERVAL 10 DAY)
                	AND 
                	DATE(Fecha) >= CURDATE()
                ORDER BY Fecha ASC
            ";
            
            $ocupied = [];
            if($result = mysqli_query($link, $query)){
                for($i = 0; $i < 10; ++$i){
                    $o = [];
                    for($k = 0; $k < 8; ++$k){
                        $o[Date('Y-m-d '.str_pad((8+$k), 2, '0', STR_PAD_LEFT).':00:00', strtotime("+". $i ." days"))] = false;
                    }
                    $ocupied[Date('Y-m-d', strtotime("+". $i ." days"))] = $o;
                }
                while($row = mysqli_fetch_assoc($result)){
                    $date = $row["Fecha"];
                    $ocupied[explode(" ", $date)[0]][$row["Fecha"]] = true;
                }
            }
            
            for($i = 0; $i < 10; ++$i){
                
                $current = $ocupied[Date('Y-m-d', strtotime("+". $i ." days"))];
                $found = true;
                $m = 0;
                for(; $m < 8 && $found; ++$m){
                    $found = $current[Date('Y-m-d '.str_pad((8+$m), 2, '0', STR_PAD_LEFT).':00:00', strtotime("+". $i ." days"))];
                }
    ?>
            <label class="date-label">
                <span><?php $date = Date('Y-m-d '.str_pad((8+$m-1), 2, '0', STR_PAD_LEFT).':00', strtotime("+". $i ." days ")); echo $date; ?></span>
                <input name="date" value="<?php echo $date; ?>" type="radio" 
                <?php echo ($m == 8) ? "disabled" : "required"; ?> />
            </label>
    <?php
            }
    ?>
    <input type="hidden" value="<?php echo $profesional; ?>" name="dniprofesional"/>
    <input type="hidden" value="<?php echo $id; ?>" name="dnicliente"/>
    <input type="submit" value="Pedir Cita" />
    <?php
        }
    ?>
</form>