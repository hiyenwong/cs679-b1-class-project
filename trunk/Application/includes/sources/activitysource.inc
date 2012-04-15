<?php

require_once 'source.inc';
require_once 'noresultexception.inc';
require_once 'sources/commonsource.inc';

class ActivitySource extends CommonSource implements Source {

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
			self::$instance = new ActivitySource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {

		$args = array();
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Insufficient read parameters provided.');
		} else {
			$args[] = new DbParam('activity.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT activity.id,
						activity.user_id,
						activity.name,
						activity.custom_name,
						activity.amount,
						activity.transaction_date,
						activity.category_id,
						activity.comment,
						activity.import_number,
						activity.import_time
					FROM activity
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
			$args[] = new DbParam('activity.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user_id");
		}

		if (array_key_exists('NAME', $params)) {
			$args[] = new DbParam('activity.name', ':name', $params['NAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter name");
		}

		if (array_key_exists('CUSTOM_NAME', $params)) {
			$args[] = new DbParam('activity.custom_name', ':custom_name', $params['CUSTOM_NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('AMOUNT', $params)) {
			$args[] = new DbParam('activity.amount', ':amount', $params['AMOUNT'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter amount");
		}

		if (array_key_exists('TRANSACTION_DATE', $params)) {
			$args[] = new DbParam('activity.transaction_date', ':transaction_date', $params['TRANSACTION_DATE'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter transaction date");
		}

		if (array_key_exists('CATEGORY_ID', $params)) {
			$args[] = new DbParam('activity.category_id', ':category_id', $params['CATEGORY_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('COMMENT', $params)) {
			$args[] = new DbParam('activity.comment', ':comment', $params['COMMENT'], PDO::PARAM_STR);
		}
		
		if (array_key_exists('IMPORT_NUMBER', $params)) {
			$args[] = new DbParam('activity.import_number', ':import_number', $params['IMPORT_NUMBER'], PDO::PARAM_INT);
		} else {
			throw new Exception("Mising required parameter import number");
		}
		
		if (array_key_exists('IMPORT_TIME', $params)) {
			$args[] = new DbParam('activity.import_time', ':import_time', $params['IMPORT_TIME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Mising required parameter import time");
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO activity " . MySqlDB::getInsertCondition($args);
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
			$args[] = new DbParam('activity.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('NAME', $params) && $original['name'] != $params['NAME']) {
			$args[] = new DbParam('activity.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('CUSTOM_NAME', $params) && $original['custom_name'] != $params['CUSTOM_NAME']) {
			$args[] = new DbParam('activity.custom_name', ':custom_name', $params['CUSTOM_NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('AMOUNT', $params) && $original['amount'] != $params['AMOUNT']) {
			$args[] = new DbParam('activity.amount', ':amount', $params['AMOUNT'], PDO::PARAM_INT);
		}

		if (array_key_exists('TRANSACTION_DATE', $params) && $original['transaction_date'] != $params['TRANSACTION_DATE']) {
			$args[] = new DbParam('activity.transaction_date', ':transaction_date', $params['TRANSACTION_DATE'], PDO::PARAM_STR);
		}

		if (array_key_exists('CATEGORY_ID', $params) && $original['category_id'] != $params['CATEGORY_ID']) {
			$args[] = new DbParam('activity.category_id', ':category_id', $params['CATEGORY_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('COMMENT', $params) && $original['comment'] != $params['COMMENT']) {
			$args[] = new DbParam('activity.comment', ':comment', $params['COMMENT'], PDO::PARAM_STR);
		}

		if (sizeof($args)) {
			$sql = "UPDATE activity
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE activity.id = :id";
			$args[] = new DbParam('activity.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		return $this->deleteFromTableById('activity', $params['ID']);
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('activity.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('NAME', $params)) {
			$args[] = new DbParam('activity.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('CUSTOM_NAME', $params)) {
			$args[] = new DbParam('activity.custom_name', ':custom_name', $params['CUSTOM_NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('TRANSACTION_DATE', $params)) {
			$args[] = new DbParam('activity.transaction_date', ':transaction_date', $params['TRANSACTION_DATE'], PDO::PARAM_STR);
		}
		
		if (array_key_exists('IMPORT_NUMBER', $params)) {
			$args[] = new DbParam('activity.import_number', ':import_number', $params['IMPORT_NUMBER'], PDO::PARAM_INT);
		}
		
		if (array_key_exists('IMPORT_TIME', $params)) {
			$args[] = new DbParam('activity.import_time', ':import_time', $params['IMPORT_TIME'], PDO::PARAM_STR);
		}
		
		if (array_key_exists('TRANSACTION_DATE_START', $params)) {
			$args[] = new DbParam('activity.transaction_date', ':transaction_date', $params['TRANSACTION_DATE'], PDO::PARAM_STR, '>=');
		}
		
        if (array_key_exists('TRANSACTION_DATE_END', $params)) {
			$args[] = new DbParam('activity.transaction_date', ':transaction_date', $params['TRANSACTION_DATE'], PDO::PARAM_STR, '<=');
		}

		$sql = "SELECT DISTINCT
					activity.id,
					IF (activity.custom_name IS NOT NULL, activity.custom_name, activity.name) AS name,
					activity.transaction_date,
					activity.amount
				FROM activity
				WHERE " . MySqlDB::getSelectConditions($args, ' AND ') . "
				ORDER BY activity.transaction_date DESC";

		return $this->db->execSql($sql, $args);

	}

}
?>
