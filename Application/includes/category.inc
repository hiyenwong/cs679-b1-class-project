<?php

require_once 'user.inc';
require_once 'view.inc';
require_once 'factory.inc';
require_once 'comparable.inc';
require_once 'keys/categorykey.inc';
require_once 'sources/categorysource.inc';

class Category extends View implements Comparable {

	private $key;
	protected $id;

	private $name;
	private $user;
	private $active;

	public function __construct (CategoryKey $key) {
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

	public function getUser() {
		return $this->user;
	}

	public function isActive() {
		return $this->active;
	}



	public function setName($name) {
		$this->markModified();
		$this->name = $name;
	}

	public function setUser(User $user) {
		$this->markModified();
		$this->user = $user;
	}

	public function setActive($active) {
		$this->markModified();
		$this->active = $active;
	}




	public function read () {
		$source = CategorySource::getSource();
		$values = $source->read (array ('ID' => $this->id));

		$this->name = $values['name'];
		$this->user = $values['user_id'] ? Factory::getView(new UserKey($values['user_id'])) : null;
		$this->active = $values['active'];

	}

	protected function insert () {
		$params = array();

		if ($this->name) {
			$params ['NAME'] = $this->name;
		} else {
			throw new Exception ('User requires a userid.');
		}

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->active) {
			$params['ACTIVE'] = $this->active;
		}

		$source = CategorySource::getSource();
		$this->id = $source->insert ($params);

	}

	protected function update () {
		$params = array ();

		if ($this->name) {
			$params ['NAME'] = $this->name;
		}

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->active) {
			$params['ACTIVE'] = $this->active;
		}

		$source = CategorySource::getSource();
		$source->update ($params);

	}

	protected function delete () {
		$source = CategorySource::getSource();
		$source->delete(array('ID' => $this->id));
	}

	public function preWrite () {
		if (!$this->deleteRequested()) {
			if ($this->user) {
				$this->user->write();
			}
		}
	}

	public function postWrite () {}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getName() == $other->getName() &&
				$this->getUser()->equals($other->getUser()) &&
				$this->isActive() == $other->isActive());
	}

	public static function getOptions (Array $params = array()) {
		$source = CategorySource::getSource();
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