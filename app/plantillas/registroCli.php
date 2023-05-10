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

        <label for="nombre">Nombre:
            <input type="text" name="nombre" id="nombre" required>

            <?php if (isset($errorNombre)) : ?>
                <span class="error"><?= $errorNombre ?></span>
            <?php endif ?>
        </label>
        <br>

        <label for="apellidos">Apellido:
            <input type="text" name="apellidos" id="apellidos" required>

            <?php if (isset($errorApellido)) : ?>
                <span class="error"><?= $errorApellido ?></span>
            <?php endif ?>
        </label>
        <br>

        <label for="domicilio">Domicilio:

            <label for="ciudad">Ciudad:
                <input type="text" name="ciudad" id="ciudad" required>
            </label>

            <select name="tipo_via" id="tipo_via">
                <option value="avenida">Avenida</option>
                <option value="calle">Calle</option>
                <option value="carretera">Carretera</option>
                <option value="diagonal">Diagonal</option>
                <option value="paseo">Paseo</option>
            </select>

            <input type="text" name="domicilio" id="domicilio" required>

            <?php if (isset($errorDomicilio)) : ?>
                <span class="error"><?= $errorDomicilio ?></span>
            <?php endif ?>
        </label>
        <br>

        <label for="telefono">Teléfono:
            <input type="tel" name="telefono" id="telefono" required>

            <?php if (isset($errorTlf)) : ?>
                <span class="error"><?= $errorTlf ?></span>
            <?php endif ?>
        </label>
        <br>

        <label for="email">Correo electrónico:
            <input type="email" name="email" id="email" required>

            <?php if (isset($errorEcorreo)) : ?>
                <span class="error"><?= $errorEcorreo ?></span>
            <?php endif ?>
        </label>
        <br>

        <label>Documento:
            <br>
            <select name="tipo">
                <?php foreach ($tipos as $tipo) : ?>
                    <option value="<?= $tipo->name ?>"><?= $tipo->name ?></option>
                <?php endforeach ?>
            </select>

            <input type="text" name="documento" id="documento" required>

            <?php if (isset($errorDocumento)) : ?>
                <span class="error"><?= $errorDocumento ?></span>
            <?php endif ?>
        </label>

        <label>Nacionalidad:
            <br>
            <select name="nacionalidad">
                <?php foreach ($nacionalidades as $nacionalidad) : ?>
                    <option value="<?= $nacionalidad->name ?>"><?= $nacionalidad->name ?></option>
                <?php endforeach ?>
            </select>
        </label>

        <label for="password">Contraseña:
            <br>
            <input type="password" name="password" id="password" required>

            <?php if (isset($errorPass)) : ?>
                <span class="error"><?= $errorPass ?></span>
            <?php endif ?>
        </label>

        <input type="submit" value="Enviar" name="registroOK">
    </form>
</body>

</html>
<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>