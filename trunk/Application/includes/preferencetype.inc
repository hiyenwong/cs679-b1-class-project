<?php

require_once 'view.inc';
require_once 'factory.inc';
require_once 'comparable.inc';
require_once 'keys/preferencetypekey.inc';
require_once 'sources/preferencetypesource.inc';

class PreferenceType extends View implements Comparable {

	private $key;
	protected $id;

	private $name;

	public function __construct (PreferenceTypeKey $key) {
		$this->key = $key;

		parent::__construct ();

		if ($key->isNew()) {
			$this->markNew();
		} else {
			$this->id = $key->getId();
		}
	}

	public function getKey () {
		return $this->key;
	}

	public function getId () {
		return $this->id;
	}

	public function getName() {
		return $this->name;
	}



	public function setName($name) {
		$this->markModified();
		$this->name = $name;
	}



	public function read () {
		$source = PreferenceTypeSource::getSource();
		$values = $source->read (array ('ID' => $this->id));

		$this->name = $values['name'];
	}

	protected function insert () {
		$params = array();

		if ($this->name) {
			$params ['NAME'] = $this->name;
		} else {
			throw new Exception ('User requires a userid.');
		}

		$source = PreferenceTypeSource::getSource();
		$this->id = $source->insert ($params);

	}

	protected function update () {
		$params = array ();

		if ($this->name) {
			$params ['NAME'] = $this->name;
		}

		$source = PreferenceTypeSource::getSource();
		$source->update ($params);

	}

	protected function delete () {
		$source = PreferenceTypeSource::getSource();
		$source->delete(array('ID' => $this->id));
	}

	public function preWrite () {}

	public function postWrite () {}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getName() == $other->getName());
	}

	public static function getOptions (Array $params = array()) {
		$source = PreferenceTypeSource::getSource();
		$options = array();
		foreach ($source->getOptions($params) as $row) {
			$options[$row['id']] = $row['name'];
		}
		return $options;
	}

	public function __toString () {
		return $this->name;
	}

}

?>