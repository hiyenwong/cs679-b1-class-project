<?php

include_once 'key.inc';

class ActivityKey extends Key {

	public function __construct ($id) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'Activity';
	}
}
?>
