<?php

interface Source {

  public function read (Array $params);

  public function insert (Array $params);

  public function update (Array $params);

  public function delete (Array $params);

}
?>