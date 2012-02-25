<?php

class MappingDetail implements Comparable {

	private $mapping;
	private $columnName;
	private $csvColumnNumber;
	
	public function __construct (Mapping $mapping, $columnName, $csvColumnNumber) {
		$this->mapping = $mapping;
		$this->columnName = $columnName;
		$this->csvColumnNumber = $csvColumnNumber;
	}
	
	public function getMapping() {
		return $this->mapping;
	}
	
	public function getColumnName() {
		return $this->columnName;
	}
	
	public function getCsvColumnNumber() {
		return $this->csvColumnNumber;
	}
	
	public function equals ($other) {
	
		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}
	
		return ($this->getMapping()->equals($other->getMapping()) && 
					$this->getColumnName() == $other->getColumnName() && 
					$this->getCsvColumnNumber() == $other->getCsvColumnNumber());
	}
	
	public function __toString () {
		return $this->getColumnName() . " to " . $this->getCsvColumnNumber();
	}
	
}
?>