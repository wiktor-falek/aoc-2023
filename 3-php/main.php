<?php
$content = file_get_contents( __DIR__ . '/input.txt' );

$lines = explode("\n", $content);
array_pop($lines);

define("BOUND_X", count($lines));
define("BOUND_Y", strlen($lines[0]));

function get_pos($x, $y, $lines) {
  if ($x < 0 || $y < 0 || $x >= BOUND_X || $y >= BOUND_Y) {
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
  while ($x < strlen($line)) {
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
  if (!is_numeric($mid)) {
    $mid = "";
  }
  
  $left = scan_left($startX - 1, $line);
  $right = scan_right($startX + 1, $line);
  
  if ($left !== "" && $mid !== "" && $right !== "") {
    $results = [$left . $mid . $right];
  } elseif ($left !== "" && $mid !== "") {
      $results = [$left . $mid];
  } elseif ($mid !== "" && $right !== "") {
      $results = [$mid . $right];
  } elseif ($left !== "" && $right !== "") {
      $results = [$left, $right];
  } elseif ($left !== "") {
      $results = [$left];
  } elseif ($mid !== "") {
      $results = [$mid];
  } elseif ($right !== "") {
      $results = [$right];
  } else {
      $results = [];
  }

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
        ...scan_left_and_right($x, $y - 1, $lines), // top
        ...scan_left_and_right($x, $y + 1, $lines), // bottom
      ];

      $results = array_filter($positions, function ($number) {
        return strLen($number);
      });

      $numbers = array_merge($numbers, $results);
    }
  }
}

$sum = array_reduce($numbers, function($acc, $number) {
  return $acc + intval($number);
}, 0);

echo("Part 1: " . $sum . "\n");
?>