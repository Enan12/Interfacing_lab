<!DOCTYPE html>
<html>
<head>
    <title>Sensor network</title>
    <meta http-equiv="refresh" content="2" >
</head>
<body>

<?php
if(isset($_GET['node_id']) && isset($_GET['pir']) && isset($_GET['mq2'])) {
	if($_GET['pir']=='1') echo "node " . $_GET['node_id'] . " detected motion";
    else echo "no motion detected";

    $myfile = fopen("sensor.txt", "w") or die("Unable to open file!");
    $txt = "Sensor" . $_GET['node_id'] . " PIR: " . $_GET['pir'] . " MQ2: " . $_GET['mq2'] . "\n";
    fwrite($myfile, $txt);
    fclose($myfile);
}
else {
    $myfile = fopen("sensor.txt", "r") or die("Unable to open file!");
    echo fread($myfile,filesize("sensor.txt"));
    fclose($myfile);
}
?>

</body>
</html>