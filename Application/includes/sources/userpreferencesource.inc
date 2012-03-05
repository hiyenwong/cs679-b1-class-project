<?php

require_once 'source.inc';
require_once 'sources/commonsource.inc';

class UserPreferenceSource extends CommonSource implements Source {

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
			self::$instance = new UserPreferenceSource();
		}

		return self::$instance;
	}

	/******************** Database Operations ********************/

	public function read (Array $params) {
		throw new Exception("Read is not implemented");
	}

	public function insert(Array $params) {

		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('user_preference.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('PREFERENCE_TYPE_ID', $params)) {
			$args[] = new DbParam('user_preference.preference_type_id', ':preference_type_id', $params['PREFERENCE_TYPE_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter preference type id");
		}

		$sql = "INSERT INTO user_preference " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		return $this->getLastInsertedId();
	}

	public function update (Array $params) {
		throw new Exception("Update is not implemented");
	}

	public function delete (Array $params) {
		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('user_preference.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('PREFERENCE_TYPE_ID', $params)) {
			$args[] = new DbParam('user_preference.preference_type_id', ':preference_type_id', $params['PREFERENCE_TYPE_ID'], PDO::PARAM_INT);
		}

		if ($this->selectCountStatement == null) {
			$sql = "SELECT COUNT(*) AS count FROM user_preference WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
			$this->selectCountStatement = $this->db->getStatement($sql);
		}

		$result = $this->db->execStatement($this->selectCountStatement, $args);
		$count = $result[0]['count'];

		if ($count) {
			if ($this->deleteStatement == null) {
				$sql = 'DELETE FROM user_preference WHERE ' . MySqlDB::getSelectConditions($args, ' AND ');
				$this->deleteStatement = $this->db->getStatement($sql);
			}

			$this->db->execStatement($this->deleteStatement, $args);
		}

		return $count;
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('user_preference.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('PREFERENCE_TYPE_ID', $params)) {
			$args[] = new DbParam('user_preference.preference_type_id', ':preference_type_id', $params['PREFERENCE_TYPE_ID'], PDO::PARAM_INT);
		}

		$sql = "SELECT DISTINCT
					user_preference.user_id,
					preference_type.name
				FROM user_preference
				JOIN preference_type ON preference_type.id = user_preference.preference_type_id
				WHERE " . MySqlDB::getSelectConditions($args, ' AND ') . "
				ORDER BY preference_type.name ASC";

		return $this->db->execSql($sql, $args);

	}

}
?>
