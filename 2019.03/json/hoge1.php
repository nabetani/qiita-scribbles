<?php

function test($val)
{
  $json = json_encode([$val]);
  echo $val, ": ";
  if (is_string($json)){
    echo $json, "\n";
  } else {
    var_export($json);
    echo " / ";
    var_export(json_last_error_msg());
    echo "\n";
  }
}

test( INF );
test( NAN );
