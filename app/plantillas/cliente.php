<?php ob_start() ?>

<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bienvenido</title>
</head>

<body>
    <h1>Bienvenido, cliente</h1>


</body>

</html>


<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>