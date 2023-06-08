<?php
ob_start() ?>

<?php
if (!isset($_SESSION['cliente']['nombre'])) {
    header('Location: index.php?ctl=inicio');
}
?>

<?php $_SESSION['usuario'] = 'cliente'; ?>

<h1>Bienvenido, <?= $_SESSION['cliente']['nombre'] ?></h1>

<!-- < ?= var_dump($_SESSION['cliente']) ?> -->

<form action="" method="post">

    <fieldset>
        <legend>¿Quiéres alquilar un vehículo?</legend>

        <label for="fechaAlquiler">
            Recogida del vehiculo: <input type="date" name="fechaAlquiler" id="fechaAlquiler" min="<?= (new DateTime('now'))->format('Y-m-d') ?>">
        </label>

        <label for="fechaDevolucion">
            Devolución del vehiculo: <input type="date" name="fechaDevolucion" id="fechaDevolucion" min="<?= (new DateTime('now'))->format('Y-m-d') ?>">
        </label>

        <?php if (!empty($errores['fecha'])) : ?>
            <span class="error"> <?= $errores['fecha'] ?></li> </span>
        <?php endif ?>
        <br>
        <input type="submit" name="okFechas" value="Mostrar">
    </fieldset>

    <?php if (isset($_POST['okFechas']) && empty($errores)) : ?>
        <?php foreach ($categorias as $key => $valor) : ?>
            <div class="categoria">
                <h2><?= $valor['nombre'] ?></h2>
                <p><?= $valor['descr'] ?></p>


                <table>
                    <thead>
                        <tr>
                            <th>Foto</th>
                            <th>Marca</th>
                            <th>Modelo</th>
                            <th>Año</th>
                            <th>Motor</th>
                            <th>Matricula</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($filtro as $coche) : ?>

                            <?php if ($coche['categoria'] === $valor['nombre']) : ?>
                                <!-- < ?= var_dump($coche) ?> -->
                                <tr>
                                    <td><img src="web/imagenes/<?= $coche['categoria'] ?>/<?= $coche['foto'] ?>" alt="imagen de un <?= $coche['marca'] . ' ' . $coche['modelo'] ?>" width="100px"></td>
                                    <td><?= $coche['marca'] ?></td>
                                    <td><?= $coche['modelo'] ?></td>
                                    <td><?= $coche['año'] ?></td>
                                    <td><?= $coche['motor'] ?></td>
                                    <td><?= $coche['matricula'] ?></td>
                                    <!-- <td class="disponible">< ?= $coche['estado'] ?></td> -->

                                    <!-- <td> <a href="index.php?ctl=alguno&matricula=< ?= $coche['matricula'] ?>"><input type="submit" name="< ?= $coche['matricula'] ?>" value="Más info"></a></td> -->
                                    <td> <button name="ok" value="<?= $coche['matricula'] ?>" formmethod="post">Más info</button></td>
                                </tr>
                            <?php endif ?>
                        <?php endforeach ?>
                    </tbody>
                </table>
            </div>
        <?php endforeach ?>
    <?php endif ?>

</form>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>