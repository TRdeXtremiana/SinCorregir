<?php ob_start() ?>

<h1>Bienvenido, cliente</h1>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>