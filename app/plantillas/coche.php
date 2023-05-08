<?php ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>

<h1><?= $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] ?></h1>

<form action="" method="post">
    <fieldset>
        <legend>Fechas</legend>
        <label for="alquilerDiaInicio"> Recogida:
            <input type="date" name="alquilerDiaInicio" id="alquilerDiaInicio" min="<?= (new DateTime('now'))->format('Y-m-d') ?>">
        </label>

        <label for="alquilerDiaDevolucion"> Devolución:
            <input type="date" name="alquilerDiaDevolucion" id="alquilerDiaDevolucion" min="<?= (new DateTime('now'))->format('Y-m-d') ?>">
        </label>

        <?php if (isset($texto)) : ?>
            <span id="diasAlquiler"><?= $texto ?></span>
            <br>
        <?php endif ?>

        <input type="submit" name="okAlquiler" value="Alquilar">

    </fieldset>
</form>

<!-- < ?= var_dump($_SESSION['coche']) ?> -->

<img src="web\imagenes\<?= $_SESSION['coche']['categoria'] ?>\<?= $_SESSION['coche']['foto'] ?>.jpg" alt="imagen de un <?= $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] ?>" width="500px" style="display: block; margin: 0 auto;">

<!-- < ?= var_dump($_SESSION['coche']) ?> -->

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>