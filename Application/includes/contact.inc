<?php

require_once 'user.inc';
require_once 'view.inc';
require_once 'factory.inc';
require_once 'comparable.inc';
require_once 'keys/contactkey.inc';
require_once 'sources/contactsource.inc';

class Contact extends View implements Comparable {

	private $key;
	protected $id;

	private $name;
	private $user;
	private $email;
	private $dateSubmitted;
	private $content;

	public function __construct (ContactKey $key) {
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

	public function getEmail() {
		return $this->email;
	}

	public function getDateSubmitted() {
		return $this->dateSubmitted;
	}

	public function getContent() {
		return $this->content;
	}



	public function setName($name) {
		$this->markModified();
		$this->name = $name;
	}

	public function setUser(User $user) {
		$this->markModified();
		$this->user = $user;
	}

	public function setEmail($email) {
		$this->markModified();
		$this->email = $email;
	}

	public function setDateSubmitted(Date $dateSubmitted) {
		$this->markModified();
		$this->dateSubmitted = $dateSubmitted;
	}

	public function setContent($content) {
		$this->markModified();
		$this->content = $content;
	}



	public function read () {
		$source = ContactSource::getSource();
		$values = $source->read (array ('ID' => $this->id));

		$this->name = $values['name'];
		$this->user = $values['user_id'] ? Factory::getView(new UserKey($values['user_id'])) : null;
		$this->email = $values['email'];
		$this->dateSubmitted = new Date($values['date_submitted']);
		$this->content = $values['content'];

	}

	protected function insert () {
		$params = array();

		if ($this->name) {
			$params['NAME'] = $this->name;
		} else {
			throw new Exception("Contact requires a name");
		}

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->email) {
			$params ['EMAIL'] = $this->email;
		} else {
			throw new Exception ('Contact requires an email.');
		}

		if ($this->dateSubmitted) {
			$params['DATE_SUBMITTED'] = $this->dateSubmitted;
		} else {
			throw new Exception ('Contact requires a submittion date.');
		}

		if ($this->content) {
			$params['CONTENT'] = $this->content;
		} else {
			throw new Exception ('Contact requires content.');
		}

		$source = ContactSource::getSource();
		$this->id = $source->insert ($params);

	}

	protected function update () {
		$params = array ();

		if ($this->name) {
			$params['NAME'] = $this->name;
		}

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->email) {
			$params ['EMAIL'] = $this->email;
		}

		if ($this->dateSubmitted) {
			$params['DATE_SUBMITTED'] = $this->dateSubmitted;
		}

		if ($this->content) {
			$params['CONTENT'] = $this->content;
		}

		$source = ContactSource::getSource();
		$source->update ($params);

	}

	protected function delete () {
		$source = ContactSource::getSource();
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

		return ($this->getEmail() == $other->getEmail() &&
				$this->getUser()->equals($other->getUser()) &&
				$this->getDateSubmitted() == $other->getDateSubmitted() &&
				$this->getContent() == $other->getContent());
	}

	public static function getOptions (Array $params = array()) {
		$source = ContactSource::getSource();
		$options = array();
		foreach ($source->getOptions($params) as $row) {
			$options[$row['id']] = $row['email'] . " - " . $row['date_submitted'];
		}
		return $options;
	}

	public function __toString () {
		return $row['email'] . " - " . $row['date_submitted'];
	}

}

?>