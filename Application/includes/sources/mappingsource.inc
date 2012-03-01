<?php

require_once 'source.inc';
require_once 'sources/commonsource.php';

class MappingSource extends CommonSource implements Source {

	private static $instance = null;

	private function __construct () {
		parent::__construct();
	}

	public static function getSource () {

		if (self::$instance == null) {
			self::$instance = new MappingSource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {

		$args = array();
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Insufficient read parameters provided.');
		} else {
			$args[] = new DbParam('mapping.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT mapping.id,
						mapping.name,
						mapping.user_id,
						mapping.starting_row
					FROM mapping
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

		if (array_key_exists('NAME', $params)) {
			$args[] = new DbParam('mapping.name', ':name', $params['NAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter name");
		}

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('mapping.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('STARTING_ROW', $params)) {
			$args[] = new DbParam('mapping.starting_row', ':starting_row', $params['STARTING_ROW'], PDO::PARAM_INT);
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO mapping " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		return $this->getLastInsertedId();
	}

	public function update (Array $params) {

		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		$original = $this->read ($params);

		$args = array();

		if (array_key_exists('NAME', $params) && $original['name'] != $params['NAME']) {
			$args[] = new DbParam('mapping.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('USER_ID', $params) && $original['user_id'] != $params['USER_ID']) {
			$args[] = new DbParam('mapping.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('STARTING_ROW', $params) && $original['starting_row'] != $params['STARTING_ROW']) {
			$args[] = new DbParam('mapping.starting_row', ':starting_row', $params['STARTING_ROW'], PDO::PARAM_INT);
		}

		if (sizeof($args)) {
			$sql = "UPDATE mapping
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE mapping.id = :id";
			$args[] = new DbParam('mapping.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		return $this->deleteFromTableById('mapping', $params['ID']);
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('NAME', $params)) {
			$args[] = new DbParam('mapping.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('mapping.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		$sql = "SELECT DISTINCT
					mapping.id,
					mapping.name
				FROM mapping
				WHERE " . (array_key_exists('USER_ID', $params) ? MySqlDB::getSelectConditions($args, ' AND ') :
								(sizeof($args) > 0 ? MySqlDB::getSelectConditions($args, ' AND ') . " AND " : "") . "mapping.user_id IS NULL") . "
				ORDER BY mapping.name ASC";

		return $this->db->execSql($sql, $args);

	}

}
?>
