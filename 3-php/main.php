<?php
$content = file_get_contents( __DIR__ . '/example.txt' );

$lines = explode("\n", $content);
array_pop($lines);

define("BOUND_X", count($lines));
define("BOUND_Y", strlen($lines[0]));

function get_pos($x, $y, $lines) {
  if ($x < 0 || $y < 0 || $x >= BOUND_X || $y > BOUND_Y) {
    return NULL;
  }
  return $lines[$y][$x];
}

function scan_left($startX, $line) {
  $x = $startX;
  
  $digits = [];
  while ($x >= 0) {
    $char = $line[$x];
    
    if (!is_numeric($char)) {
      break;
    }

    array_push($digits, $char);
    $x = $x - 1;
  }

  return implode("", array_reverse($digits));
}

function scan_right($startX, $line) {
  $x = $startX;

  $digits = [];
  while ($x <= strlen($line)) {
    $char = $line[$x];
    
    if (!is_numeric($char)) {
      break;
    }
    
    array_push($digits, $char);
    $x = $x + 1;
  }

  return implode("", $digits);
}

function scan_left_and_right($startX, $y, $lines) {
  $line = $lines[$y];
  
  $mid = get_pos($startX, $y, $lines);

  $left = scan_left($startX - 1, $line);
  $right = scan_right($startX + 1, $line);

  $results = match (true) {
    ($left && $mid && $right) => [$left . $mid . $right],
    ($left && $right) => [$left, $right],
    ($left && $mid) => [$left . $mid],
    ($mid && $right) => [$mid . $right],
    ($right) => [$right],
    ($left) => [$left],
    ($mid) => [$mid],
    default => [],
  };

  return $results;
}

$numbers = [];
for ($y = 0; $y < BOUND_Y; $y++) { 
  $line = $lines[$y];
  for ($x = 0; $x < BOUND_X; $x++) { 
    $char = $lines[$y][$x];
    if ($char != "." && !is_numeric($char)) {

      $positions = [
        scan_left($x - 1, $line), // left
        scan_right($x + 1, $line), // right
        scan_left_and_right($x, $y - 1, $lines), // top
        scan_left_and_right($x, $y + 1, $lines), // bottom
      ];

      // TODO: flatten
      $results = array_filter($positions, function ($number) {
        return strLen($number) != 0;
      });

      $numbers = array_merge($numbers, $results);
    }
  }
}

foreach ($numbers as $number) {
  echo($number . "\n");
}

?>