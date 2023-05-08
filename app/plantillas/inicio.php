<?php
/* Ejemplo de plantilla que se mostrará dentro de la plantilla principal
  ob_start() activa el almacenamiento en buffer de la página. Mientras se
             almacena en el buffer no se produce salida alguna hacia el
             navegador del cliente
  luego viene el código html y/o php que especifica lo que debe aparecer en
     el cliente web
  ob_get_clean() obtiene el contenido del buffer (que se pasa a la variable
             $contenido) y elimina el contenido del buffer
  Por último se incluye la página que muestra la imagen común de la aplicación
    (en este caso base.php) la cual contiene una referencia a la variable
    $contenido que provocará que se muestre la salida del buffer dentro dicha
    página "base.php"
*/
?>
<?php ob_start() ?>
<?php $_SESSION['usuario'] === 'anonimo' ?>

<div class="centro">
<iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d2943.0198866644905!2d-2.4325443233874617!3d42.46986572815652!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0xd5aab0dbd9ed72d%3A0xda98798954220d52!2sIES%20Comercio!5e0!3m2!1ses!2ses!4v1683220365676!5m2!1ses!2ses" width="600" height="450" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
</div>

<?php $contenido = ob_get_clean() ?>
<?php include 'base.php' ?>