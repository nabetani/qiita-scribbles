<?php
function test($val)
{
  $json = json_encode([$val]);
  echo( $val );
  echo( ": " );
  if (is_string($json)){
    echo( $json."\n" );
  } else {
    echo(var_export($json));
    echo(" / ");
    echo(var_export(json_last_error_msg())."\n");
  }
}

test( INF );
test( NAN );