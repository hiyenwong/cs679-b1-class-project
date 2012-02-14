<?php
abstract class Key {

	private static $INDEX = 0;

	private $id;
	private $new;

	public function __construct ($id = null) {
		if ($id === null) {
			$this->new = true;
			$this->id = self::$INDEX++;
		} else {
			$this->new = false;
			$this->id = $id;
		}
	}

	public function getId () {
		return $this->id;
	}

	public function isNew () {
		return $this->new;
	}

	abstract public function getClass ();

	public function __toString () {
		$value = $this->getClass () . '_' . $this->getId ();

		if ($this->new)
			$value .= '_new';

		return $value;
	}
}
?>