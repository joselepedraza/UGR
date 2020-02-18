<?php
require_once("includes/connect.php");

if(empty($_SESSION)){
    header("Location:/login.php");
}

$id = $_SESSION["id"];

?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>Clínica DDSI</title>
        <?php include_once("includes/head.php"); ?>
    </head>
    <body>

    <?php include_once("includes/header.php"); ?>
    <main>

        <nav>
            <ul>
                <li>
                    <a href="professional.php">
                        <figure>
                            <img src="./assets/doctor.png" title="logo" alt="logo" />
                            
                            <figcaption><?php echo $_SESSION["type"] === "client" ? "Pedir cita" : "Profesionales"; ?></figcaption>
                        </figure>
                    </a>
                </li>
                <li>
                    <a href="client.php">
                        <figure>
                            <img src="./assets/waiter.png" title="logo" alt="logo" />
                            
                            <figcaption><?php echo $_SESSION["type"] === "client" ? "Mis datos" : "Clientes"; ?></figcaption>
                        </figure>
                    </a>
                </li>
                <?php if($_SESSION["type"] === "professional"){ ?>
                <li>
                    <a href="service.php">
                        <figure>
                            <img src="./assets/stethoscope.png" title="logo" alt="logo" />
                            <figcaption>Servicios</figcaption>
                        </figure>
                    </a>
                </li>
                <?php } ?>
                <li>
                    <a href="#">
                        <figure>
                            <img src="./assets/store.png" title="logo" alt="logo" />
                            <figcaption>Tienda</figcaption>
                        </figure>
                    </a>
                </li>
            </ul>
        </nav>

    </main>

    </body>
</html>