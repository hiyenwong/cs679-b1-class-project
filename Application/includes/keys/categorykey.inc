<?php

require_once 'key.inc';

class CategoryKey extends Key {

	public function __construct ($id = null) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'Category';
	}
}
?>
