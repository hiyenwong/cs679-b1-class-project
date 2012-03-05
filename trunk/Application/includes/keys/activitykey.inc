<?php

require_once 'key.inc';

class ActivityKey extends Key {

	public function __construct ($id = null) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'Activity';
	}
}
?>
