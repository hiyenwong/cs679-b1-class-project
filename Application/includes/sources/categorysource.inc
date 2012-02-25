<?php
include_once 'source.inc';

class CategorySource implements Source {

	private static $instance = null;

	private $db;
	private $readStatement;

	private function __construct () {
		$this->db = new MySqlDB();
		$this->readStatement = null;
	}

	public static function getSource () {

		if (self::$instance == null) {
			self::$instance = new UserSource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {

		$args = array();
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Insufficient read parameters provided.');
		} else {
			$args[] = new DbParam('category.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT category.id,
						category.name,
						category.user_id,
						category.active
					FROM category
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
			$args[] = new DbParam('category.name', ':name', $params['NAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter name");
		}

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('category.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}
		
		if (array_key_exists('ACTIVE', $params)) {
			$args[] = new DbParam('category.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO category " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		if ($this->lastInsertIdStatement == null) {
			$sql = "SELECT LAST_INSERT_ID() AS id";
			$this->lastInsertIdStatement = $this->db->getStatement($sql);
		}

		$results = $this->db->execStatement($this->lastInsertIdStatement);
		return $results[0]['id'];
	}

	public function update (Array $params) {

		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter user ID.');
		}

		$original = $this->read ($params);

		$args = array();

		if (array_key_exists('NAME', $params) && $original['name'] != $params['NAME']) {
			$args[] = new DbParam('category.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('USER_ID', $params) && $original['user_id'] != $params['USER_ID']) {
			$args[] = new DbParam('category.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}
		
		if (array_key_exists('ACTIVE', $params) && $original['active'] != $params['ACTIVE']) {
			$args[] = new DbParam('category.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		}

		if (sizeof($args)) {
			$sql = "UPDATE category
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE category.id = :id";
			$args[] = new DbParam('category.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter name ID.');
		}

		$args = array(new DbParam('category.id', ':id', $params['ID'], PDO::PARAM_INT));

		if ($this->selectCountStatement == null) {
			$sql = "SELECT COUNT(*) AS count FROM category WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
			$this->selectCountStatement = $this->db->getStatement($sql);
		}

		$result = $this->db->execStatement($this->selectCountStatement, $args);
		$count = $result[0]['count'];

		if ($count) {
			if ($this->deleteStatement == null) {
				$sql = "DELETE FROM category WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
				$this->deleteStatement = $this->db->getStatement($sql);
			}

			$this->db->execStatement($this->deleteStatement, $args);
		}

		return $count;
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();
		
		if (array_key_exists('NAME', $params)) {
			$args[] = new DbParam('category.name', ':name', $params['NAME'], PDO::PARAM_STR);
		}
		
		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('category.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}
		
		$sql = "SELECT DISTINCT
					category.id,
					category.name
				FROM category
				WHERE " . (array_key_exists('USER_ID', $params) ? MySqlDB::getSelectConditions($args, ' AND ') : 
								(sizeof($args) > 0 ? MySqlDB::getSelectConditions($args, ' AND ') . " AND " : "") . "category.user_id IS NULL") . "
				ORDER BY category.name ASC";
		
		return $this->db->execSql($sql, $args);
		
	}
	
}
?>
