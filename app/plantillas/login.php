<?php ob_start() ?>
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>Login</title>
</head>

<body>
    <h1>Login</h1>
    <form action="" method="post">
        <fieldset>
            <legend>Inicio de sesión</legend>

            <label for="eCorreo">e-Correo:
                <input type="email" name="eCorreo" id="eCorreo" />
            </label>
            <br>

            <label for="password">Contraseña:
                <input type="password" name="password" id="password">
            </label>
            <br>

            <input type="submit" value="Enviar" name="loginOK" />
        </fieldset>
    </form>

    <a href="index.php?ctl=registro"> No estoy registrado </a>

</body>

</html>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>