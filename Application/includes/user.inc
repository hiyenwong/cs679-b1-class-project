<?php

require_once 'view.inc';
require_once 'phone.inc';
require_once 'activity.inc';
require_once 'mapping.inc';
require_once 'budget.inc';
require_once 'preferencetype.inc';
require_once 'comparable.inc';
require_once 'accessdeniedexception.inc';
require_once 'toomanyfailedloginexception.inc';
require_once 'userdoesnotexistexception.inc';
require_once 'keys/userkey.inc';
require_once 'sources/usersource.inc';
require_once 'sources/phonesource.inc';
require_once 'sources/userpreferencesource.inc';

class User extends View implements Comparable {

	private static $HASH_KEY = 'shajs,ddobjbqkwj6he8qjwasdpckeb[';

	private $key;
	protected $id;

	private $username;
	private $password = false;
	private $active;
	private $createdDate;
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
	private $activities;
	private $mappings;
	private $budgets;
	private $preferences;

	public function __construct (UserKey $key) {
		$this->key = $key;

		parent::__construct ();

		if ($key->isNew()) {
			$this->markNew();
		} else {
			$this->id = $key->getId();
		}

		$this->phones = array();
		$this->activities = array();
		$this->mappings = array();
		$this->budgets = array();
		$this->preferences = array();
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

	public function getCreatedDate() {
		return $this->createdDate;
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

	public function setPassword($password, $isEncrypted = false) {
		$this->markModified();
		$this->password = ($isEncrypted) ? $password : self::encryptPassword($password);
	}

	public function setActive($active) {
		$this->markModified();
		$this->active = $active;
	}

	public function setCreatedDate($createdDate) {
		$this->markModified();
		$this->createdDate = $createdDate;
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
			$this->markModified();
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
				$this->markModified();
				unset($this->phones[$key]);
				return;
			}
		}
	}

	public function getPhones() {
		return $this->phones;
	}

	public function purgePhones() {
		$this->markModified();
		$this->phones = array();
	}



	/*********
	* Mappings
	**********/
	public function addActivity(Activity $activity) {
		if (!$this->hasActivity($activity)) {
			$this->markModified();
			$this->activities[] = $activity;
		}
	}

	public function hasActivity(Activity $activity) {
		foreach ($this->activities as $a) {
			if ($activity->equals($a)) {
				return true;
			}
		}
		return false;
	}

	public function removeActivity(Activity $activity) {
		foreach ($this->activities as $key=>$a) {
			if ($activity->equals($a)) {
				$this->markModified();
				unset($this->activities[$key]);
				return;
			}
		}
	}

	public function getActivities() {
		return $this->activities;
	}
	
	public function getActivitiesAmount() {
		$debit = 0;
		$credits = 0;
		foreach ($this->activities as $index=>$activity) {
			$amount = $activity->getAmount();
			if ($activity->getAmount() > 0) {
				$debit += $amount;
			} else {
				$credit += $amount;
			}
		}
		return array('debit'=>$debit, 'credit'=>$credit);
	}

	public function purgeActivities() {
		$this->markModified();
		$this->activities = array();
	}



	/*********
	* Mappings
	**********/
	public function addMapping(Mapping $mapping) {
		if (!$this->hasMapping($mapping)) {
			$this->markModified();
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
				$this->markModified();
				unset($this->mappings[$key]);
				return;
			}
		}
	}

	public function getMappings() {
		return $this->mappings;
	}

	public function purgeMappings() {
		$this->markModified();
		$this->mappings = array();
	}



	/********
	* Budgets
	*********/
	public function addBudget(Budget $budget) {
		if (!$this->hasBudget($budget)) {
			$this->markModified();
			$this->budgets[] = $budget;
		}
	}

	public function hasBudget(Budget $budget) {
		foreach ($this->budgets as $b) {
			if ($budget->equals($b)) {
				return true;
			}
		}
		return false;
	}

	public function removeBudget(Budget $budget) {
		foreach ($this->budgets as $key=>$b) {
			if ($budget->equals($b)) {
				$this->markModified();
				unset($this->budgets[$key]);
				break;
			}
		}
	}

	public function getBudgets() {
		return $this->budgets;
	}

	public function purgeBudgets() {
		$this->markModified();
		$this->budgets = array();
	}



	/************
	* Preferences
	*************/
	public function addPreference(PreferenceType $preference) {
		if (!$this->hasPreference($preference)) {
			$this->markModified();
			$this->preferences[] = $preference;
		}
	}

	public function hasPreference(PreferenceType $preference) {
		foreach ($this->preferences as $p) {
			if ($preference->equals($p)) {
				return true;
			}
		}
		return false;
	}

	public function removePreference(PreferenceType $preference) {
		foreach ($this->preferences as $key=>$p) {
			if ($preference->equals($p)) {
				$this->markModified();
				unset($this->preferences[$key]);
				return;
			}
		}
	}

	public function getPreferences() {
		return $this->preferences;
	}

	public function purgePreferences() {
		$this->markModified();
		$this->preferences = array();
	}



	public function read () {
		$userSource = UserSource::getSource ();
		$values = $userSource->read (array ('ID' => $this->id));

		$this->username = $values['username'];
		$this->active = $values['active'];
		$this->createdDate = $values['created_date'];
		$this->lastLoginDate = $values['last_login_date'];
		$this->numberOfAttempts = $values['number_of_attempts'];
		$this->firstName = $values['first_name'];
		$this->lastName = $values['last_name'];
		$this->address = $values['address'];
		$this->city = $values['city'];
		$this->zip = $values['zip'];
		$this->state = $values['state'];
		$this->country = $values['country'];

		$phoneSource = PhoneSource::getSource();
		foreach ($phoneSource->getOptions(array('USER_ID' => $this->id)) as $row) {
			$this->phones[] = new Phone($this, $row['number'], $row['text_able'], $row['is_primary']);
		}

		$today = new Date();
		$firstDayOf6MonthsAgo = new Date(date('Y-m-d', strtotime("-5 months -" . ($today->format("%d") - 1) . " days")));
		foreach (Activity::getOptions(array(
				'USER_ID' => $this->id,
				'TRANSACTION_DATE_START' => $firstDayOf6MonthsAgo->format(Date::$SIMPLE_YEAR_MONTH_DAY),
				'TRANSACTION_DATE_END' => $today->format(Date::$SIMPLE_YEAR_MONTH_DAY))) AS $id => $value) {
			$this->activities[] = Factory::getView(new ActivityKey($id));
		}

		foreach (Mapping::getOptions(array('USER_ID' => $this->id)) AS $id=>$name) {
			$this->mappings[] = Factory::getView(new MappingKey($id));
		}

		foreach (Budget::getOptions(array('USER_ID' => $this->id)) AS $id=>$name) {
			$this->budgets[] = Factory::getView(new BudgetKey($id));
		}

		$userPreferenceSource = UserPreferenceSource::getSource();
		foreach ($userPreferenceSource->getOptions(array('USER_ID' => $this->id)) as $row) {
			$this->preferences[] = Factory::getView(new PreferenceTypeKey($row['preference_type_id']));
		}


	}

	protected function insert () {
		$params = array();

		if ($this->username) {
			$params ['USERNAME'] = $this->username;
		} else {
			throw new Exception ('User requires a username.');
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

		if ($this->createdDate) {
			$params['CREATED_DATE'] = $this->createdDate;
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

		$userSource = UserSource::getSource();
		$this->id = $userSource->insert ($params);

		$phoneSource = PhoneSource::getSource();
		foreach ($this->phones as $phone) {
			$phoneSource->insert(array(
					'USER_ID' => $this->id,
					'PHONE' => $phone->getNumber(),
					'TEXT_ABLE' => $phone->isTextable(),
					'IS_PRIMARY' => $phone->isPrimary()));
		}

		$userPreferenceSource = UserPreferenceSource::getSource();
		foreach ($this->preferences as $p) {
			$userPreferenceSource->insert(array('USER_ID' => $this->id, 'PREFERENCE_TYPE_ID' => $p->getId()));
		}

	}

	protected function update () {
		$params = array ('ID' => $this->id);

		if ($this->username) {
			$params ['USERNAME'] = $this->username;
		}

		if ($this->password) {
			$params ['PASSWORD'] = $this->password;
		}

		if ($this->active) {
			$params['ACTIVE'] = $this->active;
		}

		if ($this->createdDate) {
			$params['CREATED_DATE'] = $this->createdDate;
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

		$userSource = UserSource::getSource();
		$userSource->update ($params);

		$phoneSource = PhoneSource::getSource();
		$phoneSource->delete(array('USER_ID' => $this->id));
		foreach ($this->phones as $phone) {
			$phoneSource->insert(array(
							'USER_ID' => $this->id,
							'PHONE' => $phone->getNumber(),
							'TEXT_ABLE' => $phone->isTextable(),
							'IS_PRIMARY' => $phone->isPrimary()));
		}

		$userPreferenceSource = UserPreferenceSource::getSource();
		$userPreferenceSource->delete(array('USER_ID' => $this->id));
		foreach ($this->preferences as $p) {
			$userPreferenceSource->insert(array('USER_ID' => $this->id, 'PREFERENCE_TYPE_ID' => $p->getId()));
		}
	}

	protected function delete () {
		/** We technically do not delete user, we deactive them **/
		$params = array ('ID' => $this->id, 'ACTIVE' => false);
		$userSource = UserSource::getSource();
		$userSource->update ($params);
	}

	public function preWrite () {
		if (!$this->deleteRequested()) {
			foreach ($this->preferences as $p) {
				$p->write();
			}
		}
	}

	public function postWrite () {
		if (!$this->deleteRequested()) {
			foreach ($this->activities as $activity) {
				$activity->write();
			}

			foreach ($this->mappings as $mapping) {
				$mapping->write();
			}

			foreach ($this->budgets as $budget) {
				$budget->write();
			}
		}
	}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getUsername() == $other->getUsername());
	}

	public function __toString () {
		return $this->lastName . ', ' . $this->firstName . ' (' . $this->username . ')';
	}

	public function generateNewPassword() {
		$password = self::encryptPassword($this->randomPasswordGenerator(10));
		$this->setPassword($password);
		return $password;
	}


	public static function getOptions (Array $params = array()) {
		$userSource = UserSource::getSource ();
		$users = array();
		foreach ($userSource->getOptions($params) as $row) {
			$users[$row['id']] = $row['username'];
		}
		return $users;
	}

	public static function getUserByUserName ($username) {
		$userSource = UserSource::getSource ();
		foreach ($userSource->getOptions(array('USERNAME' => $username)) as $row) {
			// Since email address are unique, this should always return 1 user id
			return Factory::getView(new UserKey($row['id']));
		}
		return null;
	}

	public static function getUsers(Array $params = array()) {
		$users = array();
		foreach (self::getOptions($params) as $key => $val) {
			$users[] = Factory::getView(new UserKey($key));
		}
		return $users;
	}

	/**
	 * Boolean function that checks user, please if false is returned, throw a new AccessDeniedException
	 * Enter description here ...
	 * @param unknown_type $username
	 * @param unknown_type $password
	 * @throws AccessDeniedException
	 */
	public static function checkAuthentication($username, $password, $isPasswordEncrypted=false) {
		try {
			$userSource = UserSource::getSource();
			$userSource->authenticate(array('USERNAME' => $username, 'PASSWORD' => ($isPasswordEncrypted ? $password : self::encryptPassword($password))));
			return true;
		} catch (TooManyFailedLoginException $e) {
			return false;
		} catch (UserDoesNotExistException $e) {
			return false;
		} catch (AccessDeniedException $e) {
			return false;
		} catch (Exception $e) {
			return false;
		}
	}

	/**
	 * Check the Database and see if username is taken by an ACTIVE user
	 * return true/false
	 */
	public static function isUsernameTaken($username) {
		$userSource = UserSource::getSource();
		return $userSource->isUsernameTaken(array('USERNAME' => $username));
	}

	private static function encryptPassword($input) {
		$iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB);
		$iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);

		return bin2hex(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, self::$HASH_KEY, $input, MCRYPT_MODE_ECB, $iv));
	}

	private function randomPasswordGenerator($length) {
		$random= "";
		srand((double)microtime()*1000000);
		$char_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+";
		for($i = 0; $i < $length; $i++) {
			$random .= substr($char_list,(rand()%(strlen($char_list))), 1);
		}
		return $random;
	}
}

?>