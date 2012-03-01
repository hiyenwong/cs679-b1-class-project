<?php

require_once 'key.inc';

class BudgetKey extends Key {

	public function __construct ($id) {
		parent::__construct ($id);
	}

	public function getClass () {
		return 'Budget';
	}
}
?>
