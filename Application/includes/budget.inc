<?php

require_once 'user.inc';
require_once 'category.inc';
require_once 'view.inc';
require_once 'factory.inc';
require_once 'comparable.inc';
require_once 'keys/budgetkey.inc';
require_once 'sources/budgetsource.inc';

class Budget extends View implements Comparable {

	private $key;
	protected $id;

	private $user;
	private $category;
	private $amount;
	private $active;

	public function __construct (BudgetKey $key) {
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

	public function getAmount() {
		return $this->amount;
	}

	public function isActive() {
		return $this->active;
	}



	public function setUser(User $user) {
		$this->markModified();
		$this->user = $user;
	}

	public function setCategory(Category $category) {
		$this->markModified();
		$this->category = $category;
	}

	public function setAmount($amount) {
		$this->markModified();
		$this->amount = $amount;
	}

	public function setActive($active) {
		$this->markModified();
		$this->active = $active;
	}




	public function read () {
		$source = BudgetSource::getSource();
		$values = $source->read (array ('ID' => $this->id));

		$this->user = Factory::getView(new UserKey($values['user_id']));
		$this->category = Factory::getView(new CategoryKey($values['category_id']));
		$this->amount = $values['amount'];
		$this->active = $values['active'];

	}

	protected function insert () {
		$params = array();

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		} else {
			throw new Exception ('Budget requires a user id.');
		}

		if ($this->category) {
			$params['CATEGORY_ID'] = $this->category->getId();
		} else {
			throw new Exception ('Budget requires a category id.');
		}

		if ($this->amount) {
			$params['AMOUNT'] = $this->amount;
		}

		if ($this->active) {
			$params['ACTIVE'] = $this->active;
		}

		$source = BudgetSource::getSource();
		$this->id = $source->insert ($params);

	}

	protected function update () {
		$params = array ();

        $params['ID'] = $this->id;
        
		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->category) {
			$params['CATEGORY_ID'] = $this->category->getId();
		}

		if ($this->amount) {
			$params['AMOUNT'] = $this->amount;
		}

		if (isset($this->active)) {
			$params['ACTIVE'] = $this->active;
		}

		$source = BudgetSource::getSource();
		$source->update ($params);
	}

	protected function delete () {
		$source = BudgetSource::getSource();
		$source->delete(array('ID' => $this->id));
	}

	public function preWrite () {
		if (!$this->deleteRequested()) {
			$this->user->write();
			$this->category->write();
		}
	}

	public function postWrite () {}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getUser()->equals($other->getUser()) &&
				$this->getCategory()->equals($other->getCategory()) &&
				$this->getAmount() == $other->getAmount() &&
				$this->isActive() == $other->isActive());
	}

	public static function getOptions (Array $params = array()) {
		$source = BudgetSource::getSource();
		$options = array();
		foreach ($source->getOptions($params) as $row) {
			//$options[$row['id']] = $row['name'] . ' - ' . $row['amount'];
			$options[$row['id']] = array("name" => $row['name'], "amount" => $row['amount'], "category_id" => $row['category_id']);
		}
		return $options;
	}

	public function __toString () {
		return $this->getCategory()->getName() . ' - ' . $this->getAmount();
	}

}

?>