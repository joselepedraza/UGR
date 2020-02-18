<?php
$id = $_SESSION["id"];
if($_SESSION["type"] === "client"){
    $query = "SELECT Nombre FROM Cliente WHERE DNI='".$id."'";
}else{
    $query = "SELECT Nombre FROM Profesional WHERE DNI='".$id."'";
}
?>

<header>
    <nav>
        <a href="index.php"></a></a>
        <figure>
            <img src="./assets/logo-proyecto.png" title="logo" alt="logo" />
        </figure>
        </a>
        <div id="helloworld">
            ¡Hola!, 
            <i><?php 
            if($result = mysqli_query($link, $query)){
                $row = mysqli_fetch_assoc($result);
                echo $row["Nombre"];
            }
            ?></i>
            (<b><?php echo $id; ?></b>)
        </div>
        <ul>
            <li class="inicio"><a href="index.php">Inicio</a></li>
            <?php if($_SESSION["type"] === "client"){ ?>
            <li><a href="professional.php">Pedir Cita</a></li>
            <?php }else{ ?>
            <li><a href="professional.php">Profesionales</a></li>
            <?php } ?>
            <?php if($_SESSION["type"] === "client"){ ?>
            <li><a href="client.php">Mis datos</a></li>
            <?php }else{ ?>
            <li><a href="client.php">Clientes</a></li>
            <?php } ?>
            
            <?php if($_SESSION["type"] === "professional"){ ?>
            <li><a href="service.php">Servicio</a></li>
            <?php } ?>
            
            <li><a href="#">Tienda</a></li>
            <li class="logout"><a href="./logout.php">Log out</a></li>
        </ul>
    </nav>
</header>
