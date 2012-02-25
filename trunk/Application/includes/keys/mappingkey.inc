<?php

include_once 'key.inc';

class MappingKey extends Key {

	public function __construct ($id) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'Mapping';
	}
}
?>
