<?php ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>

<h1><?= $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] ?></h1>

<form action="" method="post">
    <fieldset>
        <legend>Recogida</legend>

        <label for="alquilerDiaInicio"> Día:
            <input type="date" name="alquilerDiaInicio" id="alquilerDiaInicio" min="<?= (new DateTime('now'))->format('Y-m-d') ?>">
            <input type="time" id="horaDiaInicio" name="horaDiaInicio" min="00:00" max="23:59" required>
        </label>

        <label for="ubicaRecogida">
            <select name="ubicaRecogida" id="ubicaRecogida">
                <option value="">Seleccionar una ubicación</option>
                <option value="Logroño">Logroño</option>
                <option value="Calahorra">Calahorra</option>
                <option value="Arnedo">Arnedo</option>
                <option value="Haro">Haro</option>
                <option value="Nájera">Nájera</option>
            </select>
        </label>

        <!-- <label>Ubicación:
            <br>
            <select name="ubicaRecogida" require>
                < ?php foreach ($UbicacionesAlquiler as $ubi) : ?>
                    <option value="< ?= $ubi->name ?>">< ?= $ubi->name ?></option>
                < ?php endforeach ?>
            </select>
        </label> -->

    </fieldset>

    <fieldset>
        <legend>Devolución</legend>

        <label for="alquilerDiaDevolucion"> Día:
            <input type="date" name="alquilerDiaDevolucion" id="alquilerDiaDevolucion" min="<?= (new DateTime('now'))->format('Y-m-d') ?>">
            <input type="time" id="horaDiaDevolucion" name="horaDiaDevolucion" min="00:00" max="23:59" required>
        </label>

        <label for="ubicaDevolucion">
            <select name="ubicaDevolucion" id="ubicaDevolucion">
                <option value="">Seleccionar una ubicación</option>
                <option value="Logroño">Logroño</option>
                <option value="Calahorra">Calahorra</option>
                <option value="Arnedo">Arnedo</option>
                <option value="Haro">Haro</option>
                <option value="Nájera">Nájera</option>
            </select>

    </fieldset>

    <input type="submit" name="okAlquiler" value="Alquilar">
    <input type="submit" name="okDevolver" value="Devolver">
    <br>

    <?php if (isset($confirmacion)) : ?>
        <span id="diasAlquiler"><?= $confirmacion ?></span>
    <?php endif ?>

    <?php if (!empty($errores)) : ?>
        <ul class="error">
            <?php foreach ($errores as $error) : ?>
                <li> <?= $error ?></li>
            <?php endforeach ?>
        </ul>
    <?php endif ?>
</form>

<!-- < ?= var_dump($_SESSION['coche']) ?> -->

<img src="web\imagenes\<?= $_SESSION['coche']['categoria'] ?>\<?= $_SESSION['coche']['foto'] ?>.jpg" alt="imagen de un <?= $_SESSION['coche']['marca'] . ' ' . $_SESSION['coche']['modelo'] ?>" width="500px" style="display: block; margin: 0 auto;">

<!-- < ?= var_dump($_SESSION['coche']) ?> -->

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>