<?php

require_once 'user.inc';

class Phone implements Comparable {

	private $user;
	private $number;
	private $textable;
	private $isPrimary;
	
	public function __construct (User $user, $number, $textable, $isPrimary) {
		$this->user = $user;
		$this->number = $number;
		$this->textable = $textable;
		$this->isPrimary = $isPrimary;
	}
	
	public function getUser() {
		return $this->user;
	}
	
	public function getNumber() {
		return $this->number;
	}
	
	public function isTextable() {
		return $this->textable;
	}
	
	public function isPrimary() {
		return $this->isPrimary;
	}
	
	public function equals ($other) {
	
		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}
	
		return ($this->getNumber() == $other->getNumber() && $this->getUser() == $other->getUser());
	}
	
	public function __toString () {
		return $this->number;
	}
	
}
?>