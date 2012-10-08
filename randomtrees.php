<?php

$data = "";

for($i = 0; $i < 20; ++$i) {
	$x = mt_rand(0, 2000);
	$y = mt_rand(0, 2000);

	$data .= '{ "type": "crate", "x": ' . $y . ', "y": ' . $x . ' },' . PHP_EOL;	
}
for($i = 0; $i < 100; ++$i) {
	$x = mt_rand(0, 2000);
	$y = mt_rand(0, 2000);

	$data .= '{ "type": "tree", "x": ' . $y . ', "y": ' . $x . ' },' . PHP_EOL;	
}



print trim(trim($data), ',');
