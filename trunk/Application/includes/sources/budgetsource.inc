<?php

require_once 'source.inc';
require_once 'noresultexception.inc';
require_once 'sources/commonsource.inc';

class BudgetSource extends CommonSource implements Source {

	private static $instance = null;

	private function __construct () {
		$this->db = new MySqlDB();
		$this->readStatement = null;
		$this->lastInsertIdStatement = null;
		$this->selectCountStatement = null;
		$this->deleteStatement = null;
	}

	public static function getSource () {

		if (self::$instance == null) {
			self::$instance = new BudgetSource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {

		$args = array();
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Insufficient read parameters provided.');
		} else {
			$args[] = new DbParam('user_budget.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT user_budget.id,
						user_budget.user_id,
						user_budget.category_id,
						user_budget.amount,
						user_budget.active
					FROM user_budget
					WHERE " . MySqlDB::getSelectConditions($args, MySqlDB::$CONDITION_AND);

			$this->readStatement = $this->db->getStatement($sql);
		}

		$results = $this->db->execStatement($this->readStatement, $args);
		if (sizeof($results) == 0) {
			throw new NoResultException("No Result were found for ID: " . $params['ID']);
		} else if (sizeof($results) > 1) {
			throw new Exception(sizeof($results) . " Results were found for ID: " . $params['ID']);
		} else {
			return $results[0];
		}
	}

	public function insert(Array $params) {

		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('user_budget.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('CATEGORY_ID', $params)) {
			$args[] = new DbParam('user_budget.category_id', ':category_id', $params['CATEGORY_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter category id");
		}

		if (array_key_exists('AMOUNT', $params)) {
			$args[] = new DbParam('user_budget.amount', ':amount', $params['AMOUNT'], PDO::PARAM_INT);
		}

		if (array_key_exists('ACTIVE', $params)) {
			$args[] = new DbParam('user_budget.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO user_budget " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		return $this->getLastInsertedId();
	}

	public function update (Array $params) {

		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		$original = $this->read ($params);

		$args = array();

		if (array_key_exists('USER_ID', $params) && $original['user_id'] != $params['USER_ID']) {
			$args[] = new DbParam('user_budget.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('CATEGORY_ID', $params) && $original['category_id'] != $params['CATEGORY_ID']) {
			$args[] = new DbParam('user_budget.category_id', ':category_id', $params['CATEGORY_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('AMOUNT', $params) && $original['amount'] != $params['AMOUNT']) {
			$args[] = new DbParam('user_budget.amount', ':amount', $params['AMOUNT'], PDO::PARAM_INT);
		}

		if (array_key_exists('ACTIVE', $params) && $original['active'] != $params['ACTIVE']) {
			$args[] = new DbParam('user_budget.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		}

		if (sizeof($args)) {
			$sql = "UPDATE user_budget
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE user_budget.id = :id";
			$args[] = new DbParam('user_budget.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		return $this->deleteFromTableById('user_budget', $params['ID']);
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('user_budget.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('CATEGORY_ID', $params)) {
			$args[] = new DbParam('user_budget.category_id', ':category_id', $params['CATEGORY_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('ACTIVE', $params)) {
			$args[] = new DbParam('user_budget.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		}

		$sql = "SELECT DISTINCT
					user_budget.id,
					category.name,
					user_budget.category_id,
					user_budget.amount
				FROM user_budget
				JOIN category ON category.id = user_budget.category_id
				WHERE " . MySqlDB::getSelectConditions($args, ' AND ') . "
				ORDER BY category.name ASC";

		return $this->db->execSql($sql, $args);

	}

}
?>
