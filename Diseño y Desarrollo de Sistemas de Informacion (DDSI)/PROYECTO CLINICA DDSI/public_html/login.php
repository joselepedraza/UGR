<?php
require_once("./includes/connect.php");

if(isset($_SESSION["id"])){
    header("Location:/index.php");
}

if(!empty($_POST)){
    unset($_GET);
    try{
        
        $login = htmlentities(addslashes($_POST["username"]));
        $password = htmlentities(addslashes($_POST["password"]));
        
        if($_POST["type"] === "client"){
            $query = "SELECT * FROM Cliente WHERE DNI='$login' AND Contrasenia='$password'";
        }else{
            $query = "SELECT * FROM Profesional WHERE DNI='$login' AND Contrasenia='$password'";
        }
        
        if($result = mysqli_query($link, $query)){
            $row = mysqli_fetch_assoc($result);
            if(!empty($row)){
                $_SESSION["id"] = $_POST["username"];
                $_SESSION["type"] = $_POST["type"];
                header("Location:/index.php");
            }else{
                throw new Exception("2");
            }
        }else{
            throw new Exception("2");
        }
    }catch(Exception $e){
        if(isset($e)){
            header("Location:/login.php?error=" . $e->getMessage());
        }else{
            header("Location:/login.php?error=1");
        }
    }
}
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>Clínica DDSI</title>
        <link rel="stylesheet" href="./css/style.css" />
    </head>
    <body>

    <main>
        <form method="post" id="login">
            <img src="./assets/logo-proyecto.png" alt="logo" title="logo" />
            <label>
                Tipo Inicio
                <select name="type">
                    <option value="client">Cliente</option>
                    <option value="professional">Profesional</option>
                </select>
            </label>
            <label>
                DNI
                <input type="text" name="username">
            </label>
            <label>
                Contraseña
                <input type="password" name="password">
            </label>
            <?php if(!empty($_GET) && isset($_GET["error"])){ ?>
            <div class="error">
            <?php
                if($_GET["error"] == "1"){
                    echo "Ha habido un error, vuelva a intentarlo.";
                }else if($_GET["error"] == "2"){
                    echo "Usuario inexistente.";
                }
            ?>
            </div>
            <?php } ?>
            <input type="submit" value="Enviar Datos" />
        </form>
    </main>

    </body>
</html>