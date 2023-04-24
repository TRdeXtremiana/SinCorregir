<?php ob_start() ?>
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>Registro</title>
</head>

<body>
    <h1>Formulario de Registro</h1>
    <form method="POST" action="">

        <label for="nombre">Nombre:</label>
        <input type="text" name="nombre" id="nombre" required>
        <br>

        <label for="apellidos">Apellido:</label>
        <input type="text" name="apellidos" id="apellidos" required>
        <br>

        <label for="domicilio">Domicilio:</label>
        <select name="tipo_via" id="tipo_via">
            <option value="avenida">Avenida</option>
            <option value="calle">Calle</option>
            <option value="carretera">Carretera</option>
            <option value="diagonal">Diagonal</option>
            <option value="paseo">Paseo</option>
        </select>

        <input type="text" name="domicilio" id="domicilio" required>
        <br>
        <label for="ciudad">Ciudad:
            <input type="text" name="ciudad" id="ciudad" required>
        </label>

        <label for="telefono">Teléfono:</label>
        <input type="tel" name="telefono" id="telefono" required>
        <br>

        <label for="email">Correo electrónico:</label>
        <input type="email" name="email" id="email" required>
        <br>

        <label for="documento">Documento:</label>
        <select name="tipo" id="tipo">
            <option value="dni">DNI</option>
            <option value="nie">NIE</option>
            <option value="pasaporte">Pasaporte</option>
        </select>

        <input type="text" name="documento" id="documento" required>
        <br>

        <label for="nacionalidad">Nacionalidad:</label>
        <input type="text" name="nacionalidad" id="nacionalidad" required>
        <br>

        <label for="password">Contraseña:</label>
        <input type="password" name="password" id="password" required>
        <br>

        <input type="submit" value="Enviar" name="registroOK">
    </form>
</body>

</html>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>