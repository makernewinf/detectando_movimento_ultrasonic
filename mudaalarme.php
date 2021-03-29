<?php

if (isset($_POST['texto'])) 
{
   $texto   = '<CENTER><H1>'.$_POST['texto'].'<br><br>';
   $texto   = $texto.'Data: '.date('d/m/Y').'<br><br>'.'Hora: '.date('h:i').'<br></H1></CENTER>';
   
   $arquivo =  fopen('alarme.txt', 'w');
   fwrite($arquivo, $texto);

   fclose($arquivo);
}

?>

<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="../css/bootstrap.min.css" rel="stylesheet" type="text/css" />
  <link href="../css/bootstrap-theme.min.css" rel="stylesheet" type="text/css" />
</head>
  <body>
  <h1> Grava texto no arquivo alarme.txt para ser visualizado no programa.</h1>
    <form method="post">
    <textarea name="texto" cols="300" rows="5" ></textarea><br>
      <input type="submit" name="enviar" value="enviar" class="btn btn-primary"><br>
    </form>
   </body>
</html>

