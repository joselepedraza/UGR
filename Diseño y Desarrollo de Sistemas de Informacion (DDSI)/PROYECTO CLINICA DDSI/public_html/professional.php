<?php
require_once("includes/connect.php");

if(!isset($_SESSION["id"])){
    header("location: login.php");
}
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

        <?php
            if($_SESSION["type"] == "client"){
                include_once("client/professional.php");
            }else{
                include_once("professional/professional.php");
            }
        ?>

    </main>

    </body>
</html>