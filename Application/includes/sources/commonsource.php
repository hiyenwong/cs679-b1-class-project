<?php

class CommonSource {

	protected $db;
	protected $readStatement;
	protected $lastInsertIdStatement;
	protected $selectCountStatement;
	protected $deleteStatement;

	protected function __construct () {
		$this->db = new MySqlDB();
		$this->readStatement = null;
		$this->lastInsertIdStatement = null;
		$this->selectCountStatement = null;
		$this->deleteStatement = null;
	}

	/**
	 * Query the database and get the id of the last insert statement
	 */
	public function getLastInsertedId() {
		if ($this->lastInsertIdStatement == null) {
			$sql = "SELECT LAST_INSERT_ID() AS id";
			$this->lastInsertIdStatement = $this->db->getStatement($sql);
		}

		$results = $this->db->execStatement($this->lastInsertIdStatement);
		return $results[0]['id'];
	}

	/**
	 * Delete a row from defined table by the id
	 * @param unknown_type $table
	 * @param unknown_type $id
	 * @throws Exception Missing required ID
	 */
	public function deleteFromTableById($table, $id) {
		if (!$id) {
			throw new Exception ('Missing required parameter ID.');
		}

		$args = array(new DbParam($table.'.id', ':id', $id, PDO::PARAM_INT));

		if ($this->selectCountStatement == null) {
			$sql = "SELECT COUNT(*) AS count FROM ' . $table . ' WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
			$this->selectCountStatement = $this->db->getStatement($sql);
		}

		$result = $this->db->execStatement($this->selectCountStatement, $args);
		$count = $result[0]['count'];

		if ($count) {
			if ($this->deleteStatement == null) {
				$sql = 'DELETE FROM ' . $table . ' WHERE ' . MySqlDB::getSelectConditions($args, ' AND ');
				$this->deleteStatement = $this->db->getStatement($sql);
			}

			$this->db->execStatement($this->deleteStatement, $args);
		}

		return $count;
	}



}


?>