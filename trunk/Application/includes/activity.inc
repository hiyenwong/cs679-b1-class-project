<?php

require_once 'user.inc';
require_once 'category.inc';
require_once 'view.inc';
require_once 'factory.inc';
require_once 'comparable.inc';
require_once 'keys/activitykey.inc';
require_once 'sources/activitysource.inc';

class Activity extends View implements Comparable {

	private $key;
	protected $id;

	private $user;
	private $category;
	private $name;
	private $customName;
	private $amount;
	private $transactionDate;
	private $comment;

	public function __construct (ActivityKey $key) {
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

	public function getUser() {
		return $this->user;
	}

	public function getCategory() {
		return $this->category;
	}

	public function getName() {
		return $this->name;
	}

	public function getCustomName() {
		return $this->customName;
	}

	public function getAmount() {
		return $this->amount;
	}

	public function getTransactionDate() {
		return $this->transactionDate;
	}

	public function getComment() {
		return $this->comment;
	}



	public function setUser(User $user) {
		$this->markModified();
		$this->user = $user;
	}

	public function setCategory(Category $category) {
		$this->markModified();
		$this->category = $category;
	}

	public function setName($name) {
		$this->markModified();
		$this->name = $name;
	}

	public function setCustomName($customName) {
		$this->markModified();
		$this->customName = $customName;
	}

	public function setAmount($amount) {
		$this->markModified();
		$this->amount = $amount;
	}

	public function setTransactionDate(Date $transactionDate) {
		$this->markModified();
		$this->transactionDate = $transactionDate;
	}

	public function setComment($comment) {
		$this->markModified();
		$this->comment = $comment;
	}



	public function read () {
		$source = ActivitySource::getSource();
		$values = $source->read (array ('ID' => $this->id));

		$this->user = Factory::getView(new UserKey($values['user_id']));
		$this->category = $values['category_id'] ? Factory::getView(new CategoryKey($values['category_id'])) : null;
		$this->name = $values['name'];
		$this->customName = $values['custom_name'];
		$this->amount = $values['amount'];
		$this->transactionDate = new Date($values['transaction_date']);
		$this->comment = $values['comment'];

	}

	protected function insert () {
		$params = array();

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		} else {
			throw new Exception ('Missing required parameter user id.');
		}

		if ($this->category) {
			$params['CATEGORY_ID'] = $this->category->getId();
		}

		if ($this->name) {
			$params ['NAME'] = $this->name;
		} else {
			throw new Exception ('Missing required parameter name.');
		}

		if ($this->customName) {
			$params ['CUSTOM_NAME'] = $this->customName;
		}

		$params ['AMOUNT'] = $this->amount ? $this->amount : 0;

		if ($this->transactionDate) {
			$params ['TRANSACTION_DATE'] = $this->transactionDate;
		} else {
			throw new Exception("Missing required parameter transaction date");
		}

		if ($this->comment) {
			$params ['COMMENT'] = $this->comment;
		}

		$source = ActivitySource::getSource();
		$this->id = $source->insert ($params);

	}

	protected function update () {
		$params = array();

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->category) {
			$params['CATEGORY_ID'] = $this->category->getId();
		}

		if ($this->name) {
			$params ['NAME'] = $this->name;
		}

		if ($this->customName) {
			$params ['CUSTOM_NAME'] = $this->customName;
		}

		$params ['AMOUNT'] = $this->amount ? $this->amount : 0;

		if ($this->transactionDate) {
			$params ['TRANSACTION_DATE'] = $this->transactionDate;
		}

		if ($this->comment) {
			$params ['COMMENT'] = $this->comment;
		}

		$source = ActivitySource::getSource();
		$source->update ($params);

	}

	protected function delete () {
		$source = ActivitySource::getSource();
		$source->delete(array('ID' => $this->id));
	}

	public function preWrite () {
		if (!$this->deleteRequested()) {
			$this->user->write();

			if ($this->category) {
				$this->category->write();
			}
		}
	}

	public function postWrite () {}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getId() == $other->getId());
	}

	public static function getOptions (Array $params = array()) {
		$source = ActivitySource::getSource();
		$options = array();
		foreach ($source->getOptions($params) as $row) {
			$options[$row['id']] = $row['name'];
		}
		return $options;
	}

	public function __toString () {
		return $this->transactionDate->format(Date::$DATE_TIME) . ' : ' .
					($this->customName ? $this->customName : $this->name) . ' - ' . $this->getAmount();
	}

}

?>