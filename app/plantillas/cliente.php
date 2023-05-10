<?php
ob_start() ?>
<?php $_SESSION['usuario'] = 'cliente'; ?>

<h1>Bienvenido, <?= $_SESSION['cliente']['nombre'] ?></h1>

<!-- < ?= var_dump($_SESSION['cliente']) ?> -->

<form action="" method="post">
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
                        <th>Estado</th>
                    </tr>
                </thead>

                <tbody>
                    <?php foreach ($tablaCli as $key => $value) : ?>
                        <?php if ($value['estado'] === 'disponible' && $value['categoria'] === $valor['nombre']) : ?>

                            <tr>
                                <td><img src="web\imagenes\<?= $value['categoria'] ?>\<?= $value['foto'] ?>.jpg" alt="imagen de un <?= $value['marca'] . ' ' . $value['modelo'] ?>" width="100px"></td>
                                <td><?= $value['marca'] ?></td>
                                <td><?= $value['modelo'] ?></td>
                                <td><?= $value['año'] ?></td>
                                <td><?= $value['motor'] ?></td>
                                <td><?= $value['matricula'] ?></td>

                                <?php if ($value['estado'] === 'disponible') : ?>
                                    <td class="disponible"><?= $value['estado'] ?></td>
                                <?php else : ?>
                                    <td class="noDisponible">A partir de ? a las ?</td> <!-- fecha de fin de alquiler -->
                                <?php endif ?>

                                <td><button type="submit" name="okCoche" value="<?= $value['matricula'] ?>">Más info</button></td>
                                <!-- <td><button type="submit" name="okDevolver" value="< ?= $value['matricula'] ?>">Devolver</button></td> -->
                            </tr>

                        <?php endif ?>
                    <?php endforeach ?>
                </tbody>
            </table>
        </div>
    <?php endforeach ?>
</form>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>