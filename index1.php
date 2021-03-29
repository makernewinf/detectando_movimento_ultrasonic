<?php
echo "<!DOCTYPE html><html><head><title>Atualizacao via Wifi</title>
      <META HTTP-EQUIV='REFRESH' CONTENT='5'></head>";                            // Atualiza a cada 5 seg

$arquivo = "alarme.txt";		      // abre o arquivo txt
$handle = fopen($arquivo, "r");
while (!feof ($handle)) {
  $texto = fgets($handle, 4096);
  echo $texto."<br>";			// mostra conteudo do arquivo txt
}
fclose ($handle);

echo "</html>";
?>