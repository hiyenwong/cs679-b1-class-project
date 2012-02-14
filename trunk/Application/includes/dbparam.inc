<?php

class DbParam {

	private $column;
	private $id;
	private $value;
	private $type;
	private $condition;

	public function __construct($column, $id, $value, $type, $condition = '=') {
		$this->column = $column;
		$this->id = $id;
		$this->value = $value;
		$this->type = $type;
		$this->condition = $condition;
	}

	public function getColumn() {
		return $this->column;
	}

	public function getId() {
		return $this->id;
	}

	public function getValue() {
		return $this->value;
	}

	public function getType() {
		return $this->type;
	}

	public function getCondition() {
		return $this->condition;
	}

	public function __toString() {
		return $this->column . ' ' . $this->condition . ' ' . $this->id;
	}

}

?>