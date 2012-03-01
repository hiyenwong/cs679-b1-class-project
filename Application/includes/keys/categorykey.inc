<?php

require_once 'key.inc';

class CategoryKey extends Key {

	public function __construct ($id) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'Category';
	}
}
?>
