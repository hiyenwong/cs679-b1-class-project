<?php
/**
 * $Id: user.inc,v 1.3 2010/06/09 14:59:10 cyl2478 Exp $
 */

require_once 'view.inc';
require_once 'phone.inc';
require_once 'mapping.inc';
require_once 'comparable.inc';
require_once 'keys/userkey.inc';
require_once 'sources/usersource.inc';
require_once 'sources/phonesource.inc';

class User extends View implements Comparable {

	private static $HASH_KEY = 'shajs,ddobjbqkwj6he8qjwasdpckeb[';

	private $key;
	protected $id;
	
	private $username;
	private $password = false;
	private $active;
	private $createDate;
	private $lastLoginDate;
	private $numberOfAttempts;
	private $firstName;
	private $lastName;
	private $email;
	private $address;
	private $city;
	private $zip;
	private $state;
	private $country;
	
	private $phones;
	private $mappings;

	public function __construct (UserKey $key) {
		$this->key = $key;

		parent::__construct ();

		if ($key->isNew()) {
			$this->markNew();
		} else {
			$this->id = $key->getId();
		}
		
		$this->phones = array();
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
	
	public function getActive() {
		return $this->active;
	}
	
	public function getCreateDate() {
		return $this->createDate;
	}
	
	public function getLastLoginDate() {
		return $this->lastLoginDate;
	}
	
	public function getNumberOfAttempts() {
		return $this->numberOfAttempts;
	}
	
	public function getFirstName() {
		return $this->firstName;
	}
	
	public function getLastName() {
		return $this->lastName;
	}
	
	public function getEmail() {
		return $this->email;
	}
	
	public function getAddress() {
		return $this->address;
	}
	
	public function getCity() {
		return $this->city;
	}
	
	public function getZip() {
		return $this->zip;
	}
	
	public function getState() {
		return $this->state;
	}
	
	public function getCountry() {
		return $this->country;
	}
	
	

	public function setUsername($username) {
		$this->markModified();
		$this->username = $username;
	}

	public function setPassword($password) {
		$this->markModified();
		$this->password = self::encryptPassword($password);
	}

	public function setActive($active) {
		$this->markModified();
		$this->active = $active;
	}
	
	public function setCreateDate($createDate) {
		$this->markModified();
		$this->createDate = $createDate;
	}
	
	public function setLastLoginDate($lastLoginDate) {
		$this->markModified();
		$this->lastLoginDate = $lastLoginDate;
	}
	
	public function setNumberOfAttempts($numberOfAttempts) {
		$this->markModified();
		$this->numberOfAttempts = $numberOfAttempts;
	}
	
	public function setFirstName($firstName) {
		$this->markModified();
		$this->firstName = $firstName;
	}
	
	public function setLastName($lastName) {
		$this->markModified();
		$this->lastName = $lastName;
	}
	
	public function setEmail($email) {
		$this->markModified();
		$this->email = $email;
	}
	
	public function setAddress($address) {
		$this->markModified();
		$this->address = $address;
	}
	
	public function setCity($city) {
		$this->markModified();
		$this->city = $city;
	}
	
	public function setZip($zip) {
		$this->markModified();
		$this->zip = $zip;
	}
	
	public function setState($state) {
		$this->markModified();
		$this->state = $state;
	}
	
	public function setCountry($country) {
		$this->markModified();
		$this->country = $country;
	}
	
	
	/********
	 * Phones
	 ********/
	public function addPhone(Phone $phone) {
		if (!$this->hasPhone($phone)) {
			$this->phones[] = $phone;
		}
	}
	
	public function hasPhone(Phone $phone) {
		foreach ($this->phones as $p) {
			if ($phone->equals($p)) {
				return true;
			}
		}
		return false;
	}
	
	public function removePhone(Phone $phone) {
		foreach ($this->phones as $key => $p) {
			if ($phone->equals($p)) {
				unset($this->phones[$key]);
			}
		}
	}
	
	public function getPhones() {
		return $this->phones;
	}
	
	public function purgePhones() {
		$this->phones = array();
	}
	
	
	
	/*********
	* Mappings
	**********/
	public function addMapping(Mapping $mapping) {
		if (!$this->hasMapping($mapping)) {
			$this->mappings[] = $mapping;
		}
	}
	
	public function hasMapping(Mapping $mapping) {
		foreach ($this->mappings as $m) {
			if ($mapping->equals($m)) {
				return true;
			}
		}
		return false;
	}
	
	public function removeMapping(Mapping $mapping) {
		foreach ($this->mappings as $key => $m) {
			if ($mapping->equals($m)) {
				unset($this->mappings[$key]);
			}
		}
	}
	
	public function getMappings() {
		return $this->mappings;
	}
	
	public function purgeMappings() {
		$this->mappings = array();
	}
	


	public function read () {
		$userSource = UserSource::getSource ();
		$values = $userSource->read (array ('ID' => $this->id));
		
		$this->username = $values['username'];
		$this->active = $values['active'];
		$this->createDate = $values['create_date'];
		$this->lastLoginDate = $values['last_login_date'];
		$this->numberOfAttempts = $values['number_of_attempts'];
		$this->firstName = $values['first_name'];
		$this->lastName = $values['last_name'];
		$this->email = $values['email'];
		$this->address = $values['address'];
		$this->city = $values['city'];
		$this->zip = $values['zip'];
		$this->state = $values['state'];
		$this->country = $values['country'];
		
		$phoneSource = PhoneSource::getSource();
		foreach ($phoneSource->getOptions(array('USER_ID' => $this->id)) as $row) {
			$this->phones[] = new Phone($this, $row['number'], $row['text_able'], $row['is_primary']);
		}
		
		foreach (Mapping::getOptions(array('USER_ID' => $this->id)) AS $row) {
			$this->mappings[] = Factory::getView(new MappingKey($row['id']));
		}
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

		if ($this->active) {
			$params['ACTIVE'] = $this->active;
		} else {
			throw new Exception('User requires an active');
		}
		
		if ($this->createDate) {
			$params['CREATE_DATE'] = $this->createDate;
		} else {
			throw new Exception('User requires a create date');
		}
		
		if ($this->lastLoginDate) {
			$params['LAST_LOGIN_DATE'] = $this->lastLoginDate;
		} else {
			throw new Exception('User requires a last login date');
		}
		
		if ($this->numberOfAttempts) {
			$params['NUMBER_OF_ATTEMPTS'] = $this->numberOfAttempts;
		} else {
			throw new Exception('User requires a number of attempts');
		}
		
		if ($this->firstName) {
			$params['FIRST_NAME'] = $this->firstName;
		} else {
			throw new Exception('User requires a first name');
		}
		
		if ($this->lastName) {
			$params['LAST_NAME'] = $this->lastName;
		} else {
			throw new Exception('User requires a last name');
		}
		
		if ($this->email) {
			$params['EMAIL'] = $this->email;
		} else {
			throw new Exception('User requires a email');
		}
		
		if ($this->address) {
			$params['ADDRESS'] = $this->address;
		}
		
		if ($this->city) {
			$params['CITY'] = $this->city;
		}
		
		if ($this->zip) {
			$params['ZIP'] = $this->zip;
		}
		
		if ($this->state) {
			$params['STATE'] = $this->state;
		}
		
		if ($this->country) {
			$params['COUNTRY'] = $this->country;
		}

		$this->id = $userSource->insert ($params);

		$phoneSource = PhoneSource::getSource();
		foreach ($this->phones as $phone) {
			$phoneSource->insert(array(
					'USER_ID' => $this->id,
					'PHONE' => $phone->getNumber(),
					'TEXT_ABLE' => $phone->isTextable(),
					'IS_PRIMARY' => $phone->isPrimary()));
		}
		
	}

	protected function update () {
		$source = UserSource::getSource();
		$params = array ();

		if ($this->id) {
			$params ['USERNAME'] = $this->id;
		}

		if ($this->password) {
			$params ['PASSWORD'] = $this->password;
		}

		if ($this->active) {
			$params['ACTIVE'] = $this->active;
		}
		
		if ($this->createDate) {
			$params['CREATE_DATE'] = $this->createDate;
		}
		
		if ($this->lastLoginDate) {
			$params['LAST_LOGIN_DATE'] = $this->lastLoginDate;
		}
		
		if ($this->numberOfAttempts) {
			$params['NUMBER_OF_ATTEMPTS'] = $this->numberOfAttempts;
		}
		
		if ($this->firstName) {
			$params['FIRST_NAME'] = $this->firstName;
		}
		
		if ($this->lastName) {
			$params['LAST_NAME'] = $this->lastName;
		}
		
		if ($this->email) {
			$params['EMAIL'] = $this->email;
		}
		
		if ($this->address) {
			$params['ADDRESS'] = $this->address;
		}
		
		if ($this->city) {
			$params['CITY'] = $this->city;
		}
		
		if ($this->zip) {
			$params['ZIP'] = $this->zip;
		}
		
		if ($this->state) {
			$params['STATE'] = $this->state;
		}
		
		if ($this->country) {
			$params['COUNTRY'] = $this->country;
		}

		$source->update ($params);
		
		$phoneSource = PhoneSource::getSource();
		$phoneSource->delete(array('USER_ID' => $this->id));
		foreach ($this->phones as $phone) {
			$phoneSource->insert(array(
							'USER_ID' => $this->id,
							'PHONE' => $phone->getNumber(),
							'TEXT_ABLE' => $phone->isTextable(),
							'IS_PRIMARY' => $phone->isPrimary()));
		}
	}

	protected function delete () {
		throw new Exception (__CLASS__ . ' does not support the ' . __METHOD__ . ' call.');
	}

	public function preWrite () {}

	public function postWrite () {
		if (!$this->deleteRequested()) {
			foreach ($this->mappings as $mapping) {
				$mapping->write();
			}
		}
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
		$results = $userSource->authenticate(array('USERNAME' => $username, 'PASSWORD' => self::encryptPassword($password)));
		if (sizeof($results) === 0) {
			throw new AccessDeniedException('Username and password does not match any record');
		} else if (sizeof($results) > 1) {
			throw new AccessDeniedException('Username and password provided yield inconsistent information, please contact site admin for help.');
		} else {
			return true;
		}
	}

	public function __toString () {
		return $this->lastName . ', ' . $this->firstName . ' (' . $this->username . ')';
	}
	
	private static function encryptPassword($input) {
		$iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB);
		$iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
	
		return bin2hex(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, self::$HASH_KEY, $input, MCRYPT_MODE_ECB, $iv));
	}
}

?>