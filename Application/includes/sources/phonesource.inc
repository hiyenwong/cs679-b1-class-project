<?php

require_once 'source.inc';
require_once 'sources/commonsource.php';

class PhoneSource extends CommonSource implements Source {

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
			self::$instance = new PhoneSource();
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
			$args[] = new DbParam('phone.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter user id");
		}

		if (array_key_exists('PHONE', $params)) {
			$args[] = new DbParam('phone.phone', ':phone', $params['PHONE'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter phone");
		}

		if (array_key_exists('TEXT_ABLE', $params)) {
			$args[] = new DbParam('phone.text_able', ':text_able', $params['TEXT_ABLE'], PDO::PARAM_BOOL);
		} else {
			throw new Exception("Missing required parameter Textable");
		}

		if (array_key_exists('IS_PRIMARY', $params)) {
			$args[] = new DbParam('phone.primary', ':primary', $params['IS_PRIMARY'], PDO::PARAM_BOOL);
		} else {
			throw new Exception("Missing required parameter is primary");
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO phone " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		return $this->getLastInsertedId();
	}

	public function update (Array $params) {
		throw new Exception("Update is not implemented");
	}

	public function delete (Array $params) {
		if (!array_key_exists ('USER_ID', $params)) {
			throw new Exception ('Missing required parameter user id.');
		}

		return $this->deleteFromTableById('phone', $params['USER_ID'], 'user_id');
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if (array_key_exists('USER_ID', $params)) {
			$args[] = new DbParam('phone.user_id', ':user_id', $params['USER_ID'], PDO::PARAM_INT);
		}

		if (array_key_exists('TEXT_ABLE', $params)) {
			$args[] = new DbParam('phone.text_able', ':text_able', $params['TEXT_ABLE'], PDO::PARAM_BOOL);
		}

		if (array_key_exists('IS_PRIMARY', $params)) {
			$args[] = new DbParam('phone.is_primary', ':is_primary', $params['IS_PRIMARY'], PDO::PARAM_BOOL);
		}

		$sql = "SELECT DISTINCT
					phone.phone,
					phone.text_able,
					phone.is_primary
				FROM phone
				WHERE " . (array_key_exists('USER_ID', $params) ? MySqlDB::getSelectConditions($args, ' AND ') :
								(sizeof($args) > 0 ? MySqlDB::getSelectConditions($args, ' AND ') . " AND " : "") . "phone.user_id IS NULL") . "
				ORDER BY phone.name ASC";

		return $this->db->execSql($sql, $args);

	}

}
?>
