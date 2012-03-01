<?php

require_once 'source.inc';
require_once 'sources/commonsource.php';

class PreferenceTypeSource extends CommonSource implements Source {

	private static $instance = null;

	private function __construct () {
		parent::__construct();
	}

	public static function getSource () {

		if (self::$instance == null) {
			self::$instance = new PreferenceTypeSource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {

		$args = array();
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Insufficient read parameters provided.');
		} else {
			$args[] = new DbParam('preference_type.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT preference_type.id,
						preference_type.name
					FROM preference_type
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
			$args[] = new DbParam('preference_type.name', ':name', $params['NAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter name");
		}

		$sql = "INSERT INTO preference_type " . MySqlDB::getInsertCondition($args);
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
			$args[] = new DbParam('preference_type.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		if (sizeof($args)) {
			$sql = "UPDATE preference_type
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE preference_type.id = :id";
			$args[] = new DbParam('preference_type.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		return $this->deleteFromTableById('preference_type', $params['ID']);
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('NAME', $params)) {
			$args[] = new DbParam('preference_type.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		$sql = "SELECT DISTINCT
					preference_type.id,
					preference_type.name
				FROM preference_type
				" . (sizeof($args) > 0 ? 'WHERE ' . MySqlDB::getSelectConditions($args, ' AND ') : "") . "
				ORDER BY preference_type.name ASC";

		return $this->db->execSql($sql, $args);

	}

}
?>
