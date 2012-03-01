<?php

require_once 'key.inc';

class UserKey extends Key {

	public function __construct ($id) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'User';
	}
}
?>
