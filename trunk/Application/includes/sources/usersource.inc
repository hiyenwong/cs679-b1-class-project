<?php

require_once 'source.inc';
require_once 'date.inc';
require_once 'userdoesnotexistexception.inc';
require_once 'toomanyfailedloginexception.inc';
require_once 'accessdeniedexception.inc';
require_once 'noresultexception.inc';
require_once 'sources/commonsource.php';

class UserSource extends CommonSource implements Source {

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
			$args[] = new DbParam('user.id', ':id', $params['ID'], PDO::PARAM_INT);
		}

		if ($this->readStatement == null) {
			$sql = "SELECT user.id,
						user.username,
						user.active,
						user.created_date,
						user.last_login_date,
						user.number_of_attempts,
						user_profile.first_name,
						user_profile.last_name,
						user_profile.address,
						user_profile.city,
						user_profile.zip,
						user_profile.state,
						user_profile.country
					FROM user
					JOIN user_profile ON user_profile.user_id = user.id
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

		if (array_key_exists('USERNAME', $params)) {
			$args[] = new DbParam('user.username', ':username', $params['USERNAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter username");
		}

		if (array_key_exists('PASSWORD', $params)) {
			$args[] = new DbParam('user.password', ':password', $params['PASSWORD'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter password");
		}

		if (array_key_exists('ACTIVE', $params)) {
			$args[] = new DbParam('user.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		} else {
			throw new Exception("Missing required parameter active");
		}

		if (array_key_exists('CREATE_DATE', $params)) {
			$args[] = new DbParam('user.create_date', ':create_date', $params['CREATE_DATE'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter create date");
		}

		if (array_key_exists('LAST_LOGIN_DATE', $params)) {
			$args[] = new DbParam('user.last_login_date', ':last_login_date', $params['LAST_LOGIN_DATE'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter last login date");
		}

		if (array_key_exists('NUMBER_OF_ATTEMPTS', $params)) {
			$args[] = new DbParam('user.number_of_attempts', ':number_of_attempts', $params['NUMBER_OF_ATTEMPTS'], PDO::PARAM_INT);
		} else {
			throw new Exception("Missing required parameter number of attempts");
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO user " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		$id = $this->getLastInsertedId();

		$args = array(new DbParam('user_profile.user_id', ':user_id', $id, PDO::PARAM_INT));

		if (array_key_exists('FIRST_NAME', $params)) {
			$args[] = new DbParam('user_profile.first_name', ':first_name', $params['FIRST_NAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter first name");
		}

		if (array_key_exists('LAST_NAME', $params)) {
			$args[] = new DbParam('user_profile.last_name', ':last_name', $params['LAST_NAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter last name");
		}

		if (array_key_exists('ADDRESS', $params)) {
			$args[] = new DbParam('user_profile.address', ':address', $params['ADDRESS'], PDO::PARAM_STR);
		}

		if (array_key_exists('CITY', $params)) {
			$args[] = new DbParam('user_profile.city', ':city', $params['CITY'], PDO::PARAM_STR);
		}

		if (array_key_exists('ZIP', $params)) {
			$args[] = new DbParam('user_profile.zip', ':zip', $params['ZIP'], PDO::PARAM_STR);
		}

		if (array_key_exists('STATE', $params)) {
			$args[] = new DbParam('user_profile.state', ':state', $params['STATE'], PDO::PARAM_STR);
		}

		if (array_key_exists('COUNTRY', $params)) {
			$args[] = new DbParam('user_profile.country', ':country', $params['COUNTRY'], PDO::PARAM_STR);
		}

		if (!sizeof($args)) {
			throw new Exception ('Missing all parameters.');
		}

		$sql = "INSERT INTO user_profile " . MySqlDB::getInsertCondition($args);
		$this->db->execSql($sql, $args);

		return $id;
	}

	public function update (Array $params) {

		if (!array_key_exists ('ID', $params)) {
			throw new Exception ('Missing required parameter ID.');
		}

		$original = $this->read ($params);

		$args = array();

		if (array_key_exists('USERNAME', $params) && $original['username'] != $params['USERNAME']) {
			$args[] = new DbParam('user.username', ':username', $params['USERNAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('PASSWORD', $params) && $original['password'] != $params['PASSWORD']) {
			$args[] = new DbParam('user.password', ':password', $params['PASSWORD'], PDO::PARAM_STR);
		}

		if (array_key_exists('ACTIVE', $params) && $original['active'] != $params['ACTIVE']) {
			$args[] = new DbParam('user.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		}

		if (array_key_exists('CREATE_DATE', $params) && $original['create_date'] != $params['CREATE_DATE']) {
			$args[] = new DbParam('user.create_date', ':create_date', $params['CREATE_DATE'], PDO::PARAM_STR);
		}

		if (array_key_exists('LAST_LOGIN_DATE', $params) && $original['last_login_date'] != $params['LAST_LOGIN_DATE']) {
			$args[] = new DbParam('user.last_login_date', ':last_login_date', $params['LAST_LOGIN_DATE'], PDO::PARAM_STR);
		}

		if (array_key_exists('NUMBER_OF_ATTEMPTS', $params) && $original['number_of_attempts'] != $params['NUMBER_OF_ATTEMPTS']) {
			$args[] = new DbParam('user.number_of_attempts', ':number_of_attempts', $params['NUMBER_OF_ATTEMPTS'], PDO::PARAM_INT);
		}

		if (sizeof($args)) {
			$sql = "UPDATE user
						SET " . MySqlDB::getSelectConditions($args, ', ') . "
						WHERE user.id = :id";
			$args[] = new DbParam('user.id', ':id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}


		$args = array();

		if (array_key_exists('FIRST_NAME', $params) && $original['first_name'] != $params['FIRST_NAME']) {
			$args[] = new DbParam('user_profile.first_name', ':first_name', $params['FIRST_NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('LAST_NAME', $params) && $original['last_name'] != $params['LAST_NAME']) {
			$args[] = new DbParam('user_profile.last_name', ':last_name', $params['LAST_NAME'], PDO::PARAM_STR);
		}

		if (array_key_exists('ADDRESS', $params) && $original['address'] != $params['ADDRESS']) {
			$args[] = new DbParam('user_profile.address', ':address', $params['ADDRESS'], PDO::PARAM_STR);
		}

		if (array_key_exists('CITY', $params) && $original['city'] != $params['CITY']) {
			$args[] = new DbParam('user_profile.city', ':city', $params['CITY'], PDO::PARAM_STR);
		}

		if (array_key_exists('ZIP', $params) && $original['zip'] != $params['ZIP']) {
			$args[] = new DbParam('user_profile.zip', ':zip', $params['ZIP'], PDO::PARAM_STR);
		}

		if (array_key_exists('STATE', $params) && $original['state'] != $params['STATE']) {
			$args[] = new DbParam('user_profile.state', ':state', $params['STATE'], PDO::PARAM_STR);
		}

		if (array_key_exists('COUNTRY', $params) && $original['country'] != $params['COUNTRY']) {
			$args[] = new DbParam('user_profile.country', ':country', $params['COUNTRY'], PDO::PARAM_STR);
		}

		if (sizeof($args)) {
			$sql = "UPDATE user_profile
					SET " . MySqlDB::getSelectConditions($args, ', ') . "
					WHERE user_profile.user_id = :user_id";
			$args[] = new DbParam('user_profile.user_id', ':user_id', $params['ID'], PDO::PARAM_INT);

			$this->db->execSql($sql, $args);
		}
	}

	public function delete (Array $params) {
		throw new Exception("User deleting is not implemented. Set user status to inactive.");
	}

	/******************** Custom Operations ********************/
	public function getOptions(Array $params = array()) {
		$args = array();

		if ($params && array_key_exists("ACTIVE", $params)) {
			$args[] = new DbParam('user.active', ':active', $params['ACTIVE'], PDO::PARAM_BOOL);
		} else {
			$args[] = new DbParam('user.active', ':active', true, PDO::PARAM_BOOL);
		}


		$sql = "SELECT DISTINCT
					user.id,
					user.username
				FROM user" .
			(sizeof($args) > 0 ? " WHERE " . MySqlDB::getSelectConditions($args, ' AND ') : "")
			. " ORDER BY user.username ASC";

		return $this->db->execSql($sql, $args);

	}

	public function authenticate(Array $params = array()) {
		$args = array(new DbParam('user.active', ':active', true, PDO::PARAM_BOOL));
		if (array_key_exists('USERNAME', $params)) {
			$args[] = new DbParam('user.username', ':username', $params['USERNAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter username");
		}

		$sql = "SELECT last_login_date, number_of_attempts
				FROM user
				WHERE " . MySqlDB::getSelectConditions($args, ' AND ');

		$results = $this->db->execSql($sql, $args);
		if (sizeof($results) === 0) {
			throw new UserDoesNotExistException('User ' . $params['USERNAME'] . ' does not exist');
		} else if (sizeof($results) > 1) {
			throw new Exception('Username and password provided yield inconsistent information, please contact site admin for help.');
		} else {
			// 5 failed login and you'll be put into a 10 minute time out.
			$numberOfAttempts = 0;
			foreach ($results as $row) {
				$numberOfAttempts = $row['number_of_attempts'];
				$lastLogin = new Date($row['last_login_date']);
				$tenMinsAgo = new Date(strtotime("-10 minutes"));

				if ($lastLogin > $tenMinsAgo && $numberOfAttempts > 5) {
					throw new TooManyFailedLoginException("User had attempted too many failed login within last 10 minutes. Please come back in 10 minutes");
				}
				break;
			}

			if (array_key_exists('PASSWORD', $params)) {
				$args[] = new DbParam('user.password', ':password', $params['PASSWORD'], PDO::PARAM_STR);
			} else {
				throw new Exception("Missing required parameter password");
			}

			$sql = "SELECT DISTINCT user.id, user.username
					FROM user
					WHERE " . MySqlDB::getSelectConditions($args, ' AND ');

			$results = $this->db->execSql($sql, $args);
			if (sizeof($results) === 0) {
				// User failed login, Log the time, and increment failed login
				$sql = "UPDATE user SET last_login_date = NOW(), number_of_attempts = " . ($numberOfAttempts+1);
				$this->db->execSql($sql, $args);
				throw new AccessDeniedException('Username and password does not match');
			} else if (sizeof($results) > 1) {
				throw new Exception('Username and password provided yield inconsistent information, please contact site admin for help.');
			} else {
				// User failed login, Log the time, and clear failed login
				$sql = "UPDATE user SET last_login_date = NOW(), number_of_attempts = 0";
				$this->db->execSql($sql, $args);
				return true;
			}
		}
	}

	public function isUsernameTaken(Array $params = array()) {
		$args = array(new DbParam('user.active', ':active', true, PDO::PARAM_BOOL));
		if (array_key_exists('USERNAME', $params)) {
			$args[] = new DbParam('user.username', ':username', $params['USERNAME'], PDO::PARAM_STR);
		} else {
			throw new Exception("Missing required parameter username");
		}

		$sql = "SELECT DISTINCT user.id, user.username
				FROM user
				WHERE " . MySqlDB::getSelectConditions($args, ' AND ');
		$results = $this->db->execSql($sql, $args);
		return (sizeof($results) !== 0);
	}

}
?>
