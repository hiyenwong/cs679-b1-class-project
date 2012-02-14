<?php
interface Displayable extends Iterator {

  public function getId ();

  public function getSize ();

  public function getHeaders ();

  public function getHeaderCount ();

  public function getRows ();
  
  public function setSize ($size);

  public function setHeaders (Array $headers);

  public function addRow (Array $row);

  public function isPaged ();

  public function hasTooltips ();

  public function getTooltips ();
}
?>