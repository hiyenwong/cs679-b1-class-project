<?php
include_once 'source.inc';

class MappingDetailSource implements Source {

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
		throw new Exception("Read is not implemented");
	}

	public function insert(Array $params) {

		$args = array();

		if (array_key_exists('MAPPING_ID', $params)) {
			$args[] = new DbParam('mapping_detail.mapping_id', ':mapping_id', $params['MAPPING_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter mapping id");
		}

		if (array_key_exists('COLUMN_NAME', $params)) {
			$args[] = new DbParam('mapping_detail.column_name', ':column_name', $params['COLUMN_NAME'], PDO::PARAM_STR);
		}
		
		if (array_key_exists('CSV_COLUMN_NUMBER', $params)) {
			$args[] = new DbParam('mapping_detail.csv_column_number', ':csv_column_number', $params['CSV_COLUMN_NUMBER'], PDO::PARAM_INT);
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO mapping_detail " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		if ($this->lastInsertIdStatement == null) {
			$sql = "SELECT LAST_INSERT_ID() AS id";
			$this->lastInsertIdStatement = $this->db->getStatement($sql);
		}

		$results = $this->db->execStatement($this->lastInsertIdStatement);
		return $results[0]['id'];
	}

	public function update (Array $params) {
		throw new Exception("Update is not implemented");
	}

	public function delete (Array $params) {
		if (!array_key_exists ('MAPPING_ID', $params)) {
			throw new Exception ('Missing required parameter mapping ID.');
		}

		$args = array(new DbParam('mapping_detail.mapping_id', ':mapping_id', $params['MAPPING_ID'], PDO::PARAM_INT));

		if ($this->selectCountStatement == null) {
			$sql = "SELECT COUNT(*) AS count FROM mapping_detail WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
			$this->selectCountStatement = $this->db->getStatement($sql);
		}

		$result = $this->db->execStatement($this->selectCountStatement, $args);
		$count = $result[0]['count'];

		if ($count) {
			if ($this->deleteStatement == null) {
				$sql = "DELETE FROM mapping_detail WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
				$this->deleteStatement = $this->db->getStatement($sql);
			}

			$this->db->execStatement($this->deleteStatement, $args);
		}

		return $count;
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();
		
		if (array_key_exists('MAPPING_ID', $params)) {
			$args[] = new DbParam('mapping_detail.mapping_id', ':mapping_id', $params['MAPPING_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter mapping id");
		}
		
		$sql = "SELECT DISTINCT
					mapping_detail.column_name,
					mapping_detail.csv_column_number
				FROM mapping_detail
				WHERE " . MySqlDB::getSelectConditions($args, ' AND ') . "
				ORDER BY mapping_detail.csv_column_number ASC";
		
		return $this->db->execSql($sql, $args);
		
	}
	
}
?>
