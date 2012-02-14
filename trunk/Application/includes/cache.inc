<?php
include_once 'key.inc';
include_once 'view.inc';

class Cache {

	private static $cache = null;

	private $values;

	private function __construct () {
		$this->values = array ();
	}

	public static function getCache () {

		if (self::$cache == null) {
			self::$cache = new Cache ();
		}

		return self::$cache;
	}

	public function flush () {
		$this->values = array ();
	}

	public function writeAndFlush () {
		foreach ($this->values as $key => $view) {
			$view->write ();
		}

		$this->flush ();
	}

	public function unregisterView (Key $key) {

		if (!array_key_exists ($key->__toString (), $this->values)) {
			throw new Exception ($key . ' not in cache.');
		}

		unset ($this->values [$key->__toString ()]);
	}

	public function registerView (Key $key, View $view) {
		$this->values [$key->__toString ()] = $view;
	}

	public function getView (Key $key) {

		if (!array_key_exists ($key->__toString (), $this->values)) {
			return null;
		}

		return $this->values [$key->__toString ()];
	}

	public function __toString () {
		$modified = 0;
		foreach ($this->values as $value) {
			if ($value->isModified ()) {
				$modified++;
			}
		}

		return 'Cache ' . count ($this->values) . ' views / ' . $modified . ' modified';
	}
}
?>