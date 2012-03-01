<?php

require_once 'user.inc';
require_once 'mappingdetail.inc';
require_once 'view.inc';
require_once 'factory.inc';
require_once 'comparable.inc';
require_once 'sources/mappingsource.inc';
require_once 'sources/mappingdetailsource.inc';

class Mapping extends View implements Comparable {

	private $key;
	protected $id;

	private $name;
	private $user;
	private $startingRow;
	private $mappingDetails;

	public function __construct (MappingKey $key) {
		$this->key = $key;

		parent::__construct ();

		if ($key->isNew()) {
			$this->markNew();
		} else {
			$this->id = $key->getId();
		}
		$this->mappingDetails = array();
	}

	public function getKey () {
		return $this->key;
	}

	public function getId () {
		return $this->id;
	}

	public function getName() {
		return $this->name;
	}

	public function getUser() {
		return $this->user;
	}

	public function getStartingRow() {
		return $this->startingRow;
	}



	public function setName($name) {
		$this->markModified();
		$this->name = $name;
	}

	public function setUser(User $user) {
		$this->markModified();
		$this->user = $user;
	}

	public function setStartingRow($startingRow) {
		$this->markModified();
		$this->startingRow = $startingRow;
	}




	/*****************
	 * Mapping Details
	 *****************/
	public function addMappingDetail(MappingDetail $detail) {
		if (!$this->hasMappingDetail($detail)) {
			$this->mappingDetails[] = $detail;
		}
	}

	public function hasMappingDetail(MappingDetail $detail) {
		foreach ($this->mappingDetails as $d) {
			if ($detail->equals($d)) {
				return true;
			}
		}
		return false;
	}

	public function removeMappingDetail(MappingDetail $detail) {
		foreach ($this->mappingDetails as $key => $d) {
			if ($detail->equals($d)) {
				unset($this->mappingDetails[$key]);
			}
		}
	}

	public function getMappingDetails() {
		return $this->mappingDetails;
	}

	public function purgeMappingDetails() {
		$this->mappingDetails = array();
	}



	public function read () {
		$mappingSource = MappingSource::getSource();
		$values = $mappingSource->read (array ('ID' => $this->id));

		$this->name = $values['name'];
		$this->user = $values['user_id'] ? Factory::getView(new UserKey($values['user_id'])) : null;
		$this->startingRow = $values['starting_row'];

		$mappingDetailSource = MappingDetailSource::getSource();
		foreach ($mappingDetailSource->getOptions(array('MAPPING_ID' => $this->id)) as $row) {
			$this->mappingDetails[] = new MappingDetail($this, $row['column_name'], $row['csv_column_number']);
		}
	}

	protected function insert () {
		$params = array();

		if ($this->name) {
			$params ['NAME'] = $this->name;
		} else {
			throw new Exception ('User requires a userid.');
		}

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->startingRow) {
			$params['STARTING_ROW'] = $this->startingRow;
		}

		$mappingSource = MappingSource::getSource();
		$this->id = $mappingSource->insert ($params);

		$mappingDetailSource = MappingDetailSource::getSource();
		foreach ($this->mappingDetails as $detail) {
			$mappingDetailSource->insert(array(
					'MAPPING_ID' => $this->id,
					'COLUMN_NAME' => $detail->getColumnName(),
					'CSV_COLUMN_NUMBER' => $detail->getCsvColumnNumber()));
		}

	}

	protected function update () {
		$params = array ();

		if ($this->name) {
			$params ['NAME'] = $this->name;
		}

		if ($this->user) {
			$params['USER_ID'] = $this->user->getId();
		}

		if ($this->startingRow) {
			$params['STARTING_ROW'] = $this->startingRow;
		}

		$mappingSource = MappingSource::getSource();
		$mappingSource->update ($params);

		$mappingDetailSource = MappingDetailSource::getSource();
		$mappingDetailSource->delete(array('MAPPING_ID' => $this->id));
		foreach ($this->mappingDetails as $detail) {
			$mappingDetailSource->insert(array(
							'MAPPING_ID' => $this->id,
							'COLUMN_NAME' => $detail->getColumnName(),
							'CSV_COLUMN_NUMBER' => $detail->getCsvColumnNumber()));
		}

	}

	protected function delete () {
		$mappingDetailSource = MappingDetailSource::getSource();
		$mappingDetailSource->delete(array('MAPPING_ID' => $this->id));

		$mappingSource = MappingSource::getSource();
		$mappingSource->delete(array('ID' => $this->id));
	}

	public function preWrite () {
		if (!$this->deleteRequested()) {
			if ($this->user) {
				$this->user->write();
			}
		}
	}

	public function postWrite () {}

	/*********************************************************************************/

	public function equals ($other) {

		if (!is_a ($other, __CLASS__)) {
			throw new Exception ('Object is not a ' . __CLASS__ . '.');
		}

		return ($this->getId () == $other->getId ());
	}

	public static function getOptions (Array $params = array()) {
		$mappingSource = MappingSource::getSource();
		$options = array();
		foreach ($mappingSource->getOptions($params) as $row) {
			$options[$row['id']] = $row['name'];
		}
		return $options;
	}

	public function __toString () {
		return $this->name;
	}

}

?>