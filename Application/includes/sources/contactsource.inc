<?php

require_once 'source.inc';
require_once 'sources/commonsource.php';

class ContactSource extends CommonSource implements Source {

	private static $instance = null;

	private function __construct () {
		parent::__construct();
	}

	public static function getSource () {

		if (self::$instance == null) {
			self::$instance = new ContactSource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {

		$args = array();
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Insufficient read parameters provided.');
		} else {
			$args[] = new DbParam('contact.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT contact.id,
						contact.user_id,
						contact.email,
						contact.date_submitted,
						contact.content
					FROM contact
					WHERE " . MySqlDB::getSelectConditions($args, MySqlDB::$CONDITION_AND);

			$this->readStatement = $this->db->getStatement($sql);
		}

		$results = $this->db->execStatement($this->readStatement, $args);
		if (sizeof($results) == 0) {
			throw new Exception("No Result were found for ID: " . $params['ID']);
		} else if (sizeof($results) > 1) {
			throw new Exception(sizeof($results) . " Results were found for ID: " . $params['ID']);
		} else {
			return $results[0];
		}
	}

	public function insert(Array $params) {

		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('contact.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('EMAIL', $params)) {
			$args[] = new DbParam('contact.email', ':email', $params['EMAIL'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter email");
		}

		if (array_key_exists('DATE_SUBMITTED', $params)) {
			$args[] = new DbParam('contact.date_submitted', ':date_submitted', $params['DATE_SUBMITTED'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter date submitted");
		}

		if (array_key_exists('CONTENT', $params)) {
			$args[] = new DbParam('contact.content', ':content', $params['CONTENT'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter content");
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO contact " . MySqlDB::getInsertCondition($args);
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
			$args[] = new DbParam('contact.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('EMAIL', $params) && $original['email'] != $params['EMAIL']) {
			$args[] = new DbParam('contact.email', ':email', $params['EMAIL'], PDO::PARAM_STR);
		}

		if (array_key_exists('DATE_SUBMITTED', $params) && $original['date_submitted'] != $params['DATE_SUBMITTED']) {
			$args[] = new DbParam('contact.date_submitted', ':date_submitted', $params['DATE_SUBMITTED'], PDO::PARAM_STR);
		}

		if (array_key_exists('CONTENT', $params) && $original['content'] != $params['CONTENT']) {
			$args[] = new DbParam('contact.content', ':content', $params['CONTENT'], PDO::PARAM_STR);
		}

		if (sizeof($args)) {
			$sql = "UPDATE contact
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE contact.id = :id";
			$args[] = new DbParam('contact.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		return $this->deleteFromTableById('contact', $params['ID']);
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('EMAIL', $params)) {
			$args[] = new DbParam('contact.email', ':email', $params['EMAIL'], PDO::PARAM_STR);
		}

		if (array_key_exists('DATE_SUBMITTED', $params)) {
			$args[] = new DbParam('contact.date_submitted', ':date_submitted', $params['DATE_SUBMITTED'], PDO::PARAM_STR);
		}

		$sql = "SELECT DISTINCT
					contact.id,
					contact.user_id,
					contact.email,
					contact.date_submitted,
					contact.content
				FROM contact
				" . (sizeof($args) > 0 ? 'WHERE ' . MySqlDB::getSelectConditions($args, ' AND ') : '') . "
				ORDER BY contact.date_submitted DESC";

		return $this->db->execSql($sql, $args);
	}

}
?>
