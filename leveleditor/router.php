<?php

date_default_timezone_set("UTC");
error_reporting(-1);
ini_set("session.save_path", $_SERVER['DOCUMENT_ROOT'] . DIRECTORY_SEPARATOR  . ".." . DIRECTORY_SEPARATOR . "tmp/");


$direct = array('gif', 'png', 'jpg', 'css', 'js', 'xml', 'ico', 'swf', 'class');
$info   = pathinfo($_SERVER["PHP_SELF"]);

if(isset($info["extension"]) && in_array($info["extension"], $direct)) {
    return false; // serve the requested resource as-is.
}

if(isset($info['basename']) == "phpliteadmin.php") {
    return false; // serve the requested resource as-is.
}

return true;