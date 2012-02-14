<?php
/**
 * $Id: user.inc,v 1.3 2010/06/09 14:59:10 cyl2478 Exp $
 */

include_once 'view.inc';
include_once 'role.inc';
include_once 'comparable.inc';
include_once 'keys/userkey.inc';
include_once 'sources/usersource.inc';
include_once 'sources/userrolesource.inc';

class User extends View implements Comparable {

	private $key;
	protected $id;
	
	private $username;
	private $password;
	private $status;
	private $roles;

	public function __construct (UserKey $key) {
		$this->key = $key;

		parent::__construct ();

		if ($key->isNew()) {
			$this->markNew();
		} else {
			$this->id = $key->getId();
		}
	}

	public function getKey () {
		return $this->key;
	}

	public function getId () {
		return $this->id;
	}
	
	public function getUsername() {
		return $this->username;
	}
	
	private function loadRoles() {
		$userRoleSource = UserRoleSource::getSource ();
		foreach ($userRoleSource->getUserRoles(array('USERID' => $this->id)) as $row) {
			$role = Factory::getView(new RoleKey($row['ROLE']));
			$this->roles[] = $role;
		}
	}
	
	public function getRoles () {
		if (!isset($this->roles)) {
			$this->loadRoles();
		}
		return $this->roles;
	}

	public function hasRole(Role $role) {
		foreach ($this->getRoles() as $r) {
			if ($role->equals($r)) {
				return true;
			}
		}
		return false;
	}
	
	public function removeRole (Role $role) {
		if ($this->hasRole($role)) {
			foreach ($this->roles as $key => $r) {
				if ($role->equals ($r)) {
					unset($this->roles[$key]);
					$this->markModified();
					break;
				}
			}
		}
	}

	public function addRole (Role $role) {
		if (!$this->hasRole($role)) {
			$this->roles[] = $role;
			$this->markModified();
		}
	}

	public function setUsername($username) {
		$this->markModified();
		$this->username = $username;
	}

	public function setPassword($password) {
		$this->markModified();
		$this->password = $password;
	}

	public function setStatus($status) {
		$this->markModified();
		$this->status = $status;
	}


	public function read () {
		$userSource = UserSource::getSource ();
		$values = $userSource->read (array ('ID' => $this->id));
		
		$this->username = $values['username'];
		$this->status = $values['status'];
	}

	protected function insert () {
		$userSource = UserSource::getSource();
		$params = array();

		if ($this->id) {
			$params ['USERNAME'] = $this->id;
		} else {
			throw new Exception ('User requires a userid.');
		}
		
		if ($this->password) {
			$params['PASSWORD'] = $this->password;
		} else {
			throw new Exception('User requires a password');
		}

		if ($this->status) {
			$params ['STATUS'] = $this->status;
		}

		$this->id = $userSource->insert ($params);

	}

	protected function update () {
		$source = UserSource::getSource();
		$params = array ();

		if ($this->id) {
			$params ['USERNAME'] = $this->id;
		} else {
			throw new Exception ('User requires a userid.');
		}

		if ($this->password) {
			$params ['PASSWORD'] = $this->password;
		} else {
			throw new Exception('User requires a password.');
		}

		if ($this->status) {
			$params ['STATUS'] = $this->status;
		}

		$source->update ($params);
	}

	protected function delete () {
		throw new Exception (__CLASS__ . ' does not support the ' . __METHOD__ . ' call.');
	}

	public function preWrite () {
		foreach ($this->roleData as $roleData) {
			$roleData ['ROLE']->write ();
		}
	}

	public function postWrite () {
		// nothing
	}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getId () == $other->getId ());
	}

	public static function getOptions (Array $params = array()) {
		$userSource = UserSource::getSource ();
		$users = array();
		foreach ($userSource->getOptions($params) as $row) {
			$users[$row['id']] = $row['username'];
		}
		return $users;
	}

	public static function getUsers(Array $params = array()) {
		$users = array();
		foreach (self::getOptions($params) as $key => $val) {
			$users[] = Factory::getView(new UserKey($key));
		}
		return $users;
	}
	
	public static function checkAuthentication($username, $password) {
		$userSource = UserSource::getSource();
		$results = $userSource->authenticate(array('USERNAME' => $username, 'PASSWORD' => $password));
		if (sizeof($results) === 0) {
			throw new AccessDeniedException('Username and password does not match any record');
		} else if (sizeof($results) > 1) {
			throw new AccessDeniedException('Username and password provided yield inconsistent information, please contact site admin for help.');
		} else {
			return true;
		}
	}

	public function __toString () {
		return self::formatUser ($this, self::$LONG_FORMAT);
	}
}

?>