<?php

require_once 'errors.inc';
require_once 'dbparam.inc';

class MySqlDB {

	public static $CONDITION_AND = ' AND ';
	public static $CONDITION_OR = ' OR ';

	private $CONNECTION;

	public function __construct() {
		GLOBAL $DBHOST;
		GLOBAL $DBNAME;
		GLOBAL $DBUSER;
		GLOBAL $DBPASSWD;
		try {
			$this->CONNECTION = new PDO('mysql:host='.$DBHOST.';dbname='.$DBNAME, $DBUSER, $DBPASSWD);
			$this->CONNECTION->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
			// $this->CONNECTION->setAttribute(PDO::ATTR_PERSISTENT, false);
			// $this->CONNECTION->setAttribute(PDO::MYSQL_ATTR_INIT_COMMAND, "SET NAMES utf8");
		} catch (PDOException $e) {
			trigger_error ($e->getMessage(), E_USER_ERROR);
		}
	}

	public function getStatement($sql) {
		return $this->CONNECTION->prepare($sql);
	}

	public function execSql(String $sql, Array $params = null) {
		$statement = $this->getStatement($sql);
		return $this->execStatement($statement, $params);
	}

	public function execStatement(PDOStatement $statement, Array $params = null) {
		try {
			foreach ($params as $p) {
				$statement->bindParam($p->getId(), $p->getValue(), $p->getType());
			}

			$statement->execute();
			$result = $statement->fetchAll();
			return $result;

		} catch (Exception $e) {
			trigger_error ($e->getMessage(), E_USER_ERROR);
		}
	}

	public function startTransaction() {
		$this->CONNECTION->beginTransaction();
	}

	public function commitTransaction() {
		$this->CONNECTION->commit();
	}

	public function rollbackTransaction() {
		$this->CONNECTION->rollBack();
	}



	public static function getSelectConditions(Array $args, $condition = ' AND ') {
		return implode($condition, $args);
	}

	public static function getInsertCondition(Array $args) {
		$columns = array();
		$params = array();

		foreach ($args as $a) {
			$columns[] = $a->getColumn();
			$params[] = $a->getId();
		}

		return "(" . implode (', ', $columns) . ") VALUES (" . implode (', ', $params) . ")";
	}

}

?>
