<?php

require_once 'key.inc';

class UserKey extends Key {

	public function __construct ($id = null) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'User';
	}
}
?>
