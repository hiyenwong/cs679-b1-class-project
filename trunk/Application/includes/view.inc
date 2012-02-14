<?php
abstract class View {
  private $modified;
  private $state;

  private static $stack = array ();

  private static $STATE_INSERT = 1;
  private static $STATE_UPDATE = 2;
  private static $STATE_DELETE = 3;

  public function __construct () {
    $this->modified = false;
    $this->state = self::$STATE_UPDATE;
  }

  protected function markModified () {
    $this->modified = true;    
  }

  protected function markNew () {
    $this->state = self::$STATE_INSERT;
  }

  public function requestDelete () {
    $this->modified = true;
    $this->state = self::$STATE_DELETE;
  }

  public function isModified () {
    return ($this->modified);
  }

  protected function deleteRequested () {
    return ($this->state == self::$STATE_DELETE);
  }

  abstract public function getKey ();

  abstract public function read ();
  abstract protected function insert ();
  abstract protected function update ();
  abstract protected function delete (); 

  abstract protected function preWrite ();
  abstract protected function postWrite ();

  final public function write () {

    if (!in_array ($this, self::$stack)) {
      array_push (self::$stack, $this);

      $this->preWrite ();

      if ($this->isModified ()) {      
	
	switch ($this->state) {
	case self::$STATE_DELETE:
	  $this->delete ();
	  break;
	  
	case self::$STATE_INSERT:
	  $this->insert ();
	  break;
	  
	case self::$STATE_UPDATE:
	  $this->update ();
	  break;
	}
      } 
      
      $this->postWrite (); 
   
      array_pop (self::$stack);
   
      $this->modified = false;
      $this->state = self::$STATE_UPDATE;    
    }
  }
}
?>
